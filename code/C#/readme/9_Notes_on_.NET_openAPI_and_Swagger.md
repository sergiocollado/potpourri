
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


