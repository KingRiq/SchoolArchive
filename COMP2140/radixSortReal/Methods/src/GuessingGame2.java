import java.util.Scanner;

public class GuessingGame2 {
	
	static Scanner input = new Scanner(System.in);  
	static String answer;
	static int max, min, number, guess;
	
	public static void guessingGame()
	{	
		getGuess();
		
		if(number==guess)
		{
			System.out.println("Congrats, you got it"
				+ "\nThe answer was " + number);	
		}
		else
		{ 
			System.out.println("Nah dawg the answer is " + number
					+"\nYour guess was " + guess);
		}
	}
	
	
	public static int getRandomNumber(int max, int min)
	{
		return (int) (Math.random() * (max - min + 1)) + min;
	}
	
	public static int getGuess()
	{ 
		while(true)
		{
			
			System.out.println("Pick your a maximum number.");
			max = input.nextInt();
			System.out.println("Pick a minimum value greater than 0");
			min = input.nextInt();
			number = getRandomNumber(max, min);
			System.out.println("I'm thinking of a number between " + min + " and " + max );
			System.out.println("What's your guess fam?");
			guess = input.nextInt();
			if(guess < min || guess > max)
			{
				System.out.println("Fam..."
					+ " Thats outta the range, try again!");
			}
			else
			{
			return guess;
			}
		}
	}
	
	public static boolean askFor()
	{
		
		while(true)
		{
			System.out.println("Do you want to play another round breh? "
					+ "Type 'Y' if yes or 'N'");
			answer = input.next();
			/*if(!answer.equalsIgnoreCase("N") || !answer.equalsIgnoreCase("Y"))
			{
			System.out.println("Kek... you thought I'd fall for that "
					+ "\nTry again!");
			}
			else*/ if(answer.equalsIgnoreCase("Y"))
			{
				System.out.println("bet fam");
				return true;
			}
			else if(answer.equalsIgnoreCase("N"))
			{
				System.out.println("IIGHT IMMA HEAD OUT!!");
			return false;
			}
			
		}
	}
	
	
	public static void main(String[] args)
	{
		System.out.println("What's good! Wanna play a guessing game?");
		System.out.println("Too bad bitch I didn't feel like coding your response");
		do
		{
			guessingGame();
		}
		while (askFor());
		System.out.println("Peace out");
	}

}
	
