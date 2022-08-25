import java.io.*; 
import java.util.*; 
class radixSortImplementation
{
	static void countingSort(int[] a, int n, int exp)
	{
		int bucket[] = new int[10];  
        int i; 
        int count[] = new int[10]; 
        Arrays.fill(count,0); 
         
       for (i = 0; i < n  ; i++) 
       {
    	   System.out.println(a[i]/exp);
    	   count[ a[i]/exp%10]++;
        }
       
       for (i = 1; i < 10; i++)
       {
    	   count[ i ] = count[i]+ count [i - 1];
    	   
       }
      
    // Build the output array 
       for (i = n - 1; i >= 0; i--) 
       { 
    	   
           bucket[count[ (a[i]/exp)%10 ] - 1] = a[i]; 
           
           count[ (a[i]/exp)%10 ]--; 
       } 
       
      
       // Copy the output array to arr[], so that arr[] now 
       // contains sorted numbers according to curent digit 
       for (i = 0; i < n; i++) 
           a[i] = bucket[i]; 

	}
	
	static void radixSort(int[] a, int n)
	{
		int max = a[0];
		for(int i = 1; i < n; i++)
		{
			if(a[i] > max)
				max = a[i];
	    
		}
		
		int max1= (int)Math.log10(max)+1;
		int exp = (int) Math.pow(10, max1-1);
		
		for(int i = exp; max1 !=0 && exp > 0; exp/=10)
			countingSort(a, n, exp);
		
	}
public static void main(String[] args)
	{
		int[] myNums = {170, 45, 75, 901, 802, 801, 2, 66};
		
		
		radixSort(myNums, myNums.length);
		for(int i =0; i < myNums.length; i++)
		System.out.println(myNums[i]);
	}
	
}