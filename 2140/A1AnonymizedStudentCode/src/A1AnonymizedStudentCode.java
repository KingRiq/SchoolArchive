/**
* A1****
*
* COMP 2140 SECTION A01
* INSTRUCTOR Akcora
* ASSIGNMENT Assignment #1
* @author *****
* @version 2020.02.02
*
* PURPOSE: Comparing the time of different sorting methods
*/
import java.util.*;

public class A1AnonymizedStudentCode {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int times = 10000;
		for(int i=1; i<=5; i++) {
			testSortingMethodsTime(i*times);
		}
		
		System.out.println("End Of Processing");

	}
	
/* ***********************************************************
 *                         Merge Sort
 *************************************************************/
	
	/**
	* PURPOSE: Public driver method of merge sort
	* Pass in the array as the parameter
	* 
	*/
	public static void mergeSort(int[] arr) {
		if(!(arr==null)&&!(arr.length<2)) {         // Sort the array if it is not empty or null or just 1 element
		    int[] temp = new int[arr.length];
		    mergeSort(arr, 0, arr.length, temp);
		}
	}
	
	/**
	* PURPOSE: Private method for the merge sort, recursively sort the array for a certain part
	* Parameters:
	* @param firstParameter: Array that we pass in to sort
	* @param SecondParameter: start index of the array to sort
	* @param thirdParameter: End index of the array to sort
	* @param fourthParamter: A temporary array to store the value that has already been sorted
	*/
	private static void mergeSort(int[] arr,int start, int end, int[] temp) {
		if(end-start>1) {
		    int mid = (start+end) / 2;
		    mergeSort(arr,start, mid,temp);
		    mergeSort(arr,mid,end,temp);
		    merge(arr,start,mid,end,temp);
		}

	}
	
	/**
	* PURPOSE: helper method that merge the two sorted lists into one
	* Parameters:
	* @param firstParameter: Array that we pass in to merge
	* @param SecondParameter: Start index of the array to merge
	* @param thirdParameter: Mid index that divide the list into two half
	* @param fourthParamter: End index of the array to merge
	* @param FifthParameter: A temporary array to store the value that has already been sorted
	*/
	private static void merge(int[] arr,int start,int mid, int end, int[] temp) {
		int currL = start;
		int currR = mid;
		int currT = start;
		
		for(currT=start;currT<end;currT++) {
			if(currL<mid&&(currR>=end||arr[currL]<arr[currR])) {    //checking if the index is out of bound first, then compare the value
				temp[currT] = arr[currL++];
			}else {
				temp[currT] = arr[currR++];
			}
		}
		for(int i=start; i<end; i++) {
			arr[i] = temp[i];
		}
	}
	
/* ***************************************************************************
 *                         Merge Sort Inefficient	
 * ***************************************************************************/
	/**
	* PURPOSE: Public driver method of merge sort that doesn't use a share array
	* Pass in the array as the parameter
	*/
	public static void mergeSortInefficient(int[] arr) {
		if(!(arr==null)&&!(arr.length==0)) 
		   mergeSortInefficient(arr,0,arr.length);
	}
	
	/**
	* PURPOSE: private method that accept the array to sort
	* 
	* @param firstParameter: Array that we pass in to sort
	* @param secondParameter: start index of the array to sort
    * @param thirdParameter: end index of the array to sort
	*/
	private static void mergeSortInefficient(int a[], int start, int end) {
		if(end-start>1) {
			int mid = (start + end)/2;
			mergeSortInefficient(a,start,mid);
			mergeSortInefficient(a,mid,end);
			System.arraycopy(merge(a,start,mid,end), 0, a, start, end-start);
		}
	}
	
	/**
	* PURPOSE: helper method that accept the array to merge without a share temporary array
	* 
	*  @param firstParameter: The array pass in to sort
	*  @param secondParameter: the start index of the array to sort
	*  @param thirdParameter: the mid index of the array, dividing the array into two half
	*  @param fourthParameter: the end index of the array to sort
	*  
	*  @return return an array that has been't sorted
	*/
	private static int[] merge(int[] a,int start,int mid, int end) {
		int[] temp = new int[end-start];
		int currL = start;
		int currR = mid;
		
		for(int currT=0;currT<end-start;currT++) {
			if(currL<mid&&(currR>=end||a[currL]<a[currR])) {    //checking if the index is out of bound first, then compare the value
				temp[currT] = a[currL++];
			}else {
				temp[currT] = a[currR++];
			}
		}
		return temp;
	}
	
/* *************************************************************************
 *                               Quick Sort
 * *************************************************************************/
	
	/**
	* PURPOSE: Public driver method of quick sort 
	* Pass in the array as the parameter
	*/
	public static void quickSort(int[] a) {
		if(!(a==null)&&!(a.length<2)) {
			quickSort(a, 0 , a.length);
		}
	}
	
	/**
	* PURPOSE: Private method of quick sort, divide the array that pass in into two half using the pivot 
	* 
	*  @param firstParameter: The array pass in to sort
	*  @param secondParameter: the start index of the array to sort
	*  @param thirdParameter: the end index of the array to sort
	*/
	private static void quickSort(int[] a, int start, int end) {
		if(end-start>1) {
			if(end-start==2) {
				if(a[start]>a[start+1]) {
					int temp = a[start];
					a[start] = a[start+1];
					a[start+1] = temp;
				}
			}else {
				medianOfThree(a,start,(start+end)/2,end);
				int pivot = partition(a,start,end);
				quickSort(a,start,pivot);
				quickSort(a,pivot+1,end);
			}
		}
	}
	
	/**
	* PURPOSE: Find the median in the start, mid, end index, and then swap the median to index start.
	* 
	*/
	private static void medianOfThree(int[] a, int start, int mid, int end) {
		int temp;
		if(a[start]<a[mid]) {
			if(a[mid]<a[end-1]) {
				temp = a[mid];
				a[mid] = a[start];
				a[start] = temp;
			}else if(a[start]<a[end-1]) {
				temp = a[end-1];
				a[end-1] = a[start];
				a[start] = temp;
			}
		}else {
			if(a[start]<a[end-1]) {
				;                  //Do nothing because median is already in a[start]
			}else if(a[mid]<a[end-1]) {
				temp = a[end-1];
				a[end-1] = a[start];
				a[start] = temp;
			}else {
				temp = a[mid];
				a[mid] = a[start];
				a[start] = temp;
			}
		}
	}
	
	/**
	* PURPOSE: Partition method for quick sort, using the first element of the list as the pivot
	*          putting elements smaller than pivot in the front part of the array, bigger, in the second
	*          half part of the array
	* 
	*  @param firstParameter: The array pass in to sort
	*  @param secondParameter: the start index of the array to part
	*  @param thirdParameter: the end index of the array to part
	*/
	private static int partition(int[] a,int start, int end) {
		int bigStart = start+1;
		int curr = start+1;
		int key = a[start];
		while(curr<end) {
			if(a[curr]<key) {
				int temp = a[curr];
				a[curr] = a[bigStart];
				a[bigStart] = temp;
				bigStart++;
			}
			curr++;
		}
		a[start] = a[bigStart-1];
		a[bigStart-1] = key;
		return bigStart-1;
	}
	
	
/* ***************************************************************
 *                          Radix Sort
 * ***************************************************************/
	
	/**
	* PURPOSE: Public driver method of the radix sort
	* 
	*  @param firstParameter: The array pass in to sort
	*  
	*/
	public static void radixSort(int[] arr) {
		int maxDig = findMaxDig(findMaxNum(arr));
		int currDig = (int)Math.pow(10, maxDig-1);
		int[] temp = new int[arr.length];
		radixSort(arr, currDig ,0 ,arr.length, temp);
	}
	
	/**
	* PURPOSE: Private method of the radix sort.
	*          It recursively divide the array into different buckets starting from the most significant digit
	*          to the least significant digit.
	*          Each bucket will contain another 10 bucket or maybe less, depending on the current digit of the
	*          the values in the bucket of what numbers they have.
	* 
	*  @param firstParameter: The array pass in to sort
	*  @param secondParameter: The starting index in the array of one bucket
	*  @param thirdParameter: The end index in the array of a certain bucket
	*  @param fourthParameter: A shared temporary array that has the same size as the original array,
	*                          used to temporary store the value of different buckets.
	*  
	*/
	private static void radixSort(int[] a, int curDig, int start, int end, int[] temp) {
		if(!(curDig==0)&&!(end-start<=1)) {        //current digit will be 0 if 1/10 convert to integer, or if  the bucket only have one element  
			                                       //in the bucket, no need to sort
			int range = 10;
			int[] frequency = new int[range];      //an array to store how many times a certain digit appears
			
			for(int i=start;i<end;i++) {
				frequency[(a[i]/curDig)%10]++;     
			}
			for(int i=1;i<10;i++) {
				frequency[i] += frequency[i-1];    //calculate the last index of a certain digit that should be in the bucket
			}
			
			//copy the value from one bucket to the temporary array using the frequency array that indicate the index
			//in the bucket they should be in, (frequency[value]-1+start): start is the start index of the current bucket,
			// adding the frequency-1 gives the index of the whole array that the value should be in.
			for(int i=end-1;i>=start;i--) {             
				int value = (a[i] / curDig) % 10;
				temp[frequency[value]-1+start] = a[i];
				frequency[value]--;
			}
			
			System.arraycopy(temp, start, a, start, end-start);
			
			curDig /= 10;         // Next significant digit
			
			//Recursively divide the current bucker into different small buckets depends on the next digit starting from index 'start' to 'end'.
			//For example there are 15 78 69, then the 0 bucket starts from 0 to 3.
			//(frequency + start): frequency are only the index in the bucket, plus start will be the index in the array
			//After the operation in the last for loop, frequency[i] now contains the digit i start index in the array
			// and the frequency[i+1] contains the end index of digit i.
			//(i+1==range?end:frequency[i+1]): if i has reached the range, the end index should be the parameter "end"
			//                                 frequency[i+1] will give an index out of bound exception. 
			for(int i=0;i<range;i++) {   
				radixSort(a,curDig,frequency[i]+start,i+1==range?end:frequency[i+1]+start,temp);
			}
		}
	}
	
	/**
	* PURPOSE: Find the maximum number in an array.
	* 
	*/
	private static int findMaxNum(int[] arr) {
		return Arrays.stream(arr).max().getAsInt();
	}
	
	/**
	* PURPOSE: Find the maximum digit of a certain number
	* 
	*/
	private static int findMaxDig(int num) {
		return (int)Math.log10(num)+1;
	}
	
/* ************************************************************
 *                       Check sorted
 * ************************************************************/
	
	/**
	* PURPOSE: To check whether an array is sorted or not
	* 
	* @param an array passed in to check
	*/
	public static boolean isSorted(int[] arr) {
		boolean flag = true;
		if(arr==null||arr.length==0) {
			System.out.println("Array is null or array is empty.");
			flag = false;
		}
		for(int i=1;i<arr.length&&flag;i++) {
			if(arr[i]<arr[i-1]) {                    //if a number is smaller than the number before it, it is not sorted
				flag = false;
			}
		}
		
		return flag;
	}
	
	/**
	* PURPOSE: To fill in an array with numbers in order starting from 0
	* 
	* @param an array passed in to fill
	*/
	public static void fillArray(int[] arr) {
		if(arr!=null&&arr.length!=0) {
			for(int i=0;i<arr.length;i++) {
				arr[i] = i;
			}
		}
	}
	
	/**
	* PURPOSE: To randomly swap two elements in an array n times
	* 
	* @param an array passed in swap
	* @param times that the swap to be done
	*/
	public static void swapArrayRandom(int[] arr,int n) {
		Random r = new Random();
		int pos1,pos2,temp;
		for(int i=0;i<n;i++) {
			pos1 = (int)r.nextInt(arr.length);
			pos2 = (int)r.nextInt(arr.length);
			temp = arr[pos1];
			arr[pos1] = arr[pos2];
			arr[pos2] = temp;
		}
	}
	
	/**
	* PURPOSE: To test all the sorting method, record their execution time and compare with a 
	*          given array size
	* 
	* @param the size of the array that needs to be initialized
	*/
	public static void testSortingMethodsTime(int size) {
		int[] arr = new int[size];
		int numSwaps = (int)(0.25*size);   //how many swap operations that need to be done of a certain array size.
		int sortTimes = 100;
		long startTime,endTime;       //a record for the start time and end time of the sorting method
		
		long[] timeData = new long[sortTimes];
		
		fillArray(arr);                  //fill array from 0 to size-1 in order
		swapArrayRandom(arr,numSwaps);   //randomly swap the array n times
		
		//test for merge sort
		for(int i=0; i<sortTimes; i++) {
			startTime = System.nanoTime();
			mergeSort(arr);
			endTime = System.nanoTime();
			if(!isSorted(arr)) {
				System.out.println("Merge Sort did not sort the Array properly.");
			}
			timeData[i] = endTime - startTime;
			swapArrayRandom(arr,numSwaps);
		}
		
		double mergeSortMean = arithmeticMean(timeData);
		System.out.println("Merge Sort average sorting " + size + " elemnts used time is: " + mergeSortMean + " nano Seconds\n");
		
		//test for merge sort inefficient
		for(int i=0; i<sortTimes; i++) {
			startTime = System.nanoTime();
			mergeSortInefficient(arr);
			endTime = System.nanoTime();
			if(!isSorted(arr)) {
				System.out.println("Merge Sort Inefficient did not sort the Array properly.\n");
			}
			timeData[i] = endTime - startTime;
			swapArrayRandom(arr,numSwaps);
		}
		
		double mergeSortInefficientMean = arithmeticMean(timeData);
		System.out.println("Merge Sort Inefficient sorting " + size + " elemnts average used time is: " + mergeSortInefficientMean + " nano Seconds\n");
		
		//test for quick sort
		for(int i=0; i<sortTimes; i++) {
			startTime = System.nanoTime();
			quickSort(arr);
			endTime = System.nanoTime();
			if(!isSorted(arr)) {
				System.out.println("Quick Sort did not sort the Array properly.\n");
			}
			timeData[i] = endTime - startTime;
			swapArrayRandom(arr,numSwaps);
		}
		
		double qucikSortMean = arithmeticMean(timeData);
		System.out.println("Quick Sort sorting " + size + " elemnts average used time is: " + qucikSortMean + " nano Seconds\n");
		
		//test for radix sort
		for(int i=0; i<sortTimes; i++) {
			startTime = System.nanoTime();
			radixSort(arr);
			endTime = System.nanoTime();
			if(!isSorted(arr)) {
				System.out.println("Radix Sort did not sort the Array properly.\n");
			}
			timeData[i] = endTime - startTime;
			swapArrayRandom(arr,numSwaps);
		}
		
		double radixSortMean = arithmeticMean(timeData);
		System.out.println("Radix Sort sorting " + size + " elemnts average used time is: " + radixSortMean + " nano Seconds\n\n");
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
	
	
/* **********************************************************************************************************************
 *                                        REPORT:
 *                                        
 * 1.
 *                             |    ArraySize    |    Time(ms)    |
 *    MergeSort                |      10000      |      0.88      |
 *    MergeSortInefficient     |      10000      |      0.97      |
 *    QuickSort                |      10000      |      0.62      |
 *    RadixSort                |      10000      |      1.13      |
 *    
 *    MergeSort                |      20000      |      1.26      |
 *    MergeSortInefficient     |      20000      |      1.53      |
 *    QuickSort                |      20000      |      1.08      |
 *    RadixSort                |      20000      |      1.47      |
 *    
 *    MergeSort                |      30000      |      1.87      |
 *    MergeSortInefficient     |      30000      |      2.23      |
 *    QuickSort                |      30000      |      1.65      |
 *    RadixSort                |      30000      |      1.61      |
 *        
 *    MergeSort                |      40000      |      2.54      |
 *    MergeSortInefficient     |      40000      |      2.97      |
 *    QuickSort                |      40000      |      2.20      |
 *    RadixSort                |      40000      |      2.08      |
 *    
 *    MergeSort                |      50000      |      3.22      |
 *    MergeSortInefficient     |      50000      |      3.78      |
 *    QuickSort                |      50000      |      2.81      |
 *    RadixSort                |      50000      |      2.63      |
 *    
 * 2. Merge Sort is slower than Quick Sort at array size of 10000. Merge Sort requires an additional array and Array copy operation
 *    while Quick Sort does everything within its array making it use less resource than the Merge Sort.
 *   
 * 3. The cost of using Merge Sort Inefficient is the new assigned temporary array that every time merge function called.
 *    It uses at least (log2(10000) = 13) 2^13 + 2^12 + ... + 2^0 new array with 10000 elements.
 *    
 * 4. Radix Sort is slower than Merge Sort at 10000 elements.
 * 
 * 5. The operation that slow radix sort was the additional array value assign operation. Every time going into a bucket needs
 *    to assign value to the temporary array and copy the value back to the original array.
 * **********************************************************************************************************************/

}
