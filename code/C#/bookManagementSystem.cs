// See https://aka.ms/new-console-template for more information
// https://learn.microsoft.com/en-us/dotnet/core/tutorials/with-visual-studio-code
// dotnet new console -n bookManagementSystem
// cd bookManagementSystem
// dotnet run
// https://learn.microsoft.com/en-us/dotnet/core/tutorials/debugging-with-visual-studio-code


using System.Runtime.ExceptionServices;

public class BookManager
{

    const int booksListSize = 5;
    public static int bookCount = 0;

    public static string[] bookList = new string[booksListSize];
    public static bool[] checkoutList = new bool[booksListSize];
    public static int borrowLimit = 3;
    public static string[] borrowedBooksList = new string[borrowLimit];

    public static int borrowedBooks = 0;

    public static void BookListInit()
    {
        for (int i=0; i < booksListSize; i++)
        {
            bookList[i] = string.Empty;
        }

        for (int i=0; i < borrowLimit; i++)
        {
            checkoutList[i] = false;
        }

        borrowedBooks = 0;
    }

   public static void AddBook()
    {
        if (bookCount < booksListSize)
        {
            Console.WriteLine("Enter a new book:");
            var bookName = Console.ReadLine();
            if (bookName != null)
            {
                bookName = bookName.Trim();
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

    public static bool RemoveBook(int index)
    {
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
                    return false;
                }
                Console.WriteLine("\n\n");
                return true;
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
        return false;
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
                        RemoveBook(index);
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
                Console.WriteLine((i + 1) + ". " + bookList[i] + (checkoutList[i] ? " (checked out)": ""));
            }
        }
    }

    public static void ViewBorrowedBooks()
    {
        for (int i = 0; i < booksListSize; i++)
        {
            if ( checkoutList[i] == true) // borrowedBooksList[i].Trim() != string.Empty &&
            {
                Console.WriteLine((i + 1) + ". " + bookList[i]);
            }
        } 
    }

    public static void SearchBook()
    {
        Console.WriteLine("Input the name of the book to search for:");
        var inputString = Console.ReadLine();
        bool bookFound = false;
        if (inputString != null)
        {
            string bookName = inputString.Trim();
            for (int i = 0; i < booksListSize; i++)
            {
                if (bookList[i] != string.Empty)
                {
                    if (bookList[i] == bookName )
                    {
                        Console.WriteLine("> book: \'" + bookName + "\' found\n\n");
                        bookFound = true;
                        break;
                    }
                }
            }
            if (bookFound == false)
            {
                 Console.WriteLine("> book: \'" + bookName + "\' not found\n\n");
            }
        }
        else
        {
            Console.WriteLine("Not valid empty line\n\n");
        }
    }

    public static bool BorrowBook(string bookName)
    {
        if (borrowedBooks < borrowLimit)
        {
            for(int i = 0; i < borrowLimit; i++)
            {
                if(!string.IsNullOrWhiteSpace(borrowedBooksList[i]))
                {
                    borrowedBooksList[i] = bookName;     // add it to the list of borrowed books
                    checkoutList[i] = true;              // mark it as checked out
                    borrowedBooks++;                     // add +1 to the borrowed books
                    return true;
                }
            }
        }
        return false;
    }

    public static void BorrowBook()
    {
        if (borrowedBooks <= borrowLimit)
        {
            Console.WriteLine("Input the index of the book to borrow\n");
            ViewBooks();
            var inputString = Console.ReadLine();
            if (inputString != null)
            {
                if (Int32.TryParse(inputString, out int numValue))
                {
                    if(BorrowBook(bookList[numValue-1]) == true)
                    {
                        Console.WriteLine("borrowed book: " + inputString + "\n");
                    }
                    else
                    {
                        Console.WriteLine("> Cannot borrow a new book, you already have borrowed the maximum number of books: " + borrowLimit.ToString());
                    }
                }
            }
        }
        else
        {
            Console.WriteLine("> Cannot borrow a new book, you already have borrowed the maximum number of books: " + borrowLimit.ToString());
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
            Console.WriteLine("4. Search book");
            Console.WriteLine("5. Borrow book");  
            Console.WriteLine("6. view borrowed book");            
            Console.WriteLine("7. Exit");
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
                        SearchBook();
                        Console.WriteLine("\n\n");
                        break;     
                    case 5:
                        BorrowBook();
                        Console.WriteLine("\n\n");
                        break;   
                    case 6:
                        ViewBorrowedBooks();   
                        Console.WriteLine("\n\n");
                        break;                                     
                    case 7:
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
