import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Random;

public class PeerToPeerNetwork {

    final int maxNumOfTransactions = 100;
    static Random randomAdd = new Random();
    static final int bound = 20;
    /*
    This function will create fake transactions for us to include in a block.
     */
    public ArrayList<Transaction> collectNewTransactions() {

        ArrayList<Transaction> txList = new ArrayList<>();
        Random randomAmount = new Random();

        int numOfTx = randomAdd.nextInt(maxNumOfTransactions);
        for(int i=0;i<numOfTx;i++){
            String fromAddress = generateRandomAddress();
            String toAddress = generateRandomAddress();
            BigInteger amount = BigInteger.valueOf(randomAmount.nextInt(bound)* A5HamptonEriq.SATOSHI);
            Transaction tx = new Transaction(fromAddress,toAddress,amount);
            txList.add(tx);
        }
        return txList;

    }

    private String generateRandomAddress() {
        //bitcoin addresses can contain alphanumeric values, but here we will use numeric addresses only for ease.
        StringBuilder address = new StringBuilder();
        address.append("1");//bitcoin addresses can start with 1, 3 or bc. We will use the most standard 1 addresses.
        for(int i=0;i<30;i++){
            address.append(randomAdd.nextInt(10));
        }
        return address.toString();
    }
}
