using Microsoft.EntityFrameworkCore;

namespace ExercitiuLaborator12.Models
{
    public class AppDbContext : DbContext
    {
        public AppDbContext(DbContextOptions<AppDbContext> options)
        : base(options)
        {
        }
    }
}
