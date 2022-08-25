// CLASS: Human Player
//
// Author: Eriq Hampton
//
// REMARKS: Utilizes the player and human interface to prompt
//  user for their turn
//-----------------------------------------
public class HumanPlayer implements Human, Player
{
    private SwingGUI UI;
    private GameLogic gl;

    public HumanPlayer()
    {
        UI = new SwingGUI();
    }

    public void setAnswer(int p)
    {
        gl.setAnswer(p);
    }

    public void lastMove(int lastCol)
    {
        UI.lastMove(lastCol);
    }

    public void gameOver(Status winner)
    {
        UI.gameOver(winner);
    }

    public void setInfo(int size, GameLogic gl)
    {
        UI.setInfo(this, size);
        this.gl = gl;
    }

}
