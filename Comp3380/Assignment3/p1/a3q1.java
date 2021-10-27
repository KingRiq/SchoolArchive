import javax.print.DocFlavor;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;


public class a3q1 {
    public static void main(String[] args) throws FileNotFoundException {


            //read files and create 2D arraylists
            File file1, file2;
            String input;
            Scanner sc = new Scanner(System.in);
            System.out.println("You can always press 'q' and enter to quit");
            do {
                System.out.println("Please type the name of the first file (include .txt)");
                input = sc.next();
                file1 = new File(input);
                if(input.equalsIgnoreCase("q"))
                    System.exit(0);
            } while (!file1.exists());

            System.out.println("File Found");

            do {
                System.out.println("Please type the name of the second file (include .txt)");
                input = sc.next();
                file2 = new File(input);
                if(input.equalsIgnoreCase("q"))
                    System.exit(0);
            } while (!file2.exists());
            System.out.println("File Found");

        ArrayList<ArrayList<String>> set1, set2;

        //fill them with data
        set1 = readFile(file1);
        set2 = readFile(file2);

        innerJoin(set1,set2);
        leftJoin(set1, set2);
        fullOuterJoin(set1, set2);
    }

    public static ArrayList<ArrayList<String>> readFile(File input) throws FileNotFoundException {
        ArrayList<ArrayList<String>> Table = new ArrayList<>();
        Scanner sc = new Scanner(input);

        while(sc.hasNextLine())
        {
            ArrayList<String> rows = new ArrayList<>();
            String i = sc.nextLine();
            String[] p = i.split(",");

            for(int q = 0; q< p.length; q++)
                rows.add(p[q]);

            Table.add(rows);
        }

        //no memory leaks
        sc.close();
        return Table;
    }

    public static void innerJoin(ArrayList<ArrayList<String>> Table1, ArrayList<ArrayList<String>>Table2)
    {
        String report = "--- Inner join ---\n";
        int size = 0;
        //which table is smaller
        for(int i = 1; i<Table1.size(); i++)
        {
            for(int j = 1; j<Table2.size(); j++) {
                if (Table1.get(i).get(0).equals(Table2.get(j).get(0))) {
                    for(int k = 0; k<Table1.get(i).size(); k++)
                    {
                        report += Table1.get(i).get(k)+
                                 ",";//+ Table2.get(j).get(k) + "\n";
                    }
                    for(int k = 0; k<Table2.get(j).size(); k++)
                    {
                        report += Table2.get(j).get(k);
                        if(k < Table2.get(j).size()-1)
                              report +=  ",";//+ Table2.get(j).get(k) + "\n";
                    }
                        report += "\n";
                }
            }
        }

        printReport(report);
    }

    public static void leftJoin(ArrayList<ArrayList<String>> Table1, ArrayList<ArrayList<String>>Table2)
    {
        int matches = 0;
        String report = "--- Left join ---\n";
        //get everything left and
        for(int i = 1; i<Table1.size(); i++)
        {
            matches = 0;
            for(int j = 1; j<Table2.size(); j++) {

                if (Table1.get(i).get(0).equals(Table2.get(j).get(0))) {
                    for(int k = 0; k<Table1.get(i).size(); k++)
                    {
                        report += Table1.get(i).get(k)+
                                ",";//+ Table2.get(j).get(k) + "\n";
                    }
                    for(int k = 0; k<Table2.get(j).size(); k++)
                    {
                        report += Table2.get(j).get(k);
                        if(k < Table2.get(j).size()-1)
                            report +=  ",";//+ Table2.get(j).get(k) + "\n";
                    }
                    report += "\n";
                    matches++;
                }
            }
            if(matches == 0)
            {
                for(int k = 0; k<Table1.get(0).size(); k++)
                {
                    report += Table1.get(i).get(k)+
                            ",";//+ Table2.get(j).get(k) + "\n";
                }
                for(int k = 0; k<Table2.get(0).size(); k++) {
                    report += "Null";
                    if(k < Table2.get(0).size()-1)
                        report +=  ",";
                }
                report += "\n";
            }
        }

        printReport(report);
    }
    public static void fullOuterJoin(ArrayList<ArrayList<String>> Table1, ArrayList<ArrayList<String>>Table2) {
        String report = "--- Full Outer join ---\n";
        int matches = 0;
        //get everything left and
        for(int i = 1; i<Table1.size(); i++)
        {
            matches = 0;
            for(int j = 1; j<Table2.size(); j++) {

                if (Table1.get(i).get(0).equals(Table2.get(j).get(0))) {
                    for(int k = 0; k<Table1.get(i).size(); k++)
                    {
                        report += Table1.get(i).get(k)+
                                ",";//+ Table2.get(j).get(k) + "\n";
                    }
                    for(int k = 0; k<Table2.get(j).size(); k++)
                    {
                        report += Table2.get(j).get(k);
                        if(k < Table2.get(j).size()-1)
                            report +=  ",";//+ Table2.get(j).get(k) + "\n";
                    }
                    report += "\n";
                    matches++;
                }
            }
            if(matches == 0)
            {
                for(int k = 0; k<Table1.get(0).size(); k++)
                {
                    report += Table1.get(i).get(k)+
                            ",";//+ Table2.get(j).get(k) + "\n";
                }
                for(int k = 0; k<Table2.get(0).size(); k++) {
                    report += "Null";
                    if(k < Table2.get(0).size()-1)
                        report +=  ",";
                }
                report += "\n";
            }
        }
        for(int i = 1; i<Table2.size(); i++) {
            matches = 0;
            for(int j = 1; j<Table1.size(); j++) {
                if (Table2.get(i).get(0).equals(Table1.get(j).get(0))) {
                    matches++;
                }

            }
            if(matches==0)
            {
                for(int k = 0; k<Table1.get(0).size(); k++) {
                    report += "Null"+ ",";
                }
                for(int k = 0; k<Table2.get(0).size(); k++)
                {
                    report += Table2.get(i).get(k);
                    if(k < Table2.get(0).size()-1)
                        report +=  ",";
                }
                report += "\n";
            }
        }
        printReport(report);
    }
    public static void printReport(String GoodMORNIN){
        System.out.println(GoodMORNIN);
    }
}


