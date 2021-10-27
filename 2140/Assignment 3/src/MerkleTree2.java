import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;

public class MerkleTree2 {

    public String buildFrom(ArrayList<Transaction> transactions) throws NoSuchAlgorithmException 
    {
    	String topHash ="";
    	int size = transactions.size();
    	ArrayList<String> hashes = new ArrayList<String>();
    	MessageDigest digest = MessageDigest.getInstance("SHA-256");
    	int level = 0;
    	System.out.println("\nMerkle Tree, Bottom Up, Level: "+level+++", number of hashes: "+size);
    	
    	for(int i=0;i<transactions.size();i=i+2)
    	{
            Transaction tx1 = transactions.get(i);
            Transaction tx2 = tx1;
            if(i+1 < transactions.size()) 	
            	tx2 = transactions.get(i+1); //odd hash
            
            String h1 = UtilityFunctions.getSHA256(digest, tx1.toString()); //tx1 is hashed
            String h2 = h1+(UtilityFunctions.getSHA256(digest, tx2.toString())); //tx2 is hashed and added to h1
            String h3 = UtilityFunctions.getSHA256(digest, h2); //the whole thing is hashed
            hashes.add(h3);
        }
       
    	while(size >0)
    	{
        	size = hashes.size();
        	System.out.println("Merkle Tree, Bottom Up, Level: "+level+++", number of hashes: "+size);
        	hashes = mergeLeaves(hashes);
        	if(size == 1)
        	{
        		topHash =hashes.get(0);
        		size = 0;
        	}
        }
        System.out.println( "Merkle top hash is: "+topHash);
       
        return topHash;

    }
    
    ArrayList<String> mergeLeaves(ArrayList<String> merge) throws NoSuchAlgorithmException
    {
    	MessageDigest digest = MessageDigest.getInstance("SHA-256");
    	ArrayList<String> hashes = new ArrayList<String>();
    	
    	if(merge.size() >1)
    	{
    		for(int i=0;i<merge.size();i=i+2)
    		{
    		
    			String h1 = merge.get(i);
    			String h2 = h1;
    			if(i+1 < merge.size())
            	h2 = merge.get(i+1); //odd hash
    			h2= h1+h2;
    			String h3 =UtilityFunctions.getSHA256(digest, h2);
    			hashes.add(h3);
    		}
    		merge = hashes;
    	}
    	//else do nothing
    	
    	return merge;
    }
} 
