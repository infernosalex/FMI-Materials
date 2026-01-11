var builder = WebApplication.CreateBuilder(args);

// Add services to the container.
builder.Services.AddControllersWithViews();

var app = builder.Build();

// Configure the HTTP request pipeline.
if (!app.Environment.IsDevelopment())
{
    app.UseExceptionHandler("/Home/Error");
    // The default HSTS value is 30 days. You may want to change this for production scenarios, see https://aka.ms/aspnetcore-hsts.
    app.UseHsts();
}

app.UseHttpsRedirection();
app.UseRouting();

app.UseAuthorization();

app.MapStaticAssets();


// /articole/show/id

app.MapControllerRoute(
    name: "ArticlesShow",
    pattern: "articole/show/{id?}",
    defaults: new { controller = "Articles", action = "Show" })
    .WithStaticAssets();

app.MapControllerRoute(
    name: "default",
    pattern: "{controller=Articles}/{action=Index}/{id?}")
    .WithStaticAssets();

/* Pentru redenumirea metodei Index in listare
 * 
app.MapControllerRoute(
    name: "default",
    pattern: "{controller=Articles}/{action=listare}/{id?}")
    .WithStaticAssets();
*/

app.Run();
