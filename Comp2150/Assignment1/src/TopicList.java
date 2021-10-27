// CLASS: TopicList
//
// Author: Eriq Hampton, 7852830
//
// REMARKS: This list holds all the topics a
// tutor can teach. For each tutor in List.java 
//-----------------------------------------
public class TopicList extends List{

	public class Node
	{
		String topic;
		int price;
		Node next;
		public Node(String topic, int price, Node newNext)
		{
			this.topic = topic;
			this.price = price;
			next = newNext;
		}
		
	}
	private Node head;
	
	
	public TopicList()
	{
		head = null;
		
	}
	
	
	public void add(String topic, int price)
	{
		Node newNode = new Node(topic, price, null);
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

	public boolean search(String userID)
	{
		Node prev = null;
		Node curr = head;
		boolean topicFound = false;
		while(curr != null)
		{
			
			if(curr.topic.equals(userID)) //check if tutor or student list
			{ 
				topicFound = true;
			}
			prev = curr;
			curr = curr.next;
		}
	return topicFound;
	}
	 public int getPrice(String topic)
	 {
		 Node prev;
		 Node curr = head;
		 int price;
		 while(curr !=null && !curr.topic.equals(topic))
		 {	
			 prev = curr;
			 curr = curr.next;
		 }
		 
		 return curr.price;
	 }
}


