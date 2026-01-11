# Markly — Social Bookmarking with AI Suggestions

<p align="center">
  <img src="wwwroot/images/logo.svg" alt="Markly logo" width="240" height="240" style="border-radius: 16px;">
  <br>
  <a href="https://github.com/infernosalex/markly">
    <img src="https://img.shields.io/badge/GitHub-181717?style=flat&logo=github&logoColor=white" alt="GitHub">
  </a>
</p>

A social bookmarking built with ASP.NET Core MVC, Entity Framework Core, PostgreSQL with Anthropic tag and category suggestions.

## Features

- Accounts, roles, profiles, and social voting/commenting
- Bookmarks with categories, tags, advanced search, and public/private visibility
- AI-assisted tag/category suggestions via Anthropic Claude 4.5 Haiku
- Seed data with ready-to-use accounts for quick demos
- Docker Compose with PostgreSQL and Caddy reverse proxy

## Prerequisites
- .NET 9.0 SDK
- Docker & Docker Compose
- PostgreSQL database
- Anthropic API key (for AI suggestions)

## Configuration

### Database

Configure your PostgreSQL connection string in `appsettings.json`:

```json
{
  "ConnectionStrings": {
    "DefaultConnection": "Host=localhost;Port=5434;Database=markly;Username=markly_user;Password=markly_password"
  }
}
```

### Caddy (Basic Auth)

Caddy is configured to read the bcrypt hash from the MARKLY_BASICAUTH_HASH environment variable (the project Caddyfile uses {$MARKLY_BASICAUTH_HASH}).

Generate a bcrypt hash for the password (example uses `ImiPlaceASPdotnet`):

```bash
python3 -c 'import bcrypt; print(bcrypt.hashpw(b"ImiPlaceASPdotnet", bcrypt.gensalt()).decode())'
```
Set the environment variable before starting Caddy:

```bash
export MARKLY_BASICAUTH_HASH="$2b$12$..."
```

### AI Suggestions (Anthropic Claude)

The application uses Claude 4.5 Haiku for AI-powered tag and category suggestions. To enable this feature:

1. **Get an API key** from [Anthropic Console](https://console.anthropic.com/)

2. **Configure the API key** using one of these methods:

   **Option A: User Secrets (Recommended for development)**
   ```bash
   dotnet user-secrets init
   dotnet user-secrets set "Anthropic:ApiKey" "your-api-key-here"
   ```

   **Option B: Environment Variable**
   ```bash
   export Anthropic__ApiKey="your-api-key-here"
   ```

   **Option C: appsettings.json (Not recommended for production)**
   ```json
   {
     "Anthropic": {
       "ApiKey": "your-api-key-here",
       "Model": "claude-haiku-4-5",
       "MaxTokens": 256
     }
   }
   ```

3. **Rate Limiting Configuration** (optional):
   ```json
   {
     "RateLimiting": {
       "MaxRequestsPerWindow": 10,
       "WindowSeconds": 60
     }
   }
   ```
   This limits each user to 10 AI suggestion requests per minute.

### Running the Application

#### Option 1: Local Development

**Tip:** You can use Docker to run just the PostgreSQL database while developing locally:
```bash
docker compose up -d postgres
```
This avoids needing to install PostgreSQL locally. The connection string in `appsettings.Development.json` is already configured to work with this setup.

1. **Apply database migrations:**
   ```bash
   dotnet ef database update
   ```

2. **Run the application:**
   ```bash
   dotnet run
   ```

3. **Access the application** at `https://localhost:5001` or `http://localhost:5000`

#### Default Test Accounts (Seed Data)

The database is automatically seeded with sample data and test accounts:

| Email | Password | Role | Name |
|-------|----------|------|------|
| `admin@markly.com` | `Admin123!` | Admin | Alex Morgan |
| `sarah@example.com` | `Sarah123!` | User | Sarah Chen |
| `mike@example.com` | `Mike1234!` | User | Michael Johnson |

These accounts come with sample bookmarks, categories, tags, comments, and votes. The seed data only runs on an empty database.

#### Option 2: Docker

1. **Configure environment variables** in `docker-compose.yml`:
    ```yaml
    environment:
       Anthropic__ApiKey: ${ANTHROPIC_API_KEY}
    ```

    You can provide the `ANTHROPIC_API_KEY` in two common ways:

    - Option A: Export a system environment variable (useful for CI or local shells)

       ```bash
       export ANTHROPIC_API_KEY="your_actual_api_key"
       docker compose up -d
       ```

    - Option B: Create a `.env` file next to `docker-compose.yml` (recommended for local development)

       ```env
       ANTHROPIC_API_KEY=your_actual_api_key
       ```

2. **Start all services** (PostgreSQL, app, and Caddy reverse proxy):
   ```bash
   docker compose up -d
   ```

3. **Access the application** at `http://localhost` (port 80) or `https://localhost` (port 443)

4. **View logs:**
   ```bash
   docker compose logs -f markly
   ```

5. **Stop all services:**
   ```bash
   docker compose down
   ```

The Docker setup includes:
- **PostgreSQL** database (data persisted in a Docker volume)
- **Markly app** with automatic database migrations on startup
- **Caddy** reverse proxy with automatic HTTPS

## Using AI Suggestions

1. Navigate to Create or Edit Bookmark page
2. Enter a title and optionally a description
3. Click the **"Suggest with AI"** button
4. Review the suggested tags and categories
5. Click on any suggestion to add it to your bookmark
6. New tags/categories will be created automatically if they don't exist

## Project Structure

```
markly/
├── Configuration/          # Settings classes (Anthropic, RateLimiting)
├── Controllers/            # MVC Controllers
├── Data/
│   └── Entities/           # Entity models
├── Helpers/                # Utility classes
├── Migrations/             # EF Core migrations
├── Models/                 # Domain models
├── Services/
│   ├── Interfaces/         # Service contracts
│   └── Implementations/    # Service implementations
├── ViewModels/             # View models
├── Views/                  # Razor views
└── wwwroot/                # Static files (CSS, JS)
```

## Technologies

- ASP.NET Core MVC 9.0
- Entity Framework Core
- PostgreSQL
- ASP.NET Identity
- Bootstrap 5
- Anthropic Claude API

## License

This project is for educational purposes.
