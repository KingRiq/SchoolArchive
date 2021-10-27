import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import java.sql.SQLException;
import java.sql.PreparedStatement;

public class CS3380A1 {
	static Connection connection;

	public static void main(String[] args) throws Exception {
	
		// startup sequence
		MyDatabase db = new MyDatabase();		

		
		db.showAll();
		db.getStaffMember(50);
		db.getStaffMember(1);
		db.getManager(10);

		System.out.println("Exiting...");
		db.shutdown();
	}
}

class MyDatabase{
	private Connection connection;
	public MyDatabase(){
		try {
			Class.forName("org.hsqldb.jdbcDriver");
			// creates an in-memory database
			//connection = DriverManager.getConnection("jdbc:hsqldb:mem:mymemdb", "SA", "");
			connection = DriverManager.getConnection("jdbc:hsqldb:file:staff;readonly=true","SA","");
			//connection = DriverManager.getConnection("jdbc:hsqldb:file:staff","SA","");

		}
		catch (ClassNotFoundException e) {
			e.printStackTrace(System.out);
		}
		catch (SQLException e) {
			e.printStackTrace(System.out);
		}
	}

	public void shutdown(){
		try {
			connection.close();
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}

	public void showAll(){
		try{
			String sql = "Select * from staff;";

			Statement statement = connection.createStatement();
			ResultSet resultSet = statement.executeQuery(sql);

			while (resultSet.next()) {
                System.out.println(resultSet.getInt("id") + " - " + resultSet.getString("firstname") + " " + resultSet.getString("lastname") + ", " + resultSet.getInt("manager"));
				
			}
			resultSet.close();
			statement.close();
		}
		catch (SQLException e) {
			e.printStackTrace(System.out);
		}

	}


	public void getStaffMember(int id){
		try{
			String sql = "Select * from staff where id = ?";

			PreparedStatement statement = connection.prepareStatement(sql);
			statement.setInt(1, id);
			ResultSet resultSet = statement.executeQuery();

			System.out.println("Showing single staff member " + id);
			while (resultSet.next()) {
				if (resultSet.getString("manager") == null) // alternatively, check for 0. Neither feels satisfying
					System.out.println("The boss!");
                System.out.println(resultSet.getInt("id") + " - " + resultSet.getString("firstname") + " " + resultSet.getString("lastname") + ", " + resultSet.getInt("manager"));
				
			}
			resultSet.close();
			statement.close();
		}
		catch (SQLException e) {
			e.printStackTrace(System.out);
		}

	}

	public void getManager(int id){
		//getStaff does half the work already.
		try{
			String sql = "select * from staff where id = ?";

			PreparedStatement statement = connection.prepareStatement(sql);
			statement.setInt(1, id);
			ResultSet resultSet = statement.executeQuery();

			System.out.println("Showing manager path for " + id);
			while (resultSet.next()) {
				System.out.println(resultSet.getInt("id") + " - " + resultSet.getString("firstname") + " " + resultSet.getString("lastname") + ", " + resultSet.getInt("manager"));
				statement.setInt(1, resultSet.getInt("manager"));
				resultSet = statement.executeQuery();
			}
			resultSet.close();
			statement.close();
		}
		catch (SQLException e) {
			e.printStackTrace(System.out);
		}
	}
}
