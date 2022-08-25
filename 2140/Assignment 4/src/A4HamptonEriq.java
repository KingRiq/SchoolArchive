 /************************************************
 * COMP 2140   SECTION A01
 * INSTRUCTOR    Cuneyt Akcora
 * Assignment           4
 * @author       Eriq Hampton
 * @version      03/20/20
 *
 * PURPOSE: Create a spellchecker using tables
 *********************************************/
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;

public class A4HamptonEriq 
{
	
	public static void main(String[] args) throws IOException 
	{
		File file, file2;
		Scanner scanner = new Scanner(System.in);
		String dictionaryFilePath;
		String textFilePath; 
		boolean fileCheck = false;
	
		do
		{
			System.out.println("Please enter the complete path of the dictionary file");
			System.out.println("For example /Users/Documents/textfile.txt");
			dictionaryFilePath = scanner.nextLine(); 
			file = new File(dictionaryFilePath);
			fileCheck = file.exists();
		
			if(!fileCheck)
				System.out.println("file does not exist, please try again.");
	
		}while(!fileCheck);
	
	
		fileCheck = false;
	
		do
		{
			System.out.println("Please enter the path of the file that should be spell checked");
			textFilePath = scanner.nextLine();
			file2 = new File(textFilePath);
			fileCheck = file2.exists();
		
			if(!fileCheck)
				System.out.println("file does not exist, please try again.");
		
		}while(!fileCheck);
	
		scanner.close();
		spellChecker(file, file2);	
	
		System.out.println("\nProcessing Complete!");

	}
	
	/******************************************************************
    *
    * spellchecker
    *
    * Parameters: Accepts two files one as a dictionary that is entered 
    * into a table and used to compare the words in the 2nd file. If
    * the 2nd file has words that are not in the first table, they are considered
    * a spelling error and entered into a 2nd table which contains 
    * the lines the errors occurred. Lastly, it calls a print log method
    *
    *****************************************************************/
	static void spellChecker(File dictionary, File spellCheck) throws FileNotFoundException, IOException 
	{
	
		int tableSize = 9431;
		String line;
	    int i = 1;
	    String[] text;
	    boolean hasNextLine;
	    
	    
		TableWithQueue dictionaryTable = new TableWithQueue(tableSize);
		tableSize = 2797;
		TableWithQueue spellcheck = new TableWithQueue(tableSize);
	    
	    try (BufferedReader readin = new BufferedReader(new FileReader(dictionary))) 
	    { 
	    	hasNextLine = false;
	    	
	    	while((line =readin.readLine()) != null) 
	    	{
	    		text = line.toLowerCase().trim().split( "[^a-zA-Z']+" );
	    		
	    		for(int j = 0; j < text.length; j++)
	    			dictionaryTable.insert( text[j] );
	    			
	    	}
	    	
	    	
	    }
	    
	    try (BufferedReader readin = new BufferedReader(new FileReader(spellCheck))) 
	    {  
	    	hasNextLine = false;
	    	
	    	while((line =readin.readLine()) != null) 
	    	{
	    		text = line.toLowerCase().trim().split( "[^a-zA-Z']+" );
	    		
	    		for(int j = 0; j < text.length; j++)
	    			if ( !dictionaryTable.search( text[j] ) && !text[j].isBlank())
	    				spellcheck.insert(text[j], i);
	    		
	    		i++;
	    	}
	    	spellcheck.printTable();
	  
	    }
	}

}


 /************************************************************************************************
 * 
 * TableWithQueue
 * 
 * creates a table containing an array of linkedlists where every node 
 * contains a queue that is not initialized unless specified.
 * For this case, it is for entering incorrect words and the line numbers at which they occur.
 * 
 ************************************************************************************************/
class TableWithQueue 
{
    private Node[] hashArray;
    int numberItems; 
    private static final int A = 31; 
	
    public class Node 
    {
    	public String item;
    	public Node next;
    	public Queue lineNum;

    	public Node( String newItem, Node newNext) 
    	{
    		item = newItem;
    		next = newNext;
    	} 
	
    } // end class Node
    

    
    public TableWithQueue( int tableSize ) 
    {
    	numberItems = 0;
    	hashArray = new Node[ tableSize ];
    	
    	for ( int i = 0; i < hashArray.length; i++ ) 
    	    hashArray[ i ] = null;	
    }
        
    /*****************************************************************
    *
    * hash
    *
    * Hashes key and returns the resulting array index.
    *
    * The hash function uses the polynomial hash code
    * implemented using Horner's method.
    *
    *****************************************************************/
        
    private int hash( String key ) 
    {
    	int hashIndex = 0;

    	for ( int i = 0; i < key.length(); i++ ) 
    	{
    	    hashIndex = (hashIndex * A ) % hashArray.length + (int) key.charAt(i);
    	    hashIndex = hashIndex % hashArray.length;
    	}

    	return hashIndex;
    } 
        
    /******************************************************************
    *
    * insert
    *
    * Inserts key into the table (except if key is already in the table).
    * 
    * Parameters: accepts a string that will be stored in a node.
    * 
    *****************************************************************/
    public void insert( String key ) 
    {
    	int hashIndex;
       
    	// First, hash the key to find the starting index.
    	hashIndex = hash( key );
    	Node top = hashArray[hashIndex];
    	Node curr = top;
       	    
    	// Find an empty spot.
    	// Stop and abort if you find key
    	while ( curr != null && !curr.item.equals( key ) )
       	    	curr = curr.next;
       	    
       	    if (!search(key))      	    
       	    	//insert node with index
       	    	insertNode(hashIndex, key);
  
       	    
       	    // else do nothing because we do not want duplicates inserted 
       	    
       	}
       
    /******************************************************************
    *
    * insert
    *
    * Inserts key into the table (except if key is already in the table).
    * Initializes the queue when it inserts the key storing its line number
    *	 
    * Parameters: accepts a string that will be stored in a node.
    * and an integer indicating the line number it is located at
    * on its respective textfile.
    * 
    *****************************************************************/
        
    public void insert( String key, int lineNum ) 
    {
    	int hashIndex;
          	
    	// First, hash the key to find the starting index.
    	hashIndex = hash( key );
        Node top = hashArray[hashIndex];
        Node curr = top;
          	    
          	// Find an empty spot.    
          	// Stop and abort if you find key
          	while ( curr != null && !curr.item.equals( key ) ) 
          		curr = curr.next;
          	
          	if (!search(key) ) 
          	{
          		// insert node with index
          		// then initialize queue and enter the line number into it.
          		insertNode(hashIndex, key);
          		hashArray[hashIndex].lineNum = new Queue();
          		hashArray[hashIndex].lineNum.enter(lineNum);
       
          	}
          	
          	else if(curr.item.equals(key))
          	{
          		// We found a duplicate already in the table.
          	    curr.lineNum.enter(lineNum);
          		
          	} 
       }
       
       
       public void insertNode(int hashIndex, String key)
       {
    	   Node newNode= new Node(key, null);
    	   
    	   //insert at the top
    	   if(hashArray[hashIndex]== null)
    	   {
    		   hashArray[hashIndex]= newNode;
    	   }
    	   else
    	   {
    		   newNode.next = hashArray[hashIndex];
    		   hashArray[hashIndex]= newNode;
    	   }
    	   numberItems++;
       	}
       
       /******************************************************************
       *
       * search
       *
       * Searches the table for key, and returns true if key is found,
       * false if it isn't.
       *
       *****************************************************************/
       public boolean search( String key ) 
       {
    	   int hashIndex = hash( key );    	  
    	   Node curr = hashArray[hashIndex];
    	   boolean foundKey = false;

    	   while ( curr != null && !foundKey ) 
    	   {
    		   foundKey = curr.item.equals( key );
    		   curr = curr.next;
   	
    	   } 

    	   return foundKey;
       }
       
       /******************************************************************
       *
       * printTable
       *
       * prints the contents of the table. If the queue exists it will
       * submit all of the lines the word occurred on.
       *
       *****************************************************************/       
       public void printTable()
       {
    	   System.out.println("\nThere are a total of " + numberItems
    			   + " distinct invalid words");
    	   
    	   for(int p=0; p < hashArray.length; p++)
	    	{
    		   Node curr = hashArray[p];
	    			
	    			while(curr !=null)
	    			{
	    				System.out.print("\nInvalid word \""+curr.item +"\" found on lines " );
	    				
	    				while(curr.lineNum != null && !curr.lineNum.isEmpty())
	    				{	
	    					System.out.print(curr.lineNum.leave()+" ");
	    				}
	    				
	    				curr = curr.next;
	    			}
	    		
	    	}  
       }
}// end class TableWithQueue


class Queue
{
  private class Node
  {
    public int item;
    public Node next;

    public Node(int newItem, Node newNext)
    {
      item = newItem;
      next = newNext;
    }
  }

  private Node last;

  public Queue()
  {
    last = null; 
  }

  //adds nodes at the end
  public void enter( int newItem )
  {
    if ( last == null ) 
    {
      last = new Node( newItem, null );
      last.next = last; // the only node points at itself
    }
    else
    {
      last.next = new Node( newItem, last.next ); 
      last = last.next; 
    }
  } 

  public int leave( )
  {
    int result = Integer.MIN_VALUE;

    if ( last != null ) 
    {
      result = last.next.item; 
      if (last.next != last) 
      {
        last.next = last.next.next; 
      }
      else 
      {
        last = null;
      }
    }
    return result;
  } 

  // for debugging only
  public int front()
  {
    int result = Integer.MIN_VALUE;

    if ( last != null ) 
    {
      result = last.next.item; 
    }
    return result;
    
  } 

  public boolean isEmpty()
  {
    return last == null;
  }

}// end class Queue






