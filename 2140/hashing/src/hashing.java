
  


public class hashing 
{

	static final int A = 7;
	static int hashArray[] = new int [11];
	public static void main(String[] args)
	{
		int i[] = {2,14,12,15,20,19,4,17};
		int p = hash(i);
		System.out.println(p);
	}


	public static int hash( int key[] ) 
	{
		int hashIndex = 0;

		for ( int i = 0; i < key.length; i++ ) 
		{
			//System.out.println(hashIndex);
    	    hashIndex = (hashIndex * A ) % hashArray.length +  key[i];
    	    //System.out.println(hashIndex);
    	    //(0*3)%7+3
    	   
    	    hashIndex = hashIndex % hashArray.length;
    	    //3%7= 3
    	    //2*3= 6%7 = 6+101 = 107%7 =2
    	    //6+97 = 103%7 = 5
    	    // 5*3 = 15%7 =1 +102 = 103%7 = 5
    	    //2,2,5 5
    	    //System.out.println(key[i]);
		}

		return hashIndex;
    } 
}




