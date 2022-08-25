import java.util.Scanner;

public class lab1 {

	public static int recCado(int n)
	{	
		int p = 0;
		int result;
		if(n<= 2)
		{		
		result = 1;
		}
		else
		{
			p = recCado(n-1);
			result = recCado(p)+ recCado(n-p);	
		}
			return result;	//one return statement
	}
	public static int interCado(int n)
	{
		int cadoArr[] = new int [n+1];
		
		cadoArr[0]= 1;
		
		if(n>= 1)
			cadoArr[1]= 1;
			if (n >= 2)
			cadoArr[2]= 1;
		
			for (int i = 3; i < n+1; i++)
			{
				cadoArr[i]= (cadoArr[cadoArr[i-1]])+ (cadoArr[i-(cadoArr[i-1])]);
			}
		return cadoArr[n];	//one return statement
					
	}
	public static void main(String[] args)
	{
		//for user input support
		Scanner input = new Scanner(System.in);
		System.out.println("Enter your desired Cado number! Warning if you enter a negative number "
				+ "the program will crash");
		int number = input.nextInt(); 			
		
		//for the recursive method
		long startTime, endTime, elapsedTime;
		startTime = System.nanoTime();
		int i = recCado(number);
		endTime = System.nanoTime();
		elapsedTime = endTime - startTime;
		System.out.println("The recusive method took " + elapsedTime+ " nanoseconds");
		System.out.println("The " + number + " Cado number is "  + i );
		
		//for the iterative method
		startTime = System.nanoTime();
		int n = interCado(number);
		endTime = System.nanoTime();
		elapsedTime = endTime - startTime;
		System.out.println("The iterative method took " + elapsedTime + " nanoseconds");
		System.out.println("The " + number + " Cado number is " + n );
	}
}