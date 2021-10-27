// CLASS: CommandList
//
// Author: Eriq Hampton, 7852830
//
// REMARKS: This is the command interface class 
// it accepts the commands from FileReader
// and executes them.
//-----------------------------------------
public class CommandList 
{
	private List tutorList = new List();
	private List studentList = new List();
	private String userID;
	private int price;
	private Student newStudent;
	private Tutor newTutor;
	private String topic;
	
	protected void commandList(String commandString)
	{
		
		//array for temp storage of command
		String[] command = commandString.split("\\s+");
		 
		
		if(command[0].equals("TUTOR"))
		{
			System.out.println("Tutor command entered!");
			userID= command[1];
			int hours = Integer.parseInt(command[2]);
			
			if(!checkUser(userID))
			{
				if(hours >= 1 && hours <= 1000)
				{
					newTutor = new Tutor(userID, hours);
					tutorList.add(newTutor);
			
				}
				
				else
				{
					System.out.println("Invalid number of hours, try again!");
				}
			}
			else
			{
				System.out.println("Duplicate Tutor with userid " +userID);
			}
		}
		
		if(command[0].equals("STUDENT"))
		{
			userID = command[1];
			System.out.println("Student command entered!");
			if(!checkUser(userID))
			{
				newStudent = new Student(userID);
				studentList.add(newStudent);
			}
			else
			{
				System.out.println("Duplicate Student with userid " +userID);
			}
		}
				
		if(command[0].equals("TOPIC"))
		{
			topic = command[1];	
			userID = command[2];
			price = Integer.parseInt(command[3]);
			
			System.out.println("Topic command selected");
			if(checkUser(userID))
			{
				if(price > 0 && price < 1000)
				{
					tutorList.addTopic(topic, userID, price);
				}
				else
				{
					System.out.println("Invalid price!");
				}
			}
			else
			{
				System.out.println("Tutor not found");
			}
		}
		if(command[0].equals("REQUEST"))
		{
			userID = command[1];	
			topic = command[2];
			int hours = Integer.parseInt(command[3]);
			
			System.out.println("A Student has made a request!");
			
			if(hours> 0 && hours < 2000)
			{
				if(checkUser(userID))
				{
					System.out.println("Attempting to fulfill a request for "+ userID 
						+ " to receive "+ hours + " of tutoring in topic "+ topic);
					
					if(tutorList.availableHours(topic) == 0)
					{
						System.out.println("Topic: " + topic + "is currently not available for tutoring");
					}
					
					else if(tutorList.availableHours(topic) >= hours)
					{
						while(hours !=0)
						{
							newTutor  = tutorList.assignTutor(topic, hours);
							newStudent = studentList.fetchStudent(userID);
							
						hours = setAppt(newStudent, newTutor, topic, hours);
						}
					}
					else
					{
						System.out.println("Request failed. There are not tutors to accommodate the hours needed for "+topic+ " tutoring");
					}	
				}
				else
				{
					System.out.println("Student not found");
				}
			}
		}
		
		if(command[0].equals("STUDENTREPORT"))
		{
			System.out.println("Student report command selected");
			String userID = command [1];
			Student studentReport = studentList.fetchStudent(userID);
			
			if(studentReport !=null)
			{
				studentReport.printReport();
			}
			else
			{
				System.out.println("Student not found! Nothing to report");
			}
		}
		
		if(command[0].equals("TUTORREPORT"))
		{
			System.out.println("Tutor Report command selected");
			String userID = command [1];
			Tutor tutorReport = tutorList.fetchTutor(userID);
			
			if(tutorReport != null)
			{
				tutorReport.printReport();
			}
			else
			{
				System.out.println("Tutor not found! Nothing to report.");
			}
		}
		
		if(command[0].equals("#"))
		{
			for(int i=1; i< command.length; i++)
			System.out.print(command[i]+ " ");
			System.out.println();
		}
		
		
	}
		
	protected boolean checkUser(String userID)
	{
		boolean foundUser = false;
		newTutor = tutorList.fetchTutor(userID);
		newStudent = studentList.fetchStudent(userID);
		
		if((newTutor != null && newTutor.getUserID().equals(userID)) || (newStudent != null && newStudent.getUserID().equals(userID)))
		{
			foundUser = true;
		}
	
		return foundUser;
	}

	protected int setAppt(Student student, Tutor tutor, String topic, int hours)
	{
		int price = tutor.getTopicList().getPrice(topic);
		int apptHours = 0;
		int totalCost;
	
		//Scheduling
		if(hours > tutor.getHours())
		{
			hours = hours - tutor.getHours();
			apptHours = tutor.getHours();
			tutor.setHours(apptHours- apptHours);
		}
		else if(tutor.getHours() >= hours)
		{
			tutor.setHours(tutor.getHours()-hours);
			apptHours = hours;
			hours= hours - hours;
		}
	
		totalCost = price * apptHours;
		System.out.println("Booking Appointment!");
	
		String bookTutor = "Appointment: "+student.getClass().getSimpleName()+ ": "+ student.getUserID() + " topic: " + topic +
				", hours: " +apptHours+ ", total cost: "+ totalCost+"\n";
	
		String bookStudent = "Appointment: "+tutor.getClass().getSimpleName()+ ": "+ tutor.getUserID() + " topic: " + topic +
				", hours: " +apptHours+ ", total cost: "+ totalCost+"\n";
		
	tutor.setTutorTotal(apptHours, totalCost);
	student.setTutorTotal(apptHours, totalCost);
	
	tutor.setReport(bookTutor);	
	student.setReport(bookStudent);
	System.out.println("Appointment Booked!\n");
	
	return hours;
}

}



