// CLASS: Student
//
// Author: Eriq Hampton, 7852830
//
// REMARKS:  Student object implentation
//-----------------------------------------
public class Student {

	private String userID;
	private String report = "";
	private int tutorTotal;
	private int totalCost;
	
	public Student(){}
	
	public Student(String userID)
	{
		System.out.println("A student has been created.");
	
		this.userID = userID;
		System.out.println("Student with userid " +userID+ " successfully created.");
	}
	
	public void setUserID(String userID)
	{
		this.userID = userID;
	}
	public String getUserID()
	{
		return userID;
	}
	public void setReport(String report)
	{
		this.report += report;
	}
	public void setTutorTotal(int tutorTotal, int totalCost)
	{
		this.tutorTotal += tutorTotal;
		this.totalCost += totalCost;
	}
	public void printReport()
	{
		System.out.println("\nReport for "+ this.getClass().getSimpleName()
				+ " "+ this.getUserID());
		System.out.println("-------------------------------");
		System.out.println(report);
		System.out.println("Total number of hours of tutoring: " +tutorTotal);
		System.out.println("Total cost/revenue from tutoring: "+ totalCost);
		System.out.println("-------------------------------\n");
	}
}
