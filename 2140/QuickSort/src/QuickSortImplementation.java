
public class QuickSortImplementation {
	public static void quickSort( int[] a)
	{
		quickSort(a, 0, a.length-1);
	}
	private static void quickSort(int[]a, int start, int end)
	{
		if( start < end)
		{
			for(int i =0; i < a.length; i++)
				System.out.print(a[i]+ ", ");
			System.out.println();
			choosePivot(a, start, end);
			int pi = partition(a, start, end);
			
			System.out.println("p= "+pi);
			quickSort(a, start, pi-1);
			System.out.println("Left side done");
			quickSort(a, pi + 1, end);			
		}
		
	}

		private static void choosePivot(int a[], int start, int end)
		{
			int temp;
			
			if(end - start <= 1)
			{
				if(a[start] > a[end])
				{
					temp = a[start];
					a[start] = a[end];
					a[end] = temp;
				}
				
			}
			else
			{
				System.out.println(start+ " |" + end);
				int pivot = (start + end) /2;
				System.out.println("pivot" +pivot);
				temp = a[start]; //stores start value in temp
				a[start] = a[pivot]; //start is now same as pivot
				a[pivot] = temp; //pivot is now
			}
			
			
		}
		
		private static int partition(int[] a, int start, int end)
		{
			int pivot = a[start];
			int curr = start + 1;
			int bigStart = start+1;
			int temp;
			
			System.out.println("Comparing" + pivot);
			for(int i =0; i < a.length; i++)
				System.out.print(a[i]+ ", ");
			System.out.println();
			for(curr= start; curr <= end; curr++)
			{
				//System.out.println(curr);
				
				if(a[curr] < pivot)
				{
					
					temp = a[bigStart];
					a[bigStart] = a[curr];
					a[curr]= temp;
					bigStart++;
					for(int i =0; i < a.length; i++)
						System.out.print(a[i]+ ", ");
						System.out.println();
				}
				
			}
			System.out.println();
			System.out.println("hi"+a[bigStart-1]);
			temp = a[bigStart-1];
			a[bigStart-1]= pivot;
			a[start]= temp;
			System.out.println(bigStart-1);
			return bigStart-1;
		}


public static void main(String[] args)
{
	int[] myNums = {1,5, -4, 7, -2, 420};
	
	quickSort(myNums);
	
	for(int i =0; i < myNums.length; i++)
	System.out.print(myNums[i]+ ", ");
}

}