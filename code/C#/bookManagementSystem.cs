// See https://aka.ms/new-console-template for more information

public class BookManager
{


    const int booksListSize = 5;
    public static int bookCount = 0;

    public static string[] bookList = new string[booksListSize];

    public static void BookListInit()
    {
        for (int i=0; i < booksListSize; i++)
        {
            bookList[i] = string.Empty;
        }
    }

   public static void AddBook()
    {
        if (bookCount < booksListSize)
        {
            Console.WriteLine("Enter a new book:");
            var bookName = Console.ReadLine();
            if (bookName != null)
            {
                for (int i = 0; i < booksListSize; i++)
                {
                    if (bookList[i] == string.Empty)
                    {
                        bookList[i] = bookName;
                        bookCount++;
                        Console.WriteLine(">> Added book: " + bookName + "\n\n");
                        break;
                    }
                }
            }
            else
            {
                Console.WriteLine("Not valid empty line\n\n");
            }
        }
        else
        {
            Console.WriteLine("Max book list size reached. Cannot add any more books to the list\n\n");
        }
    }

    public static void RemoveBook()
    {
        if (bookCount > 0)
        {
            Console.WriteLine("Enter index of the book to remove:");
            ViewBooks();
            var inputString = Console.ReadLine();
            if (inputString != null)
            {
                if (Int32.TryParse(inputString, out int numValue))
                {  
                    int index = numValue;
                    if (index > 0 && index <= booksListSize)
                    {
                        if( bookList[index-1] != string.Empty)
                        {
                            string bookName =  bookList[index-1];
                            bookList[index-1] = string.Empty;
                            bookCount--;
                            Console.WriteLine(">> Removed book: " + bookName);
                            if (bookCount == 0)
                            {
                                Console.WriteLine(">> The list is empty!");
                            }
                            Console.WriteLine("\n\n");
                        }
                        else
                        {
                            Console.WriteLine(">> Not valid index for removing a book\n\n");
                        }
                    }
                    else
                    {
                         Console.WriteLine(">> " + index.ToString() + "is not valid index for removing a book\n\n");
                    }
                }
                else
                {
                    Console.WriteLine($"Int32.TryParse could not parse '{inputString}' to an int.\n\n");
                }
            }
            else
            {
                Console.WriteLine("Not valid empty line\n\n");
            }
        }
        else
        {
             Console.WriteLine("Not books to remove. The list is empty\n\n");
        }
    }

    public static void ViewBooks()
    {
        for (int i = 0; i < booksListSize; i++)
        {
            if (bookList[i] != string.Empty)
            {
                Console.WriteLine((i + 1) + ". " + bookList[i]);
            }
        }
    }

    public static void Main(string[] args)
    {
        bool running = true;
        BookListInit();

        while (running)
        {
            Console.WriteLine("What would you like to do?");
            Console.WriteLine("1. Add a book");
            Console.WriteLine("2. Remove a book");
            Console.WriteLine("3. View books");
            Console.WriteLine("4. Exit");
            Console.WriteLine("\n\n");

            var inputString = Console.ReadLine();
            if (Int32.TryParse(inputString, out int choice))
            { 
                switch (choice)
                {
                    case 1:
                        AddBook();
                        Console.WriteLine("\n\n");
                        break;
                    case 2:
                        RemoveBook();
                        Console.WriteLine("\n\n");
                        break;
                    case 3:
                        Console.WriteLine("List of books (" + bookCount.ToString() + "):");
                        if (bookCount != 0)
                        {
                            ViewBooks();
                        }
                        else
                        {
                            Console.WriteLine("The list of books is empty\n\n");
                        }
                        Console.WriteLine("\n\n");
                        break;
                    case 4:
                        running = false;
                        Console.WriteLine("Bye bye!");
                        Console.WriteLine("\n\n");
                        break;
                    default:
                        Console.WriteLine("Invalid choice. Please try again.\n\n");
                        Console.WriteLine("\n\n");
                        break;
                }
            }
            else
            {
                if (inputString != string.Empty)
                {
                    Console.WriteLine($"Read input error: Int32.TryParse could not parse '{inputString}' to an valid index.\n\n");
                }
                else
                {
                    Console.WriteLine("\n\n");
                }
            }
        }
    }

}
