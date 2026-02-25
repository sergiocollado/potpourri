# Entity Framework Core (EF Core)

## Introduction 

This text explains how Object-Relational Mapping (ORM) bridges object-oriented programming with relational databases and highlights Entity Framework Core (EF Core) as a powerful ORM tool for .NET applications.

Key Concepts:
 - Relational Databases & SQL: Relational databases organize data into structured tables of rows and columns, and SQL (Structured Query Language) is used to manage and retrieve this data efficiently.
 - Object-Oriented Programming & Data Mismatch: In object-oriented languages, data is represented as objects, which creates a mismatch with databases storing data in tables. ORM addresses this by linking objects in code with relational tables, reducing the need for manual SQL queries.
 - ORM: ORM is a technique that automatically translates data between object-oriented code and relational databases. It enables developers to manipulate data as objects rather than writing SQL, reducing the risk of errors and the complexity of managing data.

### Overview and Features of EF Core

EF Core: EF Core is an open-source ORM tool in the .NET ecosystem. It enables developers to interact with relational databases using C# objects, simplifying code by eliminating direct SQL queries.

Key Features of EF Core:
 - LINQ (Language Integrated Query): Integrates query capabilities directly into C# code, making queries type-safe and readable.
 - Database Migrations: Allows the database schema to evolve alongside application development, supporting changes like table additions or modifications.
 - Change Tracking: Automatically tracks changes made to objects, streamlining updating the database when data changes.
 - Advantages of EF Core EF Core offers ease of use, flexibility, and maintainability. It enables database interactions through C# objects, reducing SQL complexity, supporting multiple databases (such as SQL Server, PostgreSQL, and SQLite), and improving scalability.

### Conclusion 

ORM techniques and EF Core simplify backend development by enabling smoother database interactions, reducing code complexity, and supporting application growth.
