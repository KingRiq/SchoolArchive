import java.util.Arrays;

// CLASS: GameLogicClass
//
// Author: Eriq Hampton
//
// REMARKS: Uses the gamelogic interface to run Connect Four
//  It decides turns and checks who won and ends
//-----------------------------------------

public class GameLogicClass implements GameLogic
{
    private HumanPlayer user;
    private AIPlayer ai;
    private Status[][] board;
    private Player pointer;

    public GameLogicClass()
    {
        user = new HumanPlayer();
        ai = new AIPlayer();
        startGame();
    }

    private void startGame()
    {
        setBoardSize();
        System.out.println("Starting game!");
        int x = (int)Math.round(Math.random());
        if(x == 0)
        {
            System.out.println("You go first");
            pointer = user;
        }
        else
        {
            System.out.println("Computer goes first");
            pointer = ai;
        }
        pointer.lastMove(-1);

    }

    //------------------------------------------------------
    // setAnswer
    //
    // PURPOSE:   Accepts player moves and checks if they won afterward. If not, then ask
    //            the other play to take it's turn.
    // PARAMETERS: int col - used to indicate the player's most recent move decision
    //
    // Returns: Nothing
    //------------------------------------------------------
    public void setAnswer(int col)
    {
        int posn = drop(col);

        if(pointer instanceof AIPlayer)
            board[posn][col] = Status.TWO;
        else
            board[posn][col] = Status.ONE;

        if(gameOver()!=null)
        {
            System.out.println(gameOver());
            if(gameOver() == Status.TWO)
            {
                pointer.gameOver(gameOver());
                System.out.println("Loss occurred at column " + (col+1));
            }
            //prompt user
            user.gameOver(gameOver());
        }
        else
        {
            changeTurn(pointer);
            pointer.lastMove(col);
        }
    }

    //------------------------------------------------------
    // setBoardSize
    //
    // PURPOSE:    picks a number between 6-12 and sets the board to that size
    // PARAMETERS: None
    //
    // Returns: Nothing
    //------------------------------------------------------
    private void setBoardSize()
    {
        int max = 12;
        int min = 6;
        int x = (int) (Math.random() * (max - min + 1) + min);
        user.setInfo(x, this);
        ai.setInfo(x, this);
        fillBoard(x);
    }

    //------------------------------------------------------
    // gameOver
    //
    // PURPOSE:    It checks the winning conditions for the connect four board.
    //             There are 4 ways the game ends. Vertical victory, Horizontal Victory,
    //             Diagonal Victory, and Draw.
    //
    // PARAMETERS: No parameters
    //
    // Returns: Uses methods to return the status of who won or if a draw occured. Null value
    //          indicates the game has not finished.
    //------------------------------------------------------
    private Status gameOver()
    {
        Status winner = null;

        if(checkLeft() != null)
            winner = checkLeft();

        if(checkUp() != null)
            winner = checkUp();

        if(rightDiagonal() != null)
            winner = rightDiagonal();

        if(leftDiagonal() != null)
            winner = leftDiagonal();

        if(checkfull())
            winner = Status.NEITHER;

        return winner;
    }

    //------------------------------------------------------
    // fillBoard
    //
    // PURPOSE:    Apart of board initialization. Used to fill the board
    // PARAMETERS: int size - used to set board to a specified size and fill it with unplayed positions
    //
    // Returns: Nothing
    //------------------------------------------------------
    private void fillBoard(int size)
    {
        board = new Status[size][size];

        for (Status[] s : board)
        {
            Arrays.fill(s, Status.NEITHER);
        }
    }

    //------------------------------------------------------
    // drop
    //
    // PURPOSE:    drops piece at the next available spot at the column given
    // PARAMETERS: int col - used to know which column to drop the piece
    //
    // Returns: returns position available if there is one
    //------------------------------------------------------
    private int drop(int col)
    {
        int posn = 0;

        while (posn < board.length && board[posn][col] == Status.NEITHER)
        {
            posn ++;
        }

        return posn-1;
    }

    //------------------------------------------------------
    // verifyCol
    //
    // PURPOSE:    checks if column is playable
    // PARAMETERS: int col - used to check column
    // Returns: returns true if column is playable.
    //------------------------------------------------------
    public boolean verifyCol(int col)
    {
        return (col >= 0 && col < board[0].length && board[0][col] == Status.NEITHER);
    }


    private Status checkLeft()
    {
        Status checkLeft = null;
        Status temp= null;
        for (int i = board.length-1; i>=0; i--)
        {
            for(int j = 3; j < board.length; j++)
            {

                if(board[i][j] != Status.NEITHER)
                {
                    temp = board [i][j];

                    if(temp == board[i][j-1] && temp == board[i][j-2] && temp == board[i][j-3])
                        checkLeft = temp;
                }
            }
        }
        return checkLeft;
    }

    private Status checkUp()
    {
        Status checkUp = null;
        Status temp= null;
        for (int i = board.length-1; i >= 3; i--)
        {
            for(int j = 0; j < board.length; j++)
            {
                if(board[i][j] != Status.NEITHER)
                {
                    temp = board [i][j];

                    if(temp == board[i-1][j] && temp == board[i-2][j] && temp == board[i-3][j])
                        checkUp = temp;
                }
            }
        }
        return checkUp;
    }

    private Status rightDiagonal()
    {
        Status rightDiagonal = null;
        Status temp = null;

        for (int i = board.length-1; i>=3; i--)
        {
            for(int j = 0; j< board.length-3; j++)
            {
                if(board[i][j] != Status.NEITHER)
                {
                    temp = board [i][j];
                    if(temp == board[i-1][j+1] && temp == board[i-2][j+2] && temp == board[i-3][j+3])
                        rightDiagonal = temp;
                }
            }
        }
        return rightDiagonal;
    }
    private Status leftDiagonal()
    {
        Status leftDiagonal = null;
        Status temp = null;

        for (int i = board.length-1; i>=3; i--)
        {
            for(int j=3; j< board.length; j++)
            {

                if(board[i][j] != Status.NEITHER)
                {
                    temp = board [i][j];
                    if(temp == board[i-1][j-1] && temp == board[i-2][j-2] && temp == board[i-3][j-3])
                    {
                        leftDiagonal = temp;
                    }
                }
            }
        }

        return leftDiagonal;
    }

    private boolean checkfull()
    {
        boolean draw = true;

        for(Status[] s: board)
        {
            for(Status i : s)
                if(i == Status.NEITHER)
                    draw = false;
        }
        return draw;
    }

    public void changeTurn(Player pointer)
    {
        if(pointer instanceof HumanPlayer)
            this.pointer = ai;
        else
            this.pointer = user;
    }

    //------------------------------------------------------
    // checkWin
    //
    // PURPOSE:    checks if the column passed results in a win
    // PARAMETERS:  int col - used to make temporary move for AI player
    //              checks if playing there wins the game for the AI
    //
    // Returns: returns true if playing a piece in the column passed results in a win
    //------------------------------------------------------
    public boolean checkWin(int col)
    {
        boolean winningPiece= false;
        int posn = drop(col);
        board[posn][col]= Status.TWO;

        if(gameOver() == Status.TWO)
            winningPiece = true;

        board[posn][col] = Status.NEITHER;
        return winningPiece;
    }

    //------------------------------------------------------
    // checkLoss
    //
    // PURPOSE:    Checks if the AI will lose if it neglects to pick the column passed to it
    // PARAMETERS: int col - makes temporary move for human and checks winning conditions.
    //
    // Returns: returns true if it is possible to lose if the AI neglects to pick this spot.
    //------------------------------------------------------
    public boolean checkLoss(int col)
    {
        boolean defensePiece= false;
        int posn = drop(col);
        board[posn][col]= Status.ONE;

        if(gameOver() == Status.ONE)
            defensePiece = true;

        board[posn][col] = Status.NEITHER;
        return defensePiece;
    }
}
