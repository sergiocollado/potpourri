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


