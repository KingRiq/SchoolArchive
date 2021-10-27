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


public class A3P2 {
    static Connection connection;

    public static void main(String[] args) throws Exception {
	
		// startup sequence
		MyDatabase db = new MyDatabase();		
		runConsole(db);

		System.out.println("Exiting...");
	}
	
	public static void runConsole(MyDatabase db){

		Scanner console = new Scanner(System.in);

		System.out.print("db > ");
		String line = console.nextLine();
        String [] parts;
        String arg = "";

		while(line != null && !line.equals("q")){
            parts = line.split("\\s+");
            if (line.indexOf(" ") > 0)
                arg = line.substring(line.indexOf(" ")).trim();
			if (parts[0].equals("h"))
				printHelp();
			else if (parts[0].equals("w")){
				db.allWards();
			}
			else if (parts[0].equals("c")){
				db.allCouncilors();
			}
			else if (parts[0].equals("e")){
				db.allExpenses();
			}
			else if (parts[0].equals("wt")){
				try{
					if (parts.length >= 2)
						db.singleWard(arg);
					else
						System.out.println("Require an argument for this command");
				} catch(Exception e){
					System.out.println("id must be an integer");
				}
			}
			else if (parts[0].equals("ct")){
				if (parts.length >= 2)
					db.singleCouncilor(arg);
				else
					System.out.println("Require an argument for this command");
			}
			else if (parts[0].equals("de")){
				try {
					if (parts.length >= 2 )
						db.deleteExpense(arg);
					else
						System.out.println("Require an argument for this command");
				} catch(Exception e){
					System.out.println("id must be an integer");
				}
			}
			else if (parts[0].equals("dc")){
				if (parts.length >= 2 )
					db.deleteCouncilor(arg);
				else
					System.out.println("Require an argument for this command");
			}
			else if (parts[0].equals("m")){
				db.highestExpense();
			}
			else
				System.out.println("Read the help with h, or find help somewhere else.");

			System.out.print("db > ");
			line = console.nextLine();
		}

		console.close();
	}

	private static void printHelp(){
		System.out.println("Winnipeg Council Member Expenses console");
		System.out.println("Commands:");
		System.out.println("h - Get help");
		System.out.println("w - Print all wards");
		System.out.println("c - Print all coucillors");
		System.out.println("ct name - Print total expenses for councilors 'name'");
		System.out.println("wt name - Print total expenses for ward 'name'");
		System.out.println("dc name - Delete councilors named 'name'");
		System.out.println("de id - delete expense 'id'");
		System.out.println("m - Show the highest single-time expense for each councilors");
		System.out.println("q - Exit the program");

		System.out.println("---- end help ----- ");
	}
}

class MyDatabase{
	private Connection connection;
	private final String filename = "Council_Member_Expenses.csv";
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

	public void allCouncilors() {
		try {
			String sql = "Select * from councilors;";

			Statement statement = connection.createStatement();
			ResultSet resultSet = statement.executeQuery(sql);

			while (resultSet.next()) {
				System.out.println(resultSet.getInt("cID") + ": " + resultSet.getString("name"));
				
			}
			resultSet.close();
			statement.close();


		}catch (SQLException e) {
				e.printStackTrace(System.out);
		}
	}

	public void allExpenses(){
		// Works, but the table must be corrected!
		try {
            String sql = "Select eID, councilors.name as cname, wards.name as wname," +
             " description, amount from councilors join  expenses" +
             " on councilors.cID = expenses.cID" +
             " join wards on wards.wardID = councilors.wardID";

			Statement statement = connection.createStatement();
			ResultSet resultSet = statement.executeQuery(sql);

			while (resultSet.next()) {
                System.out.println(resultSet.getInt("eID") + " - " + resultSet.getString("wname") + " " + resultSet.getString("cname") + ", " + resultSet.getString("description") + ":" + resultSet.getDouble("amount"));
				
			}
			resultSet.close();
			statement.close();


		}catch (SQLException e) {
				e.printStackTrace(System.out);
		}
	}

	public void singleCouncilor(String name) {
		try {

            String sql = 
                "select name as name, sum(amount) as amount from councilors"+
                " join expenses on councilors.cID = expenses.cID " +
                " where name = '"+name+"'" +
                " group by name;"
			;
			
            Statement statement = connection.createStatement();
			ResultSet resultSet = statement.executeQuery(sql);

            while (resultSet.next()) {
                System.out.println(resultSet.getString("name") + ":" + resultSet.getDouble("amount"));
            }
            resultSet.close();
            statement.close();
        }catch (SQLException e) {
            e.printStackTrace(System.out);
        }
	}

	public void singleWard(String wardName) {
		try {
            PreparedStatement getSingle = connection.prepareStatement(
                "select wards.name as name, sum(amount) as amount from wards join councilors on wards.wardID = councilors.wardID "+
                " join expenses on councilors.cID = expenses.cID " +
                " where wards.name = ?" +
                " group by wards.name;"
            );
            getSingle.setString(1, wardName);

            ResultSet resultSet =  getSingle.executeQuery();
            while (resultSet.next()) {
                System.out.println(resultSet.getString("name") + ":" + resultSet.getDouble("amount"));
            }
            resultSet.close();
            getSingle.close();
        }catch (SQLException e) {
            e.printStackTrace(System.out);
        }
	}

	public void deleteExpense(String expenseID){
		try {
            String sql = "delete from expenses where eID = "+expenseID+";";
			
			Statement statement = connection.createStatement();
			ResultSet resultSet = statement.executeQuery(sql);
            statement.close();
        }catch (SQLException e) {
            e.printStackTrace(System.out);
        }
	}

	public void deleteCouncilor(String name){
        try {
            String sql = "delete from councilors where name = '"+name+"';";
            Statement statement = connection.createStatement();
			statement.execute(sql);
			statement.close();
        }catch (SQLException e) {
            e.printStackTrace(System.out);
        }
	}

	public void highestExpense() {
		try {
            String sql = "Select name, max(amount) as amount from councilors join expenses" +
            " on councilors.cID = expenses.cID " + 
            " group by councilors.name;";

			Statement statement = connection.createStatement();
			ResultSet resultSet = statement.executeQuery(sql);

			while (resultSet.next()) {
				System.out.println(resultSet.getString("name") + ": " + resultSet.getDouble("amount"));
				
			}
			resultSet.close();
			statement.close();


		}catch (SQLException e) {
				e.printStackTrace(System.out);
		}
	}

	private void createTables(){
		// To be completed
		String wards = "create table wards ( "+
			" wardID integer,"+
            " name VARCHAR(60),"+
            " primary key(wardID)" +
			")";
		try {
            connection.createStatement().executeUpdate(wards);

            String createCouncilor = "create table councilors ("
                + " cID integer IDENTITY," 
                + " wardID integer,"
                + " name VARCHAR(60), "
                + "primary key(cID),"
                + " foreign key (wardID) references wards);";

            connection.createStatement().executeUpdate(createCouncilor);

            String createExpense = "create table expenses ("+
                " eID integer IDENTITY," +
                " cID integer," +
                " description VARCHAR(200), " +
                " account VARCHAR(60), " +
                " amount DECIMAL," +
                " primary key (eID, cID)," +
                " foreign key (cID) references councilors on delete cascade);" ;
            connection.createStatement().executeUpdate(createExpense);

		}
		catch (SQLException e) {
			e.printStackTrace(System.out);
		}

	}

	public void allWards() {
		// Works, but the table must be corrected!
		try {
			String sql = "Select * from wards;";

			Statement statement = connection.createStatement();
			ResultSet resultSet = statement.executeQuery(sql);

			while (resultSet.next()) {
				System.out.println(resultSet.getInt("wardID") + ": " + resultSet.getString("name"));
				
			}
			resultSet.close();
			statement.close();


		}catch (SQLException e) {
				e.printStackTrace(System.out);
		}
    }
    
    private int getOrMakeWard(String wardId, String wardName) {
        /* See if ward exists, create it if it doesn't
        Return the id regardless of existance */
        int wardID = -1;
        try {
			PreparedStatement pstmt = connection.prepareStatement(
					"Select * From  wards where wardID = ?;"
				);
            pstmt.setInt(1, Integer.parseInt(wardId));

            ResultSet resultSet = pstmt.executeQuery();

			if (resultSet.next()) {
                // at least 1 row (hopefully one row!) exists. Get the ID
				wardID = resultSet.getInt("wardID");			
            }
            else {
                // make the new ward
                PreparedStatement addWard = connection.prepareStatement(
					"insert into wards (wardID, name) values (?, ?);"
                );
                wardID = Integer.parseInt(wardId);
				addWard.setInt(1, wardID);
				addWard.setString(2, wardName);

                addWard.executeUpdate();
                addWard.close();
            }

			resultSet.close();
			pstmt.close();


		}catch (SQLException e) {
				e.printStackTrace(System.out);
		}

        return wardID;
    }


    private int getOrMakeCouncilor(String name, int wardID) {
        int cID = -1;
        try {
			PreparedStatement pstmt = connection.prepareStatement(
					"Select cID From  councilors where name = ?;"
				);
            pstmt.setString(1, name);

            ResultSet resultSet = pstmt.executeQuery();

			if (resultSet.next()) {
                // at least 1 row (hopefully one row!) exists. Get the ID
				cID = resultSet.getInt("cID");			
            }
            else {
                // make the new ward
                PreparedStatement addCouncil = connection.prepareStatement(
                    "insert into councilors (name, wardID) values (?, ?);",
                    Statement.RETURN_GENERATED_KEYS
                );
                
                addCouncil.setString(1, name);
                addCouncil.setInt(2, wardID);
                int numUpdated= addCouncil.executeUpdate();
                ResultSet keys = addCouncil.getGeneratedKeys();
                if (keys.next())
                    cID = keys.getInt(1);
                addCouncil.close();
            }
			resultSet.close();
			pstmt.close();


		}catch (SQLException e) {
				e.printStackTrace(System.out);
		}

        return cID;
    }

	private void readInData(){

		// to be corrected and completed
		
		BufferedReader in = null;
		String addition;

		try {
			in = new BufferedReader((new FileReader(filename)));
		
			// throw away the first line - the header
			in.readLine();

			// pre-load loop
			String line = in.readLine();
			while (line != null) {
				// split naively on commas
				// good enough for this dataset!
				String[] parts = line.split(",");
                
                int wardID = getOrMakeWard(parts[0], parts[1]);

                int councilorId = getOrMakeCouncilor(parts[2], wardID);
				// prepared statement:
				// see
                // http://hsqldb.org/doc/2.0/apidocs/org/hsqldb/jdbc/JDBCPreparedStatement.html
                
                // add the expense
                PreparedStatement addExpense = connection.prepareStatement(
                    "insert into expenses  (cID, description, account, amount)" +
                    " values (?, ?, ?, ?);"
                );
                addExpense.setInt(1, councilorId);
                int length = parts.length;
                addExpense.setString(2, parts[length - 3]);
                addExpense.setString(3, parts[length - 2]);
                addExpense.setDouble(4, Double.parseDouble(parts[length - 1]));

                addExpense.executeUpdate();
                addExpense.close();

				
				// get next line
				line = in.readLine();
			}
			in.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
		catch (SQLException e) {
			e.printStackTrace(System.out);
		}
	}
}
