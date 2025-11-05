# Project Creation

## Introduction

This guide will walk you through the steps to create a new .NET project in Visual Studio Code, from opening the necessary tools to running your first program.
Steps to Create a New .NET Project

    Open the command palette

        Press Ctrl+Shift+P (Windows) or Cmd+Shift+P (Mac) in Visual Studio Code.

    Start a new .NET project

        Type “.NET new project” into the Command Palette and select the option from the list.

    Choose a project template

        Pick the type of project you want to create (e.g., Console Application or Web Application). For a simple start, select “Console Application.”

    Select the project folder

        Choose the folder where you want to save your new project and click "Select Folder."

    Name your project

        Enter a name for your project. A new folder with this name will be created in your chosen directory.

    Trust the project files

        When prompted, click “Trust the authors” to allow Visual Studio Code to use the new files.

    View your project files

        Open the Explorer panel in Visual Studio Code to see the newly created files, such as Program.cs.

    Run your project

        Open the terminal, type dotnet run, and press Enter to run your new .NET project. You should see “Hello World” displayed in the terminal.

## Conclusion

By following these steps, you've successfully created and run a new .NET project in Visual Studio Code. This foundational knowledge will help you as you continue to develop more complex applications.

# Project settings

## Introduction

Follow these steps to configure the initial settings for a new .NET project to ensure its smooth and efficient operation.
Steps to Configure Initial Project Settings

    Locate the .csproj file

        Open the project folder and find the .csproj file. This file configures how the project handles running, testing, and building.

    Understand the .csproj file

        The .csproj file uses XML format. Tags define settings like project type (<Project Sdk="Microsoft.NET.Sdk">) and target framework (e.g., <TargetFramework>net8.0</TargetFramework>).

    Manage project dependencies

        Use the NuGet Package Manager to add and manage dependencies. Open the command palette and select "Add NuGet Package," then search for the desired package (e.g., "Pastel") and choose the latest version.

    Verify the .csproj file after adding packages

        Check the .csproj file to confirm the new packages are listed under <PackageReference>.

    Utilize new packages in code

        For example, to use the "Pastel" package, add using Pastel; in your code. Then, implement it to customize text colors (e.g., color.Green).

## Conclusion

These steps will help you effectively set up your .NET project, ensuring that all settings and dependencies are properly configured from the start.
