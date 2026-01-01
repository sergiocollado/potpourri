# Middleware and open API

## Introduction to Middleware in ASP.NET Core

### Introduction

Middleware in ASP.NET Core is a series of software components that intercept and process HTTP requests in a structured pipeline, enabling developers to build modular,
maintainable, and secure applications. Each middleware component fulfills specific roles, such as handling requests for static files, logging, authentication, and routing. 
This layered architecture ensures efficient communication between client requests and server responses, improving performance and application management.

### Concept of Middleware
Middleware acts as a bridge between client requests and server responses, with each component performing a unique function within a sequence known as the middleware pipeline.
This setup allows for a clear separation of concerns, meaning each middleware focuses on a particular task, like logging or authentication, before passing the request along the pipeline.
For instance, logging middleware tracks user interactions, while authentication middleware verifies user credentials, controlling access to specific application sections.

### The Middleware Pipeline in ASP.NET Core
The middleware pipeline is designed to manage HTTP requests and responses in a structured sequence. When a request enters the pipeline,
it first interacts with the initial middleware component (such as logging), followed by authentication, and so on, 
until it reaches the application logic, which retrieves or processes data. After the application logic is complete, 
the pipeline generates a response and sends it back to the client. The order in which these components are executed is crucial;
for example, placing authentication middleware before data retrieval prevents unauthorized access.

### Built-in Middleware Components
ASP.NET Core offers several built-in middleware components to manage common tasks:

 - UseAuthentication: This component verifies user authentication before allowing access to secure application parts, ensuring that sensitive data remains protected.
 - UseRouting: This middleware directs incoming requests to the appropriate controller based on the request URL, simplifying navigation within the application.

### Conclusion
In ASP.NET Core, middleware plays an essential role in managing HTTP requests by breaking down the process into manageable steps within the middleware pipeline. 
This modular setup supports efficient request handling and enhances application security and maintainability. With the middleware pipeline, 
developers can create robust, responsive applications that efficiently manage client-server interactions.

# Built-in Middleware Components

## Introduction
ASP.NET Core offers several built-in middleware components that streamline the management of web requests and responses, enhancing application security and performance.

## Key Components

### Exception Handling Middleware
Manages application errors by redirecting users to a custom error page, protecting sensitive details while logging errors for developer review. For production, use app.UseExceptionHandler("/Home/Error"), and for development, use app.UseDeveloperExceptionPage() for detailed debugging information.

### Authentication Middleware
Verifies user identity to control access to restricted sections. Add authentication to the request pipeline with app.UseAuthentication() in the Startup.cs file to ensure that only logged-in users access protected areas.

### Authorization Middleware
Regulates user permissions, granting access only to authorized users. Implemented through app.UseAuthorization(), this middleware complements authentication by enforcing user access rights based on defined policies.

### Logging Middleware
Records key events and errors, offering insights into application behavior for monitoring and troubleshooting. Enable this with app.UseHttpLogging() and configure levels in appsettings.json to control log details.

## Conclusion
By implementing exception handling, authentication, authorization, and logging middleware, ASP.NET Core applications become more secure, reliable, and maintainable, providing a solid foundation for building responsive web applications.


# Custom Middleware

## Introduction
This guide covers creating and implementing custom middleware in ASP.NET Core, focusing on examples like request logging, response timing, and API key validation.

## Key Points

### Middleware Fundamentals
Middleware is central in processing requests and responses through ASP.NET Core’s pipeline.

The `app.Use()` function enables custom middleware by defining a request delegate, which processes requests sequentially.

### Examples of Custom Middleware

 - Logging Middleware: Logs request paths and response status codes using Console.WriteLine before and after each request.
 - Timing Middleware: Measures request duration by recording the start time before the next delegate and calculating the duration after it completes.

## Conditional Middleware with UseWhen()
Middleware can run conditionally based on certain criteria, such as non-GET requests, using `UseWhen()`.

Access control using API keys is demonstrated, allowing requests with a valid API key while returning a 401 Unauthorized response for invalid keys.

## Conclusion
These middleware implementations provide a foundational approach to logging, timing, and access control and show how to extend ASP.NET Core’s capabilities.

# Lab: Implementing Middleware Components 

## Step 1: prepare the application

You’ll create a small ASP.NET Core application using the command line. This application will integrate several built-in middleware components, and you’ll add custom middleware for logging requests and response details.

Steps:

Open a terminal and navigate to your desired directory.

Create a new ASP.NET Core empty project with the following command: `dotnet new web -o MyAspNetCoreApp`

Navigate to the project folder: `cd MyAspNetCoreApp`

Open the project in your code editor (e.g., Visual Studio Code): `code .`

## Step 2: configure built-in middle ware components

In this step, you will configure essential built-in middleware components: Exception Handling, Authentication, Authorization, and Logging. You don’t have to fully implement authentication and authorization. Just include the middleware components.

## Step 2: Configure built-in middle ware components

In `Program.cs`, configure the exception handling middleware for production and development environments.

Add the authentication middleware that can be used to verify user identities.

Add authorization middleware that can be used to control user permissions.

Configure HTTP logging to capture request and response details. Add the HTTP logging service in builder.Services and apply the middleware.

Save your changes after each configuration so you can verify that everything is set up correctly.


In the root directory, locate the `Program.cs file`. This file will be used to configure all middleware components.

```C#
var builder = WebApplication.CreateBuilder(args);
var app = builder.Build();

app.MapGet("/", () => "Hello World!");

app.Run();
```

Add:

For the exception handling: 

```C#
if (!app.Environment.IsDevelopment())
{
    app.UseExceptionHandler("/Home/Error");
}
else
{
    app.UseDeveloperExceptionPage();
}
```

For the Authentication Middleware:
```C#
app.UseAuthentication();
```

For the HTTP Logging Configuration:
Service configuration in builder.Services:

```C#
builder.Services.AddHttpLogging(logging =>
{
    logging.LoggingFields = Microsoft.AspNetCore.HttpLogging.HttpLoggingFields.All;
    logging.RequestBodyLogLimit = 4096;
    logging.ResponseBodyLogLimit = 4096;
});
Adding HTTP logging middleware:

app.UseHttpLogging();
```



## Step 3: develop custom middle-ware: 

You will now create custom middleware that logs the request path and response status, as well as middleware that records the request duration.

Steps:

In `Program.cs`, add custom middleware to log the request path and response status.

Add another custom middleware to track the request duration.

Save the changes once you’ve completed all the configurations.


For the custom middleware:

Middleware for Request Path and Response Status Logging:

```C#
app.Use(async (context, next) =>
{
    Console.WriteLine($"Request Path: {context.Request.Path}");
    await next.Invoke();
    Console.WriteLine($"Response Status Code: {context.Response.StatusCode}");
});
```

For the  Middleware for Request Duration Logging:

```C#
app.Use(async (context, next) =>
{
    var startTime = DateTime.UtcNow;
    Console.WriteLine($"Start Time: {startTime}");
    await next.Invoke();
    var duration = DateTime.UtcNow - startTime;
    Console.WriteLine($"Response Time: {duration.TotalMilliseconds} ms");
});
```


So the entire `Program.cs` file after all code has been added.

```C#
using Microsoft.AspNetCore.Builder;
using Microsoft.Extensions.Hosting;
using System;

var builder = WebApplication.CreateBuilder(args);

// Configure services
builder.Services.AddHttpLogging(logging =>
{
    logging.LoggingFields = Microsoft.AspNetCore.HttpLogging.HttpLoggingFields.All;
    logging.RequestBodyLogLimit = 4096;
    logging.ResponseBodyLogLimit = 4096;
});

builder.Services.AddAuthentication();
builder.Services.AddAuthorization();

var app = builder.Build();

// Configure middleware
if (!app.Environment.IsDevelopment())
{
    app.UseExceptionHandler("/Home/Error");
}
else
{
    app.UseDeveloperExceptionPage();
}

app.UseAuthentication();
app.UseAuthorization();
app.UseHttpLogging();

// Custom middleware for logging request path and response status
app.Use(async (context, next) =>
{
    Console.WriteLine($"Request Path: {context.Request.Path}");
    await next.Invoke();
    Console.WriteLine($"Response Status Code: {context.Response.StatusCode}");
});

// Custom middleware for tracking request duration
app.Use(async (context, next) =>
{
    var startTime = DateTime.UtcNow;
    Console.WriteLine($"Start Time: {startTime}");
    await next.Invoke();
    var duration = DateTime.UtcNow - startTime;
    Console.WriteLine($"Response Time: {duration.TotalMilliseconds} ms");
});

app.MapGet("/", () => "Hello, ASP.NET Core Middleware!");

app.Run();
```

## Step 4: test the middleware pipeline


inLabInstructionsPart~bxmH6aCVEe-2ew70qR_lfQ
​
With all middleware components in place, test the application to observe how requests and responses are processed.

Steps:

Run the application: `dotnet run`

Open a browser and make requests to the application, such as accessing `http://localhost:5000` (the port is defined at `launchsettings.json`.

Observe the logs in the terminal to confirm the output of the custom middleware, request timing, and built-in middleware.

Verify that error handling correctly redirects to an error page in production and shows detailed errors in development.

An example of the output: 

```
Request Path: /
Start Time: 10/29/2024 4:21:58 PM
Response Time: 8.319 ms
Response Status Code: 200
Request Path: /favicon.ico
Start Time: 10/29/2024 4:21:59 PM
Response Time: 0.084 ms
Response Status Code: 404
```

# Designing Middleware for Performance

## Introduction

This guide outlines essential steps for designing middleware in ASP.NET Core applications. These steps will help ensure middleware operates efficiently, minimizes latency, and improves application responsiveness.

## Guidelines
 - Set Up Lightweight Middleware: Design each middleware to handle only quick tasks like logging or routing. Offload complex operations to background services to avoid delays and keep middleware responsive.
 - Implement Short-Circuiting: Configure middleware to terminate requests early when conditions aren’t met, such as ending the pipeline on failed authentication. This prevents unnecessary processing.
 - Centralize Error Handling: Set up one error-handling middleware to manage exceptions, reduce repetitive code, and speed up request handling.
 - Enable Asynchronous Operations: Use asynchronous patterns within middleware to handle requests without blocking, keeping other requests moving efficiently under heavy load.
 - Leverage Built-In Middleware: Use ASP.NET Core’s built-in middleware for tasks like compression and logging. These components are optimized for performance, saving development time and ensuring efficiency.
 - Order Middleware Strategically: Critical checks, such as authentication, should be placed early in the pipeline to prevent invalid requests from reaching more intensive components.
 - Combine Middleware Where Possible: Combining similar tasks reduces the number of middleware components. This minimizes the time spent processing and simplifies the request pipeline.

## Conclusion 
Applying these steps lets you design middleware that handles requests quickly and efficiently, enhancing overall application performance. Consistently following these practices will help create an optimized ASP.NET Core application that can manage high loads with responsiveness and reliability.


# Securing Middleware

## Introduction
This guide outlines essential steps to secure middleware in ASP.NET Core applications. Following these practices can better protect your application and its users from common security threats.

## How to Secure Middleware in ASP.NET Core

 - Validate and Sanitize Inputs: Apply input validation to ensure data is correctly formatted and sanitized to strip harmful content, preventing injections and malicious scripts.
 - Enforce HTTPS for Secure Communication: Add app.UseHttpsRedirection() in your middleware setup to enforce HTTPS, ensuring data exchanged between users and your server is encrypted.
 - Secure Cookies and Session Data: Set cookies with HttpOnly and Secure attributes (Cookie.HttpOnly = true and Cookie.SecurePolicy = CookieSecurePolicy.Always) to prevent access by browser scripts, reducing cross-site scripting (XSS) vulnerabilities.
 - Perform Authentication and Authorization Early: Place app.UseAuthentication() and app.UseAuthorization() at the beginning of the middleware pipeline to block unauthorized access to restricted sections immediately.
 - Log Security Events Carefully: Log security events like login attempts and access denials without sensitive details. Logging tools capture basic information such as timestamps, IP addresses, and general event descriptions.
 - Handle Errors Securely: Configure error handling to display a generic message to users while logging detailed information for developers. Use ExceptionHandlerMiddleware to manage error responses without revealing technical information.

## Conclusion
These practices strengthen middleware security in ASP.NET Core, protecting your app from common threats. Review and update these configurations regularly to maintain security against new vulnerabilities.
manage high loads with responsiveness and reliability.


# Lab: Designing and Securing Middleware Components

## Step 1: create project and setup a new ASP.NET core WebAPI project

Open Visual Studio Code and create a new folder for your project.

Open the terminal and run the following commands to create a new ASP.NET Core Web API project: `dotnet new webapi -o MiddlewareOptimizationApp && cd MiddlewareOptimizationApp`

Open the `Program.cs` file. You’ll be modifying this file to implement middleware components.

Delete any controller files in the Controllers folder to focus solely on middleware implementation.

## Step 2: Configure HTTP Only in Program.cs

For simplicity, configure the application to listen on HTTP only by removing any HTTPS-specific code in Program.cs. This will allow learners to test the middleware without requiring a secure HTTPS connection.

```C#
var builder = WebApplication.CreateBuilder(args);

// Configure to listen on HTTP only for simplicity
builder.WebHost.ConfigureKestrel(options =>
{
    options.ListenLocalhost(5294);
});

var app = builder.Build();
```

This setup allows the app to respond only to HTTP requests on http://localhost:5294.

## Step 3: Design Middleware for Performance Optimization and Security

In this step, learners will write middleware components to handle performance optimization and security. Specifically:

 - Simulated HTTPS Enforcement: Use a query parameter to simulate HTTPS enforcement. If the secure=true parameter is missing, the middleware should block the request as if it were non-HTTPS.
 - Short-Circuit Unauthorized Access: Stop further processing for unauthorized requests.
 - Asynchronous Processing: Implement asynchronous methods to handle I/O operations without blocking other requests.
 - Input Validation: Validate incoming request data and sanitize any unsafe input.
 - Authentication Checks: Add early authentication checks to restrict access for unauthenticated users.
 - Security Event Logging: Log security events for any blocked or failed requests.

### 1. Security Event Logging: 

Place this logging middleware at the beginning of the pipeline to capture any security-related events based on status codes from subsequent middleware.

```C#
// Middleware to log security events if response status indicates an issue
app.Use(async (context, next) =>
{
    await next(); // Run the next middleware first

    if (context.Response.StatusCode >= 400)
    {
        Console.WriteLine($"Security Event: {context.Request.Path} - Status Code: {context.Response.StatusCode}");
    }
});
```

### 2. Simulated HTTPS Enforcement:

This middleware simulates HTTPS enforcement by checking for a ?secure=true query parameter. If the parameter is missing, it blocks the request.

```C#
// Simulated HTTPS Enforcement Middleware
app.Use(async (context, next) =>
{
    // Check for a query parameter to simulate HTTPS enforcement (e.g., "?secure=true")
    if (context.Request.Query["secure"] != "true")
    {
        context.Response.StatusCode = 400;
        await context.Response.WriteAsync("Simulated HTTPS Required");
        return;
    }

    await next();
});
```

### 3. Input Validation:

This middleware checks the input query parameter. Only alphanumeric characters are allowed, and it blocks any input containing <script>.

```C#
// Middleware for input validation
app.Use(async (context, next) =>
{
    var input = context.Request.Query["input"];
    if (!IsValidInput(input))
    {
        if (!context.Response.HasStarted)
        {
            context.Response.StatusCode = 400;
            await context.Response.WriteAsync("Invalid Input");
        }
        return;
    }

    await next();
});

// Helper method for input validation
static bool IsValidInput(string input)
{
    // Checks for any unsafe characters or patterns, including "<script>"
    return string.IsNullOrEmpty(input) || (input.All(char.IsLetterOrDigit) && !input.Contains("<script>"));
}
```

This middleware ensures that only safe input passes through, blocking malicious patterns like <script>.

### 4. Unauthorized Access

This middleware checks if the path is `/unauthorized`. If so, it returns a 401 status with "Unauthorized Access" and blocks further processing.

```C#
// Middleware for short-circuiting unauthorized access
app.Use(async (context, next) =>
{
    if (context.Request.Path == "/unauthorized")
    {
        if (!context.Response.HasStarted)
        {
            context.Response.StatusCode = 401;
            await context.Response.WriteAsync("Unauthorized Access");
        }
        return; // Exit middleware pipeline early if unauthorized
    }
    await next();
});
```
This middleware handles unauthorized access by blocking the request if the path is /unauthorized.

### 5. Simulated Authentication and Secure Cookies:

This middleware simulates authentication using the authenticated=true query parameter. If the parameter is missing, it blocks the request with "Access Denied" (403). For authenticated requests, it sets a secure cookie.


```C#
// Middleware for simulated authentication and secure cookies
app.Use(async (context, next) =>
{
    // Simulate authentication with a query parameter (e.g., "?authenticated=true")
    var isAuthenticated = context.Request.Query["authenticated"] == "true";
    if (!isAuthenticated)
    {
        if (!context.Response.HasStarted)
        {
            context.Response.StatusCode = 403;
            await context.Response.WriteAsync("Access Denied");
        }
        return;
    }

    context.Response.Cookies.Append("SecureCookie", "SecureData", new CookieOptions
    {
        HttpOnly = true,
        Secure = true
    });

    await next();
});
```
This middleware allows learners to simulate both "authenticated" and "unauthenticated" scenarios by including or excluding the authenticated=true query parameter.

### 6. Asynchronous Processing: 

This middleware simulates asynchronous processing by briefly delaying the response and adding "Processed Asynchronously" to the output.


```C#
// Middleware for asynchronous processing
app.Use(async (context, next) =>
{
    await Task.Delay(100); // Simulate async operation
    if (!context.Response.HasStarted)
    {
        await context.Response.WriteAsync("Processed Asynchronously\n");
    }
    await next();
});
```

The asynchronous processing middleware only executes if previous middleware components allow the request to proceed.

### 7. Final Response Middleware:

This middleware provides a final response message for any request that successfully reaches the end of the pipeline.


```C#
// Final Response Middleware
app.Run(async (context) =>
{
    if (!context.Response.HasStarted)
    {
        await context.Response.WriteAsync("Final Response from Application\n");
    }
});
```
This ensures that requests that pass through all middleware receive a final response message.

### 8 Testing middleware performance and security

After writing the middleware components, follow these testing steps. You can use a tool like Postman or curl for testing, or adjust URLs directly in your browser.

| condition | url example |
| ----------- | ----------- |
| Simulated HTTPS Enforcement | http://localhost:5294/ |
| Default Route (authenticated) | http://localhost:5294/?secure=true&authenticated=true |
| Unauthorized Access | http://localhost:5294/unauthorized?secure=true |
| Invalid Input | http://localhost:5294/?secure=true&input=<script> |
| Access Denied (Unauthenticated)  | http://localhost:5294/?secure=true |
| Security Event Log | Any blocked request (400+ status) |


### Default Route (Asynchronous Processing Test):

URL: http://localhost:5294/?secure=true 

Expected Output: "Processed Asynchronously" followed by "Final Response from Application."

Explanation: Confirms that asynchronous middleware is functioning as expected.

### Simulated HTTPS Enforcement Test: 

URL: http://localhost:5294/?secure=true&authenticated=true

Expected Output: "Simulated HTTPS Required" with a 400 status code.

Explanation: Ensures the middleware blocks requests that don’t include ?secure=true, simulating HTTPS enforcement.

### Unauthorized Access Test:

URL: http://localhost:5294/unauthorized?secure=true

Expected Output: "Unauthorized Access" with a 401 status code

Explanation: Tests that unauthorized requests are blocked early in the pipeline.

### Invalid Input Test:

URL: http://localhost:5294/?secure=true&input=<script>

Expected Output: "Invalid Input" with a 400 status code.

Explanation: This tests input validation by blocking unsafe input, such as JavaScript or HTML.

### Access Denied Test:

URL: Any URL without authentication setup, such as http://localhost:5294/?secure=true

Expected Output: "Access Denied" with a 403 status code.

Explanation: This middleware simulates access control, blocking unauthenticated requests by default.

### Security Event Log Test:

Trigger: Any request that results in a 400 or higher status code.

Expected Output: Check the console in Visual Studio Code for log messages like:
Security Event: /unauthorized - Status Code: 401

Explanation: This middleware logs security-related events, providing feedback on blocked or failed requests.


## Full code by file

```C#
using System;
using Microsoft.AspNetCore.Builder;
using Microsoft.Extensions.Hosting;
using Microsoft.AspNetCore.Http;
using System.Threading.Tasks;

var builder = WebApplication.CreateBuilder(args);

// Configure to listen on HTTP only for simplicity
builder.WebHost.ConfigureKestrel(options =>
{
    options.ListenLocalhost(5294); // HTTP only
});

var app = builder.Build();

// Middleware to log security events if response status indicates an issue
app.Use(async (context, next) =>
{
    await next(); // Run the next middleware first

    if (context.Response.StatusCode >= 400)
    {
        Console.WriteLine($"Security Event: {context.Request.Path} - Status Code: {context.Response.StatusCode}");
    }
});

// Simulated HTTPS Enforcement Middleware
app.Use(async (context, next) =>
{
    // Check for a query parameter to simulate HTTPS enforcement (e.g., "?secure=true")
    if (context.Request.Query["secure"] != "true")
    {
        context.Response.StatusCode = 400;
        await context.Response.WriteAsync("Simulated HTTPS Required");
        return;
    }

    await next();
});

// Middleware for input validation
app.Use(async (context, next) =>
{
    var input = context.Request.Query["input"];
    if (!IsValidInput(input))
    {
        if (!context.Response.HasStarted)
        {
            context.Response.StatusCode = 400;
            await context.Response.WriteAsync("Invalid Input");
        }
        return;
    }

    await next();
});

// Helper method for input validation
static bool IsValidInput(string input)
{
    // Checks for any unsafe characters or patterns, including "<script>"
    return string.IsNullOrEmpty(input) || (input.All(char.IsLetterOrDigit) && !input.Contains("<script>"));
}

// Middleware for short-circuiting unauthorized access
app.Use(async (context, next) =>
{
    if (context.Request.Path == "/unauthorized")
    {
        if (!context.Response.HasStarted)
        {
            context.Response.StatusCode = 401;
            await context.Response.WriteAsync("Unauthorized Access");
        }
        return; // Exit middleware pipeline early if unauthorized
    }
    await next();
});

// Middleware for simulated authentication and secure cookies
app.Use(async (context, next) =>
{
    // Simulate authentication with a query parameter (e.g., "?authenticated=true")
    var isAuthenticated = context.Request.Query["authenticated"] == "true";
    if (!isAuthenticated)
    {
        if (!context.Response.HasStarted)
        {
            context.Response.StatusCode = 403;
            await context.Response.WriteAsync("Access Denied");
        }
        return;
    }

    context.Response.Cookies.Append("SecureCookie", "SecureData", new CookieOptions
    {
        HttpOnly = true,
        Secure = true
    });

    await next();
});

// Middleware for asynchronous processing
app.Use(async (context, next) =>
{
    await Task.Delay(100); // Simulate async operation
    if (!context.Response.HasStarted)
    {
        await context.Response.WriteAsync("Processed Asynchronously\n");
    }
    await next();
});

// Final Response Middleware
app.Run(async (context) =>
{
    if (!context.Response.HasStarted)
    {
        await context.Response.WriteAsync("Final Response from Application\n");
    }
});

app.Run();
```

