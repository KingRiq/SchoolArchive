import java.util.Scanner;

public class GuessingGame {
	
	static Scanner input = new Scanner(System.in);
	static boolean playing = true;
	public static void main(String[] args)
	{
		System.out.println("Let's play a guessing game!");
		while(playing)
		{
			gameGuess();
		}
		System.out.println("Thanks for playing");
	}
	public static void gameGuess()
	{
		int number;
		int guess;
		String answer = "";
		boolean playAgain = false;
			
			System.out.println("I am thinking of a number between 1 through 10"); 
			number = (int) (Math.random() * 10) + 1; //random number created
			System.out.println("What do you think it is?");
			guess= input.nextInt(); //guess
			//checks guess
			if(guess < 1  || guess > 10)
			{
			System.out.println("Nah dawg go ahead and try that again");
			}
			else //guess checks out compare it
			{
				if(guess == number)
				{
				System.out.println("You got it right fam!");
				}
				else
				{
				System.out.println("Nah dawg" + "\nYou answered: "
						+ guess + "\nThe number is actually " + number);
				}
			}
			System.out.println("Would you like to play again? type 'Y' or 'N'");
			answer= input.next();
			if(answer.equalsIgnoreCase("Y"))
			{
				System.out.println("Ok, cool");
			}
			else if(answer.equalsIgnoreCase("N"))
			{
				System.out.println("iight Imma head out");
				playing = false;
			}
	}
}
		

