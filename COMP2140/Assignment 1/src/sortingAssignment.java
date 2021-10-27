/**
* Sorting Algorithm Assignment 1
*
* COMP 2140 SECTION A01
* INSTRUCTOR Akcora
* ASSIGNMENT Assignment 1
* @author Eriq Hampton
* @version 02/10/2020
*
* PURPOSE: Implements mergesort, inefficient mergesort,
* quicksort and attempted radixsort(MSD) and compares their time
* complexities based on the number size and number of swaps done on a
* random or integers.
*/
import java.io.*; 
import java.util.*; 
public class sortingAssignment {
	
	//merge sorts all items in the array
	//public driver method
	public static void mergeSort(int[] array) 
	{
		if(array.length != 0)
		{
			int[] temp = new int[array.length];
			
			mergeSort(array, 0, array.length, temp);
		}
		
		else
		{
				System.out.println("Warning this is a null array");
		}
	}
	
	//merge method
	private static void merge(int[] array, int start, int mid, int end, int[]temp)
	{
		int currT, currL, currR;
		currR= mid;
		currL= start;	
	
		for(currT = start; currT < end; currT++)
		{
			if(currL < mid &&(currR >= end || array[currL]< array[currR]))
			{
				temp[currT]= array[currL];
				currL++;
			}
			else
			{
				temp[currT]= array[currR];
				currR++;
			}
		}
	
		for(currT = start; currT < end; currT++)
		{
			array[currT] = temp[currT];
		}
	
	}
	
	private static void mergeSort(int[] array, int start, int end, int[] temp)
	{
		int mid;
		if (1 < end - start)
		{
			//Recursive case: if array has more than one item
			mid = start + (end - start) / 2;
			
			//mergeSort the left half
			mergeSort(array, start, mid, temp);
			
			//merge sort the right half
			mergeSort(array,mid, end, temp);
			merge(array, start, mid, end, temp);
		}
		//BASE CASE: else do nothing because less than 2 items in the array
	}
	
	public void quickSort( int[] a)
	{
		quickSort(a, 0, a.length);
	}
	private void quickSort(int[] array, int start, int end)
	{
		if( start < end)
		{
			
			choosePivot(array, start, end);
			int pi = partition(array, start, end);
			
			quickSort(array, start, pi-1);
			quickSort(array, pi + 1, end);			
		}
		else
		{
			System.out.println("Warning this is a null array");
		}
		
	}

	private void choosePivot(int array[], int start, int end)
	{
		int temp;
		
		if(end - start <= 1)
		{
			if(array[start] > array[end])
			{
				temp = array[start];
				array[start] = array[end];
				array[end] = temp;
			}
				
		}
			
		else
		{
			//stores start value in temp
			//start is now same as pivot
			int pivot = (start + end) /2;
			temp = array[start]; 
			array[start] = array[pivot]; 
			array[pivot] = temp;
		}
			
			
	}
		
	private int partition(int[] array, int start, int end)
	{
		int pivot = array[start];
		int curr = start + 1;
		int bigStart = start+1;
		int temp;
		
		
		for(curr= start; curr < end; curr++)
		{
			if(array[curr] < pivot)
			{					
				temp = array[bigStart];
				array[bigStart] = array[curr];
				array[curr]= temp;
				bigStart++;
			}	
		}
			
			temp = array[bigStart-1];
			array[bigStart-1]= pivot;
			array[start]= temp;
			
			return bigStart-1;
		}

	//merge sort all items in array 
	//public driver method
	public static void mergeSortInefficient(int[] array) 
	{	
		if(array.length != 0)
		{
			//no temp array is used
			mergeSortInefficient(array, 0, array.length-1);
		}		
		
	}
	private static void mergeInefficient(int[] array, int start, int mid, int end)
	{
		//points to the position after middle used in value swapping
		int pivot = mid+1;
		
		//edge case already sorted or they are the same number
		if(array[mid] <= array[pivot])
		{
			return;
		}
			
		while(start <= mid && pivot <= end) 
		{
			if(array[start] <= array[pivot])
			{
				start++;
			}
			
			else
			{
				int temp = array[pivot];
				int placeHolder= pivot;
				
				while(placeHolder != start) 
				{
					array[placeHolder] = array[placeHolder-1];
					placeHolder--;
				}
				
				array[start]= temp;
				start++;
				mid++;
				pivot++;
			}
		}
	}
		
	private static void mergeSortInefficient(int[] a, int start, int end)
	{
		if(start < end)
		{
			//Recursive case: if array has more than one item
			//mergeSort the left half
			//mergeSort the right half
			int mid = start + (end - start) / 2;
			
			mergeSortInefficient(a, start, mid);
			mergeSortInefficient(a, mid+1, end);
			
			//puts it all together
			mergeInefficient(a, start, mid, end);
		}
	
			//BASE CASE: else do nothing because less than 2 items in the array
		}
	/*static void radixSort(int[] array, int n)
	{
		int max = array[0];
		for(int i = 1; i < n; i++)
		{
			if(array[i] > max)
				max = array[i];
	    
		}
		
		int max1= (int)Math.log10(max)+1;
		int exp = (int) Math.pow(10, max1-1);
		
		for(int i = exp; max1 !=0 && exp > 0; exp/=10)
			countingSort(array, n, exp);
		
	}
	static void countingSort(int[] array, int n, int exp)
	{
		int bucket[] = new int[10];  
        int i; 
        int count[] = new int[10]; 
        Arrays.fill(count,0); 
         
       for (i = 0; i < n  ; i++) 
       {
    	   System.out.println(array[i]/exp);
    	   count[ array[i]/exp%10]++;
        }
       
       for (i = 1; i < 10; i++)
       {
    	   count[ i ] = count[i]+ count [i - 1];
    	   
       }
      
    // Build the output array 
       for (i = n - 1; i >= 0; i--) 
       { 
    	   
           bucket[count[ (array[i]/exp)%10 ] - 1] = array[i]; 
           
           count[ (array[i]/exp)%10 ]--; 
       } 
       
      
       // Copy the output array to arr[], so that arr[] now 
       // contains sorted numbers according to curent digit 
       for (i = 0; i < n; i++) 
           array[i] = bucket[i]; 

	}
	*/
	
	public static boolean isSorted(int[] array) 
	{
	    
	    int i;
	    boolean p= true;
	    
	    for(i=0; i < array.length-1; i++)
	    {
	    	if(array[i+1]< array[i])
	    	{	
	    		p= false;
	    		break;
	    	}
	    	
	    }
	    return p;
	}
	
	private static void fillArray(int[] array)
	{
		for(int i=0; i < array.length; i++)
		{
			array[i]= i;
		}
	}
	
	private static void arrayRandomizer(int[] array, int n)
	{
		for(int i=0; i < n; i++)
		{
			int pos1 = (int) (Math.random() * array.length);
			int pos2=  (int) (Math.random() * array.length);
			
			int temp = array[pos1];
			array[pos1]= array[pos2];
			array[pos2]=temp;
		}		
	}
	/*******************************************************************
	* arithmeticMean
	*
	* Purpose: Compute the average of long values.
	* To avoid long overflow, use type double in the computation.
	*
	******************************************************************/
	public static double arithmeticMean( long data[] ) {
	double sum = 0;
	for (int i = 0; i < data.length; i++)
	sum += (double)data[i];
	return sum / (double)data.length;
	} // end arithmeticMean
	
	
	/*******************************************************************
	* testingAlgorithms
	*
	* Purpose: tests the observed algorithms by sorting n array sizes and swaps
	* it is important in showing time complexity and guys us a general
	* idea of when to use a certain algorithm. It also returns is
	* a false algorithm by calling the boolean method IsEmpty
	******************************************************************/

	public static void testingAlgorithms(int size)
	{	
		int arraySize = size;
		int numSwaps = (int)(.25 * arraySize);
		
		long startTime, endTime, elapsedTime;
		
		long mergeSortTimings[]= new long[arraySize];
		for(int i=0; i<100; i++)
		{
		
			int array[] = new int[arraySize];
			fillArray(array);
			arrayRandomizer(array, numSwaps);
			startTime = System.nanoTime();
			mergeSort(array);
			endTime = System.nanoTime();
			elapsedTime = (endTime - startTime);
			mergeSortTimings[i] = elapsedTime;
			if(isSorted(array)== false)
				System.out.println("A sorting error occurred with mergeSort.");
		
		
		}
		
		
		long quickSortTimings[]= new long[arraySize];
		for(int i=0; i<100; i++)
		{
		
			int array[] = new int[arraySize];
			fillArray(array);
			arrayRandomizer(array, numSwaps);
			startTime = System.nanoTime();
			mergeSort(array);
			endTime = System.nanoTime();
			elapsedTime = endTime - startTime;
			quickSortTimings[i] = elapsedTime;
			if(isSorted(array)== false)
				System.out.println("A sorting error occurred with quickSort.");
		
		
		}
		long inefficientMergeSortTimings[]= new long[arraySize];
		for(int i=0; i<100; i++)
		{
		
			int array[] = new int[arraySize];
			fillArray(array);
			arrayRandomizer(array, numSwaps);
			startTime = System.nanoTime();
			mergeSortInefficient(array);
			endTime = System.nanoTime();
			elapsedTime = endTime - startTime;
			inefficientMergeSortTimings[i] = elapsedTime;
			if(isSorted(array)== false)
				System.out.println("A sorting error occurred with mergeSortInefficient.");
		
		
		}
		/*long radixSortTimings[]= new long[arraySize];
		for(int i=0; i<1; i++)
		{
		
			int array[] = new int[arraySize];
			fillArray(array);
			arrayRandomizer(array, numSwaps);
			startTime = System.nanoTime();
			radixSort(array, arraySize-1);
			endTime = System.nanoTime();
			elapsedTime = endTime - startTime;
			radixSortTimings[i] = elapsedTime;
			if(isSorted(array)== false)
				System.out.println("A sorting error occurred with mergeSort.")
		
		
		}*/
		
		System.out.println("Size:"+ arraySize + "\nSwaps Total: "+ numSwaps);
		
		double mergeSortMean = arithmeticMean( mergeSortTimings );
	    System.out.println("MergeSort time = " + mergeSortMean);
		
	    double inefficientMergeSortMean = arithmeticMean( inefficientMergeSortTimings );
		System.out.println("Inefficient MergeSort time = " + inefficientMergeSortMean);
		
		double quickSortMean = arithmeticMean( quickSortTimings );
		System.out.println("quickSort time = " + quickSortMean+"\n");
		
		/*double radixSortMean = arithmeticMean( radixSortTimings );
		System.out.println("radixSort time = " + mergeSortMean);*/
	}




	public static void main(String[] args)
	{
		
		testingAlgorithms(10000);
		testingAlgorithms(20000);
		testingAlgorithms(30000);
		testingAlgorithms(40000);
		testingAlgorithms(50000);
		testingAlgorithms(60000);
		System.out.println("Process Complete");

	}
}

/**
* 1. Algorithm Name 		Array Size 		Time
* 	----------------   	   ------------    ------
* 	MergeSort				10000			383.8606
* 	MergeSortInefficient	10000			3288.9476
*  	QuickSort				10000			227.6019
* 	Radix					N/A				N/A
* 
* 	MergeSort				20000			130.29305
* 	MergeSortInefficient	20000			3422.02305
* 	QuickSort				20000			205.6826
* 	Radix					N/A				N/A
* 	
* 	MergeSort				30000			100.00043333333333	
* 	MergeSortInefficient	30000			2023.5592333333334	
* 	QuickSort				30000			100.98	
* 	Radix				   	N/A				N/A		
*  	
*  	MergeSort				40000			99.165025	
* 	MergeSortInefficient	40000			2802.03305	
* 	QuickSort								100.91985
* 	Radix					N/A				N/A
*  
*  	MergeSort				50000			135.90978	
* 	MergeSortInefficient	50000			3579.38334	
* 	QuickSort				50000			103.24674	
* 	Radix					N/A				N/A
* 
*  	MergeSort				60000			129.25845	
* 	MergeSortInefficient	60000			4304.9918		
* 	QuickSort				60000			182.33378333333334
* 	Radix					N/A				N/A
*  					
*  	
*
*2. Quicksort was the best performer because its average case is is ONlogN and performs 
* better the less it has to partition. 
* 
*3. The cost is enormous. MergeSort creates a temporary array but 
* inefficient mergesort stores each sort in a temp variable. The memory saved is not
* worth it overall.
* 
*4. Although I did not complete this. I can easily predict, That radix sort
* depends entirely on the recursive calls on the buckets of the stored
* array elements. This can be really quick or very close as the algorithm deals
* with increasing edge cases.
* 
* 5. What slows down radix sort is the recursion. The counting is very quick even shown in
* lab 1 of this course.
*/