# Notes on ASP.NET Core

## Introduction
ASP.NET Core is a modern, open-source framework designed for developing web applications and APIs with high performance, scalability, and cross-platform compatibility. This framework is particularly beneficial for building reliable, efficient APIs that adapt well to both small and large applications.

### Core Features of ASP.NET Core

 - Cross-platform compatibility: ASP.NET Core supports development on Windows, Linux, and macOS, allowing applications to be developed and deployed across diverse environments.
 - High performance: Built for efficiency, ASP.NET Core handles high volumes of requests with low overhead, making it suitable for demanding applications.
 - Modular Architecture: Its modular design enables developers to select only the necessary components, optimizing application performance and resource management.
 - Dependency injection: ASP.NET Core includes built-in dependency injection, promoting modular and maintainable code, which is easier to test and expand.
 - Routing and middleware: The framework’s routing capabilities efficiently map HTTP requests to endpoints, while middleware handles request processing steps like logging, authentication, and data validation.
 - Security and deployment options: ASP.NET Core offers secure handling of user data through integrated authentication and authorization features, with flexible deployment options on the cloud, local servers, or containers.

## Benefits of ASP.NET Core
 
 - Performance and scalability: Lightweight and scalable, ASP.NET Core adapts to an application’s growing traffic needs, supporting efficient resource management.
 - Unified programming model: Developers can streamline their workflows by using the same tools for web applications and APIs, reducing code complexity and increasing efficiency.
 - Cost-effectiveness: ASP.NET Core is open-source and compatible with cost-effective hosting options like Linux, helping to lower operating expenses.
 - Flexibility and maintainability: ASP.NET Core’s modularity enables gradual growth by adding new features over time, keeping the code manageable as the application evolves.

## Conclusion
ASP.NET Core is a versatile and high-performance framework for modern web applications and API development. Its features support cross-platform development, modularity, and high scalability, empowering developers to create flexible and reliable applications that grow seamlessly with business demands.

# Setting up a Web API Project

This guide will help you set up a basic Web API using ASP.NET Core. We’ll take it step-by-step, starting from installing the right tools to writing and testing your first API endpoint. This is meant for beginners who are just getting started with web development and only have Visual Studio Code (VS Code) installed.

What You’ll Need Before You Begin

To follow this guide, you must install the following tools on your computer. If you haven’t installed them yet, follow the instructions below:

## 1. .NET SDK
What it is: A set of tools and libraries to build .NET apps.

Download here: 
https://dotnet.microsoft.com/download

Installation tip: Choose the latest LTS version of the .NET SDK (e.g., .NET 9 if available). Download the SDK not just the runtime.

To verify installation:

```bash
dotnet --version
```

## 2. Visual Studio Code (VS Code)

You should already have this installed. If not, get it from 
https://code.visualstudio.com/

## 3. C# Extension for VS Code
In VS Code:

Go to the Extensions tab (left sidebar or press Ctrl+Shift+X)

Search for “C#”

Install the extension published by Microsoft

Step-by-Step: Create Your First Web API

### Step 1: Create a New Project
Open your terminal in VS Code or your operating system and type:

```bash
dotnet new webapi -o MyFirstApi

cd MyFirstApi
```

This command:

Creates a new folder called MyFirstApi

Sets up a new Web API project using the minimal API style, which doesn’t include controllers by default

You’ll see files like Program.cs, and possibly WeatherForecast.cs and WeatherForecastController.cs depending on your .NET version.

**Important**: The template does not include a Controllers folder by default. You’ll need to create it.

### Step 2: Open the Project in VS Code

```bash
code .
```
This opens the current folder in VS Code.

If prompted, allow required assets to be added. These help with debugging and building the app.

### Step 3: Modify Program.cs to Support Controllers
By default, the minimal API template doesn’t support controllers. To enable controller support:

Open the Program.cs file.

Replace its contents with the following:

```C#
var builder = WebApplication.CreateBuilder(args);

// Add services to the container.

builder.Services.AddControllers();

var app = builder.Build();

// Configure the HTTP request pipeline.

// Remove HTTPS redirection so you can test with http

// app.UseHttpsRedirection();

app.UseAuthorization();

app.MapControllers();

app.Run();
```

Note: We commented out `app.UseHttpsRedirection();` so you can test your API with `http://` instead of `https://`, which can sometimes be problematic in early development stages.

### Step 4: Create the Controllers Folder

Right-click the root of the project

Click `New Folder` 

Name it Controllers

This is where you define controllers. Controllers manage the logic of your app and respond to HTTP requests.

### Step 5: Create Your Own Controller

Let’s add a controller that returns a list of products.

Right-click the Controllers folder

Click `New File`

Name it ProductsController.cs

Paste this code into the file:

```C#
using Microsoft.AspNetCore.Mvc;

using System.Collections.Generic;

namespace MyFirstApi.Controllers

{

    [ApiController]

    [Route("api/[controller]")]

    public class ProductsController : ControllerBase

    {

        [HttpGet]

        public ActionResult<List<string>> Get()

        {

            return new List<string> { "Apple", "Banana", "Orange" };

        }

    }

}
```

What this does:
Defines a route: `api/products`

Handles GET requests to that route

Returns a list of strings as product names

### Step 6: Run Your API
In the terminal, type:
```
dotnet run
```
You should see output like:

Now listening on: `http://localhost:5000`

Note: Your port number may be different. For example, instead of "5000" you may see a different number. Use the number that displays in your terminal instead of 5000. 

Open a browser and go to:
```
http://localhost:5000/api/products
```
You should see:

["Apple", "Banana", "Orange"]

### Step 7: Understand Routing Basics

[HttpGet] maps a method to an HTTP GET request

[Route("api/[controller]")] means the route is based on the controller name (ProductsController → products)

You can define custom routes too:

[HttpGet("featured")]

public string GetFeaturedProduct() => "Mango";

Now available at:
```
http://localhost:5000/api/products/featured
```
### Step 8: Add More HTTP Methods
In your ProductsController, you can add methods for POST, PUT, and DELETE:

```C#
[HttpPost]

public ActionResult<string> Post([FromBody] string newProduct)

{

    return $"Added: {newProduct}";

}

[HttpPut("{id}")]

public ActionResult<string> Put(int id, [FromBody] string updatedProduct)

{

    return $"Updated product {id} to: {updatedProduct}";

}

[HttpDelete("{id}")]

public ActionResult<string> Delete(int id)

{

    return $"Deleted product with ID: {id}";

}
```
Use Postman to test these methods. You can install Postman from their website and use the free version here: 
https://www.postman.com/ 

### Step 9: What to do next: Practice and Build

Now that you have a basic Web API:

Try returning real data models (not just strings)

Add validation and error handling

Store and retrieve data using collections, files, or databases (future lessons will help)

## Conclusion
You’ve now built and tested a simple Web API using ASP.NET Core in VS Code. As you move forward, this setup becomes the foundation for more advanced features like authentication, databases, and real-world deployment.

# Minimal API vs Traditional Controllers in ASP.NET Core

## A Detailed Comparison
Both approaches can build the same functionality—CRUD endpoints, authentication, logging, Swagger—but they differ significantly in structure, philosophy, and how the resulting program looks. This document explains both styles in depth and highlights their differences.

reference: https://learn.microsoft.com/en-us/aspnet/core/fundamentals/apis?view=aspnetcore-10.0

## Option A — Minimal APIs

### Project Structure

A typical minimal API project looks like:
Minimal APIs were introduced to simplify building lightweight HTTP services. They emphasize low ceremony, functional style, and direct endpoint mapping.

```
Program.cs
Models/
Data/
Middleware/
```
There is no `Controllers` folder unless you add one manually.

### How Minimal APIs Work

#### Endpoints are defined directly in `Program.cs`

```C#
app.MapGet("/api/users", (UserRepository repo) =>
{
    return Results.Ok(repo.GetAll());
});
```

#### Dependency Injection via parameters

```C#
app.MapPost("/api/users", (User user, UserRepository repo) => { ... });
```

#### Routing is explicit and functional
You define routes with:
 - MapGet
 - MapPost
 - MapPut
 - MapDelete

#### Middleware

Logging, error handling, authentication, etc. are configured globally:

```C#
app.UseAuthentication();
app.UseAuthorization();
app.UseGlobalErrorHandling();
```

#### Swagger integration uses `.WithOpenApi()`

```C#
app.MapGet("/api/users", ...)
   .WithOpenApi();
```

### Advantages of Minimal APIs
 - Very lightweight and fast to build
 - Perfect for microservices and small APIs
 - Easy to read when the API surface is small
 - Less boilerplate than controllers
 - Functional style can feel modern and expressive

### Disadvantages of Minimal APIs
 - Can become messy if many endpoints accumulate in Program.cs
 - Less structure for large enterprise applications
 - Fewer attribute-based features (filters, validation attributes, etc.)
 - Some developers prefer the OOP style of controllers

## Option B - Traditional Controllers (MVC-style)

This is the classic ASP.NET Core approach. It uses classes, attributes, and routing conventions.

### Project Structure
A typical controller-based project looks like:

```
Program.cs
Controllers/
    UsersController.cs
Models/
Data/
Filters/

```
Controllers live in their own folder and group related endpoints together.

### How Controllers Work

### Endpoints live inside controller classes

```C#
[ApiController]
[Route("api/[controller]")]
public class UsersController : ControllerBase
{
    [HttpGet]
    public IActionResult GetUsers() => Ok(_repo.GetAll());
}

```

### Dependency Injection via constructor

```C#
public UsersController(UserRepository repo)
{
    _repo = repo;
}

```

### Routing via attributes

 - [HttpGet]
 - [HttpPost]
 - [HttpPut]
 - [HttpDelete]
 - [Route("api/users")]


### Filters and attributes for cross-cutting concerns

Controllers support:
 - ActionFilter
 - IAsyncActionFilter
 - [Authorize]
 - [ValidateModel]
 - [ProducesResponseType]

These allow fine-grained control per endpoint.


### Advantages of Controllers
 - Very organized for large applications
 - Natural grouping of endpoints by resource
 - Rich ecosystem of filters, attributes, and conventions
 - Familiar to many .NET developers
 - Better for enterprise-scale APIs

### Disadvantages of Controllers
 - More boilerplate
 - More files and ceremony
 - Slower to prototype small services
 - Less “inline clarity” compared to minimal APIs


| Feature | Minimal API | Controllers  |
| ----------- | ----------- |----------- |
|  Routing   | MapGet, MapPost    |  [HttpGet], [HttpPost]     |
|   DependcyInjection  |  Lambda parameters   |    Constructor injection   |
| Organization    |   Flat, functional  | Class-based, structured       |
|  Best for   | Small APIs, microservices    |  Large enterprise apps     |
|  Swagger   |  .WithOpenApi()   |    Automatic via attributes   |
|  Cross-cutting logic   |  Middleware    |    Middleware + filters    |
|   Learning curve   |  Easier for beginners   |  Familiar to MVC developers   |


