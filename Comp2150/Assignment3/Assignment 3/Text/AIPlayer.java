// CLASS: GameLogicClass
//
// Author: Eriq Hampton
//
// REMARKS: AI that uses player interface to play against human players
//
//-----------------------------------------

public class AIPlayer implements Player{
    private GameLogicClass game;
    private int size;

    //------------------------------------------------------
    // lastMove
    //
    // PURPOSE:     Indicates the end of the Human player move and prompts AI to make
    //              a turn. If it sees a move that will result in a win it will make it. If it sees a move
    //              that would result in it's loss it blocks that move. Otherwise it chooses randomly.
    // PARAMETERS: lastCol - Is used as a variable to indicate the AI's next move
    //
    // Returns: void (returns nothing)
    //------------------------------------------------------
    public void lastMove(int lastCol)
    {
        for(int i = 0; i< size; i++)
        {
            if(game.verifyCol(i))
            {

                if (game.checkLoss(i))
                {
                    lastCol = i;
                    break;
                }
                else if (game.checkWin(i))
                {
                    lastCol = i;
                    break;
                }
                else
                {
                    lastCol = (int) (Math.random() * ((size - 1) - 0 + 1) + 0);
                    while(!game.verifyCol(lastCol))
                        lastCol = (int) (Math.random() * ((size - 1) - 0 + 1) + 0);
                }
            }

        }
        game.setAnswer(lastCol);
    }

    public void gameOver(Status winner)
    {

    }
    public void setInfo(int size, GameLogic gl)
    {
        game = (GameLogicClass) gl;
        this.size = size;
    }

}
