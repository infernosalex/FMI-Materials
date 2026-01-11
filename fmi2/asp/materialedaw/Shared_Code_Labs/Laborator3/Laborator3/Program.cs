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


// Rutele custom se definesc inaintea rutei DEFAULT

// EXERCITIUL 1

// 1
/*
 In aceasta varianta nu respecta cerinta pentru ca are nevoie obligatoriu 
 * de toti parametrii in ruta -> controller si action 
 * 
app.MapControllerRoute(
    name: "Concatenare",
    pattern: "concatenare/{controller=Examples}/{action=Concatenare}/{str1?}/{str2?}");
*/


// 1

app.MapControllerRoute(
    name: "Concatenare",
    pattern: "concatenare/{str1?}/{str2?}",
    defaults: new { controller = "Examples", action = "Concatenare" });

// 2

app.MapControllerRoute(
    name: "Produs",
    pattern: "produs/{param1}/{param2?}",
    defaults: new { controller = "Examples", action = "Produs" });


// 3

app.MapControllerRoute(
    name: "Operatie",
    pattern: "operatie/{param1?}/{param2?}/{op?}",
    defaults: new { controller = "Examples", action = "Operatie" });



// EXERCITIUL 2

// Index - varianta 1
app.MapControllerRoute(
    name: "StudentsIndex",
    pattern: "{controller=Students}/{action=Index}");

// Index - varianta 2
app.MapControllerRoute(
    name: "StudentsAll",
    pattern: "students/all",
    defaults: new { controller = "Students", action = "Index" });

//Show
app.MapControllerRoute(
    name: "StudentShow",
    pattern: "students/show/{id?}",
    defaults: new { controller = "Students", action = "Show" });

//Create
app.MapControllerRoute(
    name: "StudentCreate",
    pattern: "students/new",
    defaults: new { controller = "Students", action = "Create" });

//Edit
app.MapControllerRoute(
    name: "StudentEdit",
    pattern: "students/edit/{id?}",
    defaults: new { controller = "Students", action = "Edit" });

//Delete
app.MapControllerRoute(
    name: "StudentDelete",
    pattern: "students/delete/{id?}",
    defaults: new { controller = "Students", action = "Delete" });


// EXERCITIUL 3

// 1
// aceasta ruta permite accesarea metodei doar in momentul in care exista un numar CORECT de telefon

app.MapControllerRoute(
    name: "NrTelefon",
    pattern: "search/telefon/{telef:regex(^[0][0-9]{{9}})?}",
    defaults: new { controller = "Search", action = "NumarTelefon" });

// constrangerea nu trebuie sa fie atat de restrictiva
app.MapControllerRoute(
    name: "NrTelefon2",
    pattern: "search/telefon/{telef:regex([0-9])?}",
    defaults: new { controller = "Search", action = "NumarTelefon" });



//RUTA DEFAULT

app.MapControllerRoute(
    name: "default",
    pattern: "{controller=Home}/{action=Index}/{id?}")
    .WithStaticAssets();



app.Run();

