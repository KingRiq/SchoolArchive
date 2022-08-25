// COMP 2140 SECTION A01
// Assignment 5
// Eriq Hampton, 7852830
// April 6th, 2020
//
// PURPOSE: receives a list of transactions and returns the top hash 
// of all of the transactions
//
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;

public class MerkleTree {

    public String buildFrom(ArrayList<Transaction> transactions) throws NoSuchAlgorithmException 
    {
    	String topHash ="";
    	int size = transactions.size();
    	MessageDigest digest = MessageDigest.getInstance("SHA-256");
    	int level = 0;
    	Queue<String> queue1 = new LinkedList<String>();
    	Queue<String> queue2 = new LinkedList<String>();
    	
    	// put all transactions into one queue
    	for(int i = 0; i<transactions.size(); i=i+1)
    		queue1.add(transactions.get(i).toString());
    	
    	//hash each transaction, group them in 2's and hash the concatenated groups until we have a top hash
    	System.out.println("Merkle Tree, Bottom Up, Level: "+level+++", number of hashes: "+size);
    	while(!queue1.isEmpty())
    	{  		
    		String h1 = UtilityFunctions.getSHA256(digest, queue1.remove());
    		String h2 = h1;
    		
    		if(queue1.size() != 0)	
    			h2 = UtilityFunctions.getSHA256(digest, queue1.remove());
    		
    		String h3 = UtilityFunctions.getSHA256(digest, h1+h2);
    		queue2.add(h3);
    		
    		// if the 1st queue is empty and the 2nd queue != 1 then we are not done	
    		if(queue1.isEmpty())
    		{
    			size = queue2.size();
    			System.out.println("Merkle Tree, Bottom Up, Level: "+level+++", number of hashes: "+size);
    			
    			if(queue2.size() != 1)
    			{
    				Queue<String> temp = queue1; 
    				queue1= queue2;
    				queue2 = temp;
    			}
    		}//else we are done		
    	}
    	
    	topHash = queue2.remove();
        System.out.println( "Merkle top hash is: "+topHash);
    
        return topHash;

    }
    
} 
