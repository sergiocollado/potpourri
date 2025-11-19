// See https://aka.ms/new-console-template for more information

public class Program
{
	
    public async Task DownloadDataAsync()
    {
        try
        {
            Console.WriteLine("Download started...");
            // throw new InvalidOperationException("Simulated download error."); // uncomment for simulate an error
            await Task.Delay(3000);
            Console.WriteLine("Download completed.");
        }
        catch (Exception ex)
        {
            Console.WriteLine("An error occurred: " + ex.Message);
        }
    }

    public async Task DownloadDataAsync2()
    {
        Console.WriteLine("Download 2 started...");
        await Task.Delay(2000);
        Console.WriteLine("Download 2 completed.");
    }

    public static async Task Main(string[] args)
    {
        Program program = new Program();
        Task task1 = program.DownloadDataAsync();
        Task task2 = program.DownloadDataAsync2();
        await Task.WhenAll(task1, task2);
        Console.WriteLine("All downloads completed.");
    }
}

