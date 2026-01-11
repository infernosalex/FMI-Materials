using markly.Configuration;
using markly.Services.Interfaces;
using Microsoft.Extensions.Caching.Memory;
using Microsoft.Extensions.Options;

namespace markly.Services.Implementations;

public class InMemoryRateLimitingService : IRateLimitingService
{
    private readonly RateLimitingSettings _settings;
    private readonly IMemoryCache _cache;
    private readonly ILogger<InMemoryRateLimitingService> _logger;

    public InMemoryRateLimitingService(
        IOptions<RateLimitingSettings> settings,
        IMemoryCache cache,
        ILogger<InMemoryRateLimitingService> logger)
    {
        _settings = settings.Value;
        _cache = cache;
        _logger = logger;
    }

    public Task<bool> TryAcquireAsync(string userId, string endpoint)
    {
        var key = GetKey(userId, endpoint);
        var requests = _cache.GetOrCreate(key, entry =>
        {
            entry.AbsoluteExpirationRelativeToNow = TimeSpan.FromSeconds(_settings.WindowSeconds);
            return new Queue<DateTime>();
        });

        lock (requests)
        {
            // Remove requests older than window
            var windowStart = DateTime.UtcNow.AddSeconds(-_settings.WindowSeconds);
            while (requests.Count > 0 && requests.Peek() < windowStart)
            {
                requests.Dequeue();
            }

            // Check if within limit
            if (requests.Count < _settings.MaxRequestsPerWindow)
            {
                requests.Enqueue(DateTime.UtcNow);
                return Task.FromResult(true);
            }

            _logger.LogWarning("Rate limit exceeded for user {UserId} on endpoint {Endpoint}", userId, endpoint);
            return Task.FromResult(false);
        }
    }

    public Task<TimeSpan?> GetTimeUntilNextAllowedAsync(string userId, string endpoint)
    {
        var key = GetKey(userId, endpoint);

        if (!_cache.TryGetValue(key, out Queue<DateTime> requests))
        {
            return Task.FromResult<TimeSpan?>(null);
        }

        lock (requests!)
        {
            if (requests.Count < _settings.MaxRequestsPerWindow)
            {
                return Task.FromResult<TimeSpan?>(null);
            }

            var oldestRequest = requests.Peek();
            var expiresAt = oldestRequest.AddSeconds(_settings.WindowSeconds);
            var timeUntilExpiry = expiresAt - DateTime.UtcNow;

            return Task.FromResult<TimeSpan?>(timeUntilExpiry > TimeSpan.Zero ? timeUntilExpiry : null);
        }
    }

    private static string GetKey(string userId, string endpoint) => $"{userId}:{endpoint}";
}
