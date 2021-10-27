// CLASS: FileReader
//
// Author: Eriq Hampton, 7852830
//
// REMARKS: I was told static code was bad
// so this FileReader class accepts the File and
// sends it to the CommandList interface for processing
// quits immediately when QUIT/END is entered.
// Terminates when there are no more commands left.
//-----------------------------------------
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class FileReader {
	private File file;

 public void FileReader() throws FileNotFoundException
{
	String quit = null;
	String filename = "";
	
	file = new File(filename);
	while(!file.exists())
	{
		String path = System.getProperty("user.dir")+"/";
		System.out.println("Please enter the name of your file. (With .txt included)");
		System.out.println("Ensure the file is located:" + path);
		
		Scanner scan = new Scanner(System.in);
		filename =  path + scan.next();
		file = new File(filename);
		
		if(!file.exists())
		{
			System.out.println("File not found, Try again.");
		}
		else
		{
			System.out.println("File found");
		}
	}
	
	Scanner sc = new Scanner(file);
	CommandList p = new CommandList();
	 
	while (sc.hasNextLine())
	 {		 
		 String i = sc.nextLine().trim();
		 
		 //Quit immediately
		 if(i.equals("END") || i.equals("QUIT"))  
		 { 
			 System.out.println("BYE");			
			 break;
		 }
        
		 //Process ever command
         p.commandList(i);
         if(!sc.hasNext())
         {
        	 System.out.println("System did not recieve a quit command");
        	 System.out.println("Terminating");
         }
	 }
}
}
