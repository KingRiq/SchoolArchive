import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import java.sql.SQLException;
import java.sql.PreparedStatement;

import java.io.FileReader;
import java.io.IOException;
import java.io.BufferedReader;
import java.util.Scanner;


public class CS3380A2Q5 {
    static Connection connection;

    public static void main(String[] args) throws Exception {
	
		// startup sequence
		MyDatabase db = new MyDatabase();		
		doStuff(db);

		
		System.out.println("Exiting...");
	}
	
	public static void doStuff(MyDatabase db){

		String name = "Snowball Grottobow";
		String link = "bz4bnJ77um";
		try{
			Scanner sc = new Scanner(System.in);
			System.out.println("Gimme an Elf name: ");
			String maybeName = sc.nextLine();
			System.out.println("Gimme a CheerTube link");
			String maybeLink = sc.nextLine();

			if (maybeName.length() > 0)
				name = maybeName;
			if (maybeLink.length() > 0)
				link = maybeLink;
			sc.close();
		}
		catch(Exception e){
			System.out.println("Using defaults, loser.");
		}

		db.getAccountForElfName(name);
		
	}


}

class MyDatabase{
	private Connection connection;
	private final String accountsTXT = "accounts.txt";
	private final String videosTXT = "videos.txt";
	private final String viewsTXT = "views.txt";

	public MyDatabase(){
		try {
			Class.forName("org.hsqldb.jdbcDriver");
			// creates an in-memory database
			connection = DriverManager.getConnection("jdbc:hsqldb:mem:mymemdb", "SA", "");

			createTables();
			readInData();
		}
		catch (ClassNotFoundException e) {
			e.printStackTrace(System.out);
		}
		catch (SQLException e) {
			e.printStackTrace(System.out);
		}
	}

	
	private void createTables(){
		// To be completed
		String accounts = "create table accounts ( "+
			" accountID integer,"+
            " billingAddress VARCHAR(100),"+
            " primary key(accountID)" +
			")";
		try {
            connection.createStatement().executeUpdate(accounts);

            String createBills = "create table bills ("
                + " billID integer," 
                + " amount integer,"
                + " accountID integer, "
                + "primary key(billID),"
                + " foreign key (accountID) references accounts);";

            connection.createStatement().executeUpdate(createBills);
		}
		catch (SQLException e) {
			e.printStackTrace(System.out);
		}

	}

	public void getAccountForElfName(String elfName){
		/*
		 * To be CORRECTED and completed. Just an example of how this can work. You will have to add more tables to the FROM statement
		 */
		System.out.println("Q1 - account for " + elfName);
		try{
			PreparedStatement pstmt = connection.prepareStatement(
				"Select * from accounts where billingAddress=?;"
			);
			pstmt.setString(1, elfName);

			ResultSet resultSet = pstmt.executeQuery();

			while (resultSet.next()) {
				// at least 1 row (hopefully one row!) exists. Get the ID
				int aID = resultSet.getInt("accountID");
				System.out.println(elfName + " is associated with account " + aID);
			}

			pstmt.close();
		}
		catch (SQLException e) {
			e.printStackTrace(System.out);
		}
	}

	private void readInData(){

		// to be corrected and completed
		
		BufferedReader in = null;

		try {
			in = new BufferedReader((new FileReader(accountsTXT)));
		
			// throw away the first line - the header
			in.readLine();

			// pre-load loop
			String line = in.readLine();
			while (line != null) {
				// split naively on commas
				// good enough for this dataset!
				String[] parts = line.split(",");
				if(parts.length >= 2)
					makeAccount(parts[0], parts[2]);
				
				// get next line
				line = in.readLine();
			}
			in.close();
		} catch (IOException e) {
			e.printStackTrace();
		}

		
	}

	private int makeAccount(String accountID, String billingAddress){
		/*
		 * Really make or create account. Return the account ID
		 * whether it is new, or give the existing one if it already exists
		 */
		int aID = -1;
		try{
			PreparedStatement pstmt = connection.prepareStatement(
				"Select accountID From  accounts where accountID = ?;"
			);
			pstmt.setInt(1, Integer.parseInt(accountID));

			ResultSet resultSet = pstmt.executeQuery();

			if (resultSet.next()) {
				// at least 1 row (hopefully one row!) exists. Get the ID
				aID = resultSet.getInt("accountID");			
			}
			else{
				// no record
				// make the new account
                PreparedStatement addAccount = connection.prepareStatement(
					"insert into accounts (accountID, billingAddress) values (?, ?);"
				);
                
                addAccount.setInt(1, Integer.parseInt(accountID) );
                addAccount.setString(2, billingAddress);
                int numUpdated= addAccount.executeUpdate();
                
				addAccount.close();
            
				resultSet.close();
			}
			pstmt.close();
		}
		catch (SQLException e) {
			System.out.println("Error in " + accountID + " " +billingAddress);
			e.printStackTrace(System.out);
		}

		return aID;
	}

}
