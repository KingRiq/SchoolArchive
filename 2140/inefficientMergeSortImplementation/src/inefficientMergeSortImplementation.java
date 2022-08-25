public class inefficientMergeSortImplementation {
	 public static void mergeSortInefficient(int[] array) 
		{	
			if(array.length != 0)
			{
				mergeSortInefficient(array, 0, array.length-1);
			}		
			
		}
	
	 
    static void merge(int arr[], int start, int mid, int end) 
    { 
        int start2 = mid + 1; 
      
        
        if (arr[mid] <= arr[start2]) { 
            return; 
        } 
      
        
        while (start <= mid && start2 <= end) { 
      
        
            if (arr[start] <= arr[start2]) { 
                start++; 
            } 
            else { 
                int value = arr[start2]; 
                int index = start2; 
      
                 
                while (index != start) { 
                    arr[index] = arr[index - 1]; 
                    index--; 
                } 
                arr[start] = value; 
      
                // Update all the pointers 
                start++; 
                mid++; 
                start2++; 
            } 
        } 
    } 
      
    
    static void mergeSortInefficient(int arr[], int l, int r) 
    { 
        if (l < r) { 
      
            // Same as (l + r) / 2, but avoids overflow 
            // for large l and r 
            int m = l + (r - l) / 2; 
      
            // Sort first and second halves 
            mergeSortInefficient(arr, l, m); 
            mergeSortInefficient(arr, m + 1, r); 
      
            merge(arr, l, m, r); 
        } 
    } 
   
	public static void main(String[] args)
	{
		int[] myNums = {12, 130534, 5, 9, 31, 2, 18, 91, 500, 2305};
		
		mergeSortInefficient(myNums);
		
		for(int i =0; i < myNums.length; i++)
		System.out.println(myNums[i]);
	}
}
