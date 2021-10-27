import java.util.*;
import java.io.*;

public class tolower
{
  public static void main( String args[] )
  {
    String read_line;
    InputStreamReader theFile;
    BufferedReader in;

    // read the document 1 line at a time
    try
    {
      theFile = new InputStreamReader( System.in );
      in      = new BufferedReader( theFile );

      // process each line in turn
      read_line = in.readLine();
      while ( read_line != null )
      {
        System.out.println( read_line.toLowerCase() );
        // get the next word to process
        read_line = in.readLine();
      }

      in.close();
    }

    catch( IOException ex )
    {
      System.out.println( "I/O error: " + ex.getMessage() );
    }
  }
}

