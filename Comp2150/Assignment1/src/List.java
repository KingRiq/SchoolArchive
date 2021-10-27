// CLASS: List
//
// Author: Eriq Hampton, 7852830
//
// REMARKS: This list accepts both objects Student
// and Tutor but not both at the same time to
// avoid confusion or mixing of data.
//-----------------------------------------
public class List 
{
	protected class Node
	{
		Student newStudent;
		Tutor newTutor;
		Node next;
		
		protected Node(Student newStudent, Node newNext)
		{
			this.newStudent = newStudent;
			next = newNext;
		}
		protected Node(Tutor newTutor, Node newNext)
		{
			this.newTutor = newTutor;
			next = newNext;
		}
		
	}
	protected Node head;
	
	protected List()
	{
		head = null;
	}
	
	protected void add(Student newStudent)
	{
		Node newNode = new Node(newStudent, null);
		if(head == null)
		{
			head = newNode;
			
		}
		else
		{
			newNode.next = head;
			head = newNode;
		}
	}
	
	protected void add(Tutor newTutor)
	{
		Node newNode = new Node(newTutor, null);
		if(head == null)
		{
			head = newNode;
		}
		else
		{
			newNode.next = head;
			head = newNode;
		}
	}
	
	protected Tutor assignTutor(String topic, int hours)
	{
		Tutor currReference = null;
		currReference = findCheapest(topic);
		
		return currReference;
	}
	
	protected void addTopic(String topic, String userID, int price)
	{
		Node prev;
		Node curr = head;
		
		while(curr != null)
		{
			if(curr.newTutor.getUserID().equals(userID))
			{
				curr.newTutor.addTopicList(topic, price);
			}
			prev = curr;
			curr = curr.next;
		}
	}
	
	protected Student fetchStudent(String userID)
	{
		Node prev;
		Node curr = head;
		Student reference = null;
		while(curr != null)
		{
			if( curr.newStudent != null && curr.newStudent.getUserID().contentEquals(userID))
			{	
				reference = curr.newStudent;
			}
			
			prev = curr;
			curr = curr.next;
		}
		return reference;
	}
	
	protected Tutor fetchTutor(String userID)
	{
		Node prev;
		Node curr = head;
		Tutor reference = null;
		
		while(curr != null)
		{
			if( curr.newTutor != null && curr.newTutor.getUserID().equals(userID)) //check if tutor or student list
			{ 
				reference = curr.newTutor;
			}
			prev = curr;
			curr = curr.next;
		}
		return reference;
	}

	
	protected int availableHours(String topic)
	{
		Node prev;
		Node curr = head;
		int hoursAvail=0;
		
		while(curr != null)
			{
				TopicList checkList = curr.newTutor.getTopicList();
				if(checkList.search(topic))
				{
					hoursAvail= hoursAvail +curr.newTutor.getHours();
				}
				prev = curr;
				curr = curr.next;
			}
		return hoursAvail;
	}
	
	//------------------------------------------------------
    // findCheapest
    //
    // PURPOSE: Trivially it finds the cheapest tutor
	// however it also checks if other users has more hours
	// those that have the same price but more hours are prioritized.
	// As a last resort the userIDs are compared for priority.
    // 
	// PARAMETERS: This method accepts a String which contains the topic
    // this is needed because we need to know if the topic even exists 
	// in a tutor's list first. It then returns the tutor
	// that will be used to book an appointment
    //------------------------------------------------------
	protected Tutor findCheapest(String topic)
	{
		Node prev;
		Node curr= head;
		Tutor cheapest= null;
		int price = 1001;
		
		while(curr != null)
		{
			TopicList tutorFound =curr.newTutor.getTopicList();
			
			if(tutorFound.search(topic) && tutorFound.getPrice(topic) < price) 
			{
				
				if(curr.newTutor.getHours() > 0)
				{
					cheapest = curr.newTutor; 
					price = cheapest.getTopicList().getPrice(topic);					
				}		
			}
			else if(tutorFound.search(topic) && tutorFound.getPrice(topic) == price) 
			{
				if(curr.newTutor.getHours() > cheapest.getHours())
				{
					cheapest = curr.newTutor;
				}
				else if(curr.newTutor.getHours() == cheapest.getHours())
				{
		
					//if negative than a new cheaper tutor is chosen						
					//if positive do nothing... 				
					int alphabetize =curr.newTutor.getUserID().toLowerCase().compareTo(cheapest.getUserID().toLowerCase());
					if(alphabetize < 0)
					{
						cheapest = curr.newTutor;
					}
				}	
			}
				
			prev = curr;
			curr = curr.next;
		}
		
		return cheapest;
	}
}
