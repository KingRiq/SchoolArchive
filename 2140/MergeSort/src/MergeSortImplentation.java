
public class MergeSortImplentation {
	/* mergeSort takes 4 parameters an arrange from the user Start and end
	 * represent the beginning and end of the array and temp which stores a[] into a temp array
	 */
	private static void mergeSort(int[] a, int start, int end, int[] temp)  //helper
	{
		int mid;
		if (1< end - start) //if one is less than length minus 0
		{	//if greater than one item in array
			mid = start + (end-start)/2; //add start (0) + (whatever because its greater than one item)
			//divides it in half getting MIDDLE INDEX
			mergeSort(a, start, mid, temp); //stores mid becomes new end essentially for this instance
			/*for (int i = 0; i < a.length ; i++)
				System.out.print(temp[i]);*/
			
			//mergeSort(a, mid, end, temp);   //THINK dude  same as line above but mid becomes the start 
			merge(a, start, mid, end, temp); //merge isnt created yet but stores 
			//user array start index mid index and end, indices and all the TEMPS created to merge
			// or even this particular temp
		}
	}
	public static void mergeSort(int[] a) //driver
	{
		int[] temp = new int[a.length]; //creates an array to store the two halves
		
		mergeSort(a, 0, a.length, temp); //grabs user array copies its creates and copies length to temp and set start to begining and end to a.length 
		// finally stores all of a into temp
		// REMEMBER END IS SET PAST LAST ITEM
		
		
	}
	// this function actually does all the sorting and merging LOL
	private static void merge (int[] a, 
				int start, int mid, int end, int[] temp)
	{
		/* ok so this accepts A[] (is the same probably to place it back into A[]
		 * the new values that is all starts mids and ends and temps
		 */
		
		//create 3 variables 
		int currL = start; //captures index of current item in left half
		int currR = mid;   //captures index of current item in right half
		int currT; 		   //index in temp
		for(currT = start; currT < end; currT++) //sets T = to start index of temp array
			//parameters if T is less than the last index then increment 1
		{
			if (currL < mid && (currR >= end || a[currL] < a[currR]))
			{	
				temp[currT] = a[currL]; //copies L current index into T at T's current position
				currL++; //moves it right one index
				//Id like to mention that after this T increments 1 as well
			}
			else // copy from the right half
			{
				temp[currT] = a[currR];
				currR++;
			}
		} //end for
		for(currT = start; currT < end; currT++)
			a[currT] = temp[currT];
	} //end merge
	public static void main(String[] args)
	{
		int[] myNums = {12, 1, 5, 9, 31, 2, 18, 91};
		
		mergeSort(myNums);
		
		for(int i =0; i < myNums.length; i++)
		System.out.println(myNums[i]);
	}
	
}
