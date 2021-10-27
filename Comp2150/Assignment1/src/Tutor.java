// CLASS: Tutor
//
// Author: Eriq Hampton, 7852830
//
// REMARKS: Tutor object implementation
// extends student since both are similar
//-----------------------------------------
public class Tutor extends Student
{
	private String userID;
	private int hours;
	private TopicList topicList = new TopicList();
	
	
	
	public Tutor(String userID, int hours)
	{
		
		this.userID = userID;
		this.hours= hours;
		System.out.println("Tutor with userid " +userID+ " successfully created.");
	}
	
	public void setHours(int hours)
	{
		this.hours= hours;
	}
	
	public void addTopicList(String topic, int price)
	{
		//make sure topic exists
		if(!topicList.search(topic))
		{
			topicList.add(topic, price);
			System.out.println("Topic: " + topic + " added to " + this.getUserID()+ " with price "+price );
		}
		else 
		{
			System.out.println("Topic: "+ topic + " already exists, this entry will be ignored");
		}
	}
	
	public TopicList getTopicList()
	{
		return topicList;
	}

	public String getUserID()
	{
		return userID;
	}
	public int getHours()
	{
		return hours;
	}

	
}

