
# OpenAPI (Swagger) Integration

## Introduction
Integrating Swagger with ASP.NET Core provides a streamlined way to automatically generate and maintain up-to-date API documentation,
making it easier for developers to understand, test, and interact with APIs. This integration uses the Swashbuckle library to enable
interactive documentation directly within an ASP.NET Core application.

## Key Steps for Integration

### Install Packages:

Add Swashbuckle.AspNetCore and Microsoft.AspNetCore.OpenApi packages. These packages enable the setup and generation of Swagger documentation.

### Configure Services:

Use `builder.Services.AddEndpointsApiExplorer()` to register API endpoints.

Use `builder.Services.AddSwaggerGen()` to generate Swagger documentation in an OpenAPI format.

Enable Middleware for Swagger in Development:

Within a development-only if statement (app.Environment.IsDevelopment()), add:

`app.UseSwagger()` to produce the Swagger JSON document.

`app.UseSwaggerUI()` to create a visual interface for browsing and testing endpoints.

Enhance Documentation with Custom Descriptions:

Use `.WithOpenApi()` to add summaries and descriptions to endpoints for clarity.

Use `.Produces<StatusCode>` to define response types, improving accuracy and readability.

### Test API Routes with Swagger UI:

Access the Swagger UI at /swagger to test endpoints.

Use `.ExcludeFromDescription()` to hide internal routes, keeping the documentation focused on essential endpoints.

### Conclusion
Following these steps, Swagger can be integrated into ASP.NET Core applications to create dynamic, interactive,
and easily accessible API documentation. This integration simplifies the development process, saves time, and helps ensure documentation aligns with API functionality.


# Generating API Clients with Swagger

## Introduction
Generating API clients with Swagger simplifies building and maintaining API interactions by automating client code generation. This approach saves development time, reduces errors, and ensures consistency in client-server communication.

## Key Points

### Swagger Overview
Swagger automates client code generation for API interactions using the OpenAPI Specification, which details API endpoints, parameters,
and data formats. This documentation acts as a blueprint for building consistent API integrations.

### Process of Client Code Generation
Create API Specification: Define the API’s endpoints, parameters, and responses in OpenAPI format, establishing a clear 
structure for client-server interactions.

 - Serve Swagger JSON: Expose the API specification as JSON, which allows other software or developers to reference it programmatically. 
 - Generate Client Code with NSwag: Use NSwag to automatically generate client code, handling requests and responses per the API's specifications (https://learn.microsoft.com/en-us/aspnet/core/tutorials/getting-started-with-nswag?view=aspnetcore-8.0&viewFallbackFrom=aspnetcore-10.0&tabs=visual-studio)
 - Integrate Client Code: Add the generated code into the project to facilitate seamless communication between the client application and server API.

By generating client code, developers can avoid manually coding API interactions, streamlining development, ensuring accuracy, and supporting easy updates to the API as needed.

## Conclusion
Using Swagger to generate API clients brings efficiency and reliability to API interactions, enabling developers to focus on core functionality while maintaining consistent, up-to-date communication with backend services.


# Customizing API Client Generation

## Introduction 
This guide details how to customize API client generation in .NET using Swagger, a powerful tool within the .NET ecosystem that simplifies backend-to-frontend communication. The process outlines creating a client code template, configuring deserialization, and generating a flexible client that can be updated to match API changes.

## Key Points
API Client Code Generation with Swagger

Start by retrieving the Swagger documentation URL from a running API server for client generation.

Create an HTTP client to handle API requests and gather the Swagger JSON, which will be parsed to form a structured API document.

Creating and Configuring a Custom Client
Use Swagger’s client generator settings to define parameters such as class name and namespace, making the client specific to your API structure.

Implement deserialization options to accommodate case insensitivity, ensuring compatibility between JSON responses and C# code.

## Automating and Maintaining the Client Code
Set up a client generator class, such as SwaggerClientGenerator, that calls methods to generate, save, and update the client code whenever the API changes.

The generated code supports type-safe API calls, eliminating the need for manual request handling, error checking, or deserialization in the main application code.

## Using the Generated Client
Instantiate the generated client and call methods like BlogsAllAsync() for data retrieval or BlogsPOSTAsync() for posting data, greatly simplifying code interactions with the API.

Modify the client generation settings as needed, such as by changing a single setting to create clients for other programming languages (e.g., TypeScript).

## Conclusion
Utilizing Swagger for API client generation in .NET automates communication between backends and clients, ensuring efficient and type-safe interactions. This approach reduces manual coding, supports easy updates, and enhances maintainability, adapting to API changes with minimal effort.


# Integrating Swagger and generating API clients

## Step 1: create a new console application

In this step, you’ll create a new ASP.NET Core console application, setting up the folders and initial structure you’ll need for this lab.

Open Visual Studio Code and select a new terminal.

Run the command to create a new console application: `dotnet new console -o SwaggerApiClientLab`

Navigate into the project folder: `cd SwaggerApiClientLab`

Add the necessary packages for working with Swagger and NSwag by running:

```bash
    dotnet add package Swashbuckle.AspNetCore
    dotnet add package NSwag.Core
    dotnet add package NSwag.CodeGeneration.CSharp
    dotnet add package NSwag.ApiDescription.Client
```

Inside your project folder, create a folder named Controllers to hold your API controller.

Confirm that your project structure looks like this:
    
```
    SwaggerApiClientLab
    ├── Controllers
    ├── Program.cs
    └── SwaggerApiClientLab.csproj
```

## Step 2: configure Swagger in the application

Next, you’ll add Swagger configuration to the application. This step involves setting up Swagger middleware so the API documentation is available and ready for client generation.

Open the `Program.cs` file and locate the appropriate section to add Swagger configuration.

Configure Swagger so it serves the API documentation in JSON format. Use the Swagger UI path `/swagger/v1/swagger.json`.

Start the server. Use `app.Run();`

Run the application using `dotnet run`, and navigate to the Swagger UI endpoint in your browser to verify the Swagger setup.

```C#
// Program.cs
using Microsoft.AspNetCore.Builder;
using Microsoft.Extensions.DependencyInjection;

public class Program
{
    public static async Task Main(string[] args)
    {
         var builder = WebApplication.CreateBuilder(args);
         builder.Services.AddControllers();
         builder.Services.AddEndpointsApiExplorer();
         builder.Services.AddSwaggerGen();
         var app = builder.Build();
         app.UseSwagger();
         app.UseSwaggerUI(c => c.SwaggerEndpoint("/swagger/v1/swagger.json", "My API V1"));
         Task.Run(() => await app.RunAsync());
    }
}
```

## Step 3: Setting up the API Specification

Now, you’ll define an API endpoint to provide the functionality for client code generation. This specification will document the API routes, parameters, and response types.

Inside the Controllers folder, create a new file named `UserController.cs`.

Create a basic User class with that has Id and Name properties.

Set up a simple GetUser endpoint that will accept a user ID and return sample JSON User detail.

Run the application again and view the Swagger documentation in your browser to confirm the API endpoint appears correctly in the documentation.

```C#
public class ClientGenerator
{
    public async Task GenerateClient()
    {
        using var httpClient = new HttpClient();
        var swaggerJson = await httpClient.GetStringAsync("http://localhost:<port>/swagger/v1/swagger.json");
        var document = await OpenApiDocument.FromJsonAsync(swaggerJson);

        var settings = new CSharpClientGeneratorSettings
        {
            ClassName = "GeneratedApiClient",
            CSharpGeneratorSettings = { Namespace = "MyApiClientNamespace" }
        };

        var generator = new CSharpClientGenerator(document, settings);
        var code = generator.GenerateFile();

        await File.WriteAllTextAsync("GeneratedApiClient.cs", code);
    }
}
```

3. In Program.cs Run the client generator to produce a file containing the generated client code, verifying that it’s created in the project directory. To create the client code, follow these steps:

Replace app.Run(); with Task.Run(() => app.RunAsync());. This will run the server asynchronously.

Below the code that starts the server, add an awaited delay of 3 seconds or more. This will let the server start up before you generate the client code.

Below the delay, add an awaited call to the GenerateClient method in the ClientGenerator class.

4. Run the application again to generate the client code.


```C#
// Controllers/UserController.cs
using Microsoft.AspNetCore.Mvc;

// User model
public class User
{
    public int Id { get; set; }
    public string Name { get; set; }
}

[ApiController]
[Route("api/[controller]")]
public class UserController : ControllerBase
{
    [HttpGet("{id}")]
    [Produces("application/json")]
    public ActionResult<User> GetUser(int id)
    {
        var user = new User 
        { 
            Id = id,
            Name = $"User {id}"
        };
        
        return Ok(user);
    }
}
```

## Step 4: Generating Client Code with NSwag

In this step, you’ll use NSwag to generate client code from the Swagger documentation, which will allow client-side code to interact with the server endpoints automatically.

1. Create a new file named ClientGenerator.cs in the project root.

2. Place the following code in ClientGenerator.cs to fetch the Swagger JSON and generate client code. This code uses the NSwag library and sets a custom namespace and class name for your generated client.

```C#
// ClientGenerator.cs
using System;
using System.IO;
using System.Net.Http;
using System.Threading.Tasks;
using NSwag;
using NSwag.CodeGeneration.CSharp;

public class ClientGenerator
{
    public async Task GenerateClient()
    {
        using var httpClient = new HttpClient();
        var swaggerJson = await httpClient.GetStringAsync("http://localhost:5000/swagger/v1/swagger.json");
        var document = await OpenApiDocument.FromJsonAsync(swaggerJson);

        var settings = new CSharpClientGeneratorSettings
        {
            ClassName = "GeneratedApiClient",
            CSharpGeneratorSettings = { Namespace = "MyApiClientNamespace" }
        };

        var generator = new CSharpClientGenerator(document, settings);
        var code = generator.GenerateFile();

        await File.WriteAllTextAsync("GeneratedApiClient.cs", code);
    }
}
```

##  Step 5: Customizing Client Settings

In this step, you’ll make adjustments to the generated client settings, like customizing the namespace and class names.

Open `ClientGenerator.cs` and locate the configuration settings for class name and namespace.

Change the settings to match custom preferences, such as setting the class name to CustomApiClient and the namespace to CustomNamespace.

Run the client generator again to verify the generated client code reflects your custom settings.

In `Program.cs`, comment out or remove the call to GenerateClient.

```C#
var settings = new CSharpClientGeneratorSettings
{
    ClassName = "CustomApiClient",
    CSharpGeneratorSettings = { Namespace = "CustomNamespace" }
};
```


## Step 6: Using the Generated Client

In this final step, you’ll use the generated client to make API requests from your application.

Open Program.cs and instantiate the generated client class, passing in the API base URL and HttpClient instance.

Use the client’s methods to call the GetUser endpoint, retrieving and displaying the user data.

Run the application to confirm the API client integration is functioning as expected.

```C#
// Program.cs (Additional Code)

Using CustomNamespace //replace with your namespace

var httpClient = new HttpClient();
var client = new CustomApiClient("http://localhost:5000", httpClient); //replace CustomApiClient with your class name

var user = await client.GetUserAsync(1);
Console.WriteLine($"Fetched User: {user}");
```

To test your application and verify that the Swagger integration and client code generation are working as expected, follow these steps:

Testing the Application
1. Run the Application and Check Swagger Configuration
Objective: Ensure that Swagger is correctly set up and serving the API documentation.

Steps:

Run the application:

dotnet run

Open a web browser and navigate to the Swagger UI, typically located at http://localhost:5000/swagger.

Check that the Swagger UI is displaying, and that the GetUser endpoint appears with the correct route (api/User/{id}).

What to Look For:

The Swagger UI should display without errors.

The GetUser endpoint should be visible, and the parameters and response types should be correct.

If you see errors or the endpoint is missing, recheck your Swagger configuration in Program.cs.

2. Verify the API Endpoint with Swagger UI
Objective: Confirm that the API endpoint (GetUser) is functional and accessible.

Steps:

In the Swagger UI, locate the GetUser endpoint.

Test the endpoint by entering a sample user ID (e.g., 1) and clicking the "Try it out" button.

Check the response section for the result.

What to Look For:

A successful response should return a string like "User 1", indicating the endpoint is working.

If you get a 404 error or an empty response, verify the UserController code and the route setup.

3. Run the Client Generator
Objective: Generate client code from the Swagger JSON using the ClientGenerator.

Steps:

In Program.cs, temporarily add code to call ClientGenerator:

await new ClientGenerator().GenerateClient();

Run the program again:

dotnet run

After running, verify that GeneratedApiClient.cs (or CustomApiClient.cs if you customized) appears in the project directory.

What to Look For:

The generated file should contain methods corresponding to the API endpoints.

If the file does not appear or has errors, check that the URL in ClientGenerator matches the Swagger JSON URL displayed in your Swagger UI.

4. Test the Generated Client Code
Objective: Confirm that the generated client can successfully make requests to your API.

Steps:

            1. In Program.cs, replace any previous testing code with the following:

```C#
Using CustomNamespace //replace with your namespace
var httpClient = new HttpClient();
var client = new CustomApiClient("http://localhost:5000", httpClient);

var user = await client.UserAsync(1);
Console.WriteLine($"Fetched User: {user}");
```

      2. Run the application again: 

                 dotnet run

            3. Observe the console output.

What to Look For:

The output should display the response from the API, e.g., "Fetched User: User 1".

If you get errors, check that the base URL and endpoint routes are correctly set in the generated client and Program.cs.

5. Modify the API and Regenerate the Client
Objective: Verify that the generated client stays in sync with API changes.

Steps:

Update the GetUser endpoint in UserController.cs (e.g., change the response to "User ID: {id}").

Run the application and regenerate the client code using ClientGenerator.

Re-run the main program to check that the updated client reflects the API change.

What to Look For:

The new response should match the updated endpoint behavior, confirming that the regenerated client stays in sync with the API.

If the output does not reflect the changes, verify that you regenerated the client and are calling the latest version in Program.cs.

Troubleshooting
If you’re having trouble, here are some things to check.

Step 2: Browsing to Swagger end point. This code uses 5000 as the port number throughout the exercise. When you run your application, check the log in the terminal to make sure the port number is 5000. You should see line in the terminal window that states, Now listening on: http://localhost:5000. If the port isn’t 5000, change the port number in all the code to match the port number your app is listening on.

Step 4: Generating client code. When you call app.Run(); to start the server, any code after that line will not be run. Be sure to change app.Run(); to Task.Run(() => app.RunAsync()); so the server starts asynchronously. Then the code you add to generate the client file will run.

Step 6: Using the Generated Client. In Step 5 you customized the client code by changing the class name and namespace. 

Make sure you update the line: Using CustomNamespace in Program.cs with whatever namespace you used in the GenerateClient method in ClientGenerator.cs. 

Make sure you replace CustomApiClient in var client = new CustomApiClient("http://localhost:5000", httpClient); in Program.cs with the custom class name you used in GenerateClient.

## Complete application code by file:

### Program.cs

```C#
using Microsoft.AspNetCore.Builder;
using Microsoft.Extensions.DependencyInjection;
using System.Net.Http;
using System.Threading.Tasks;
using CustomNamespace; //replace with your custom namespace
public class Program
{
    public static async Task Main(string[] args)
    {
        var builder = WebApplication.CreateBuilder(args);
 builder.Services.AddControllers();
 builder.Services.AddEndpointsApiExplorer();
        builder.Services.AddSwaggerGen();
        var app = builder.Build();
        app.UseSwagger();
        app.UseSwaggerUI(c => c.SwaggerEndpoint("/swagger/v1/swagger.json", "My API V1"));        
        app.MapControllers();

        //app.Run();
 Task.Run(() => app.RunAsync());
 //await Task.Delay(3000);
 //await new ClientGenerator().GenerateClient();
        var httpClient = new HttpClient();
        var client = new CustomApiClient("http://localhost:5000", httpClient);
        var user = await client.GetUserAsync(1);
        Console.WriteLine($"Fetched User: {user}");
    }
}
```

### Controllers/UserController.cs

```C#
using Microsoft.AspNetCore.Mvc;
// User model
public class User
{
    public int Id { get; set; }
    public string Name { get; set; }
}
[ApiController]
[Route("api/[controller]")]
public class UserController : ControllerBase
{
    [HttpGet("{id}")]
    [Produces("application/json")]
    public ActionResult<User> GetUser(int id)
    {
        var user = new User 
        { 
            Id = id,
            Name = $"User {id}"
        };
        
        return Ok(user);
    }
}
```

### ClientGenerator.cs

```C#
using System;
using System.IO;
using System.Net.Http;
using System.Threading.Tasks;
using NSwag;
using NSwag.CodeGeneration.CSharp;
public class ClientGenerator
{
    public async Task GenerateClient()
    {
        using var httpClient = new HttpClient();
        var swaggerJson = await httpClient.GetStringAsync("http://localhost:5000/swagger/v1/swagger.json");
        var document = await OpenApiDocument.FromJsonAsync(swaggerJson);
        var settings = new CSharpClientGeneratorSettings
        {
            ClassName = "CustomApiClient",
            CSharpGeneratorSettings = { Namespace = "CustomNamespace" }
        };
        var generator = new CSharpClientGenerator(document, settings);
        var code = generator.GenerateFile();
        await File.WriteAllTextAsync("CustomApiClient.cs", code);
    }
}
```

`GeneratedApiClient.cs` (Generated by NSwag) This file will be generated automatically after running ClientGenerator and contains fully typed methods for interacting with the API.




