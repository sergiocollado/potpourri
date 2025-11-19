// See https://aka.ms/new-console-template for more information

public class Person
{
    public string Name { get; set; }
    public int Age { get; set; }

    // Define the Greet method
    public void Greet()
    {
        Console.WriteLine("Hello, my name is " + Name);
    }
}

public class Program
{
    public static void Main(string[] args)
    {
        // Create the first Person object
        Person friend = new Person();
        friend.Name = "John Doe";
        friend.Age = 30;

        // Create the second Person object
        Person colleague = new Person();
        colleague.Name = "Jane Smith";
        colleague.Age = 25;

        // Call the Greet method on each object
        friend.Greet(); // Output: Hello, my name is John Doe
        colleague.Greet(); // Output: Hello, my name is Jane Smith
    }
}
