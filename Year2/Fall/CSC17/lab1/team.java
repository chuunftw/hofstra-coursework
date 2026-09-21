import java.lang.Double;

interface Playable
{
   void win();
   void lose();
   // optionally, you may also allow ties.
   void printrecord();
   void play(team x);
   double winningpercentage();
}

class team implements Playable {

  private int losses;
  private int wins;
  private String name;

  public team(String teamName) {
    name = teamName;
    losses = 0;
    wins = 0;
  }

  public void win() {
    wins += 1;
  }

  public void lose() {
    losses += 1;
  }

  public void printrecord() {
    System.out.println("W-L: " + wins + "-" + losses);
  }

  public void play(team x) {
    double LHS = Math.random();
    double RHS = Math.random();
    if ( (Double.compare(LHS, RHS)) < 0 ) {
      this.win();
      x.lose();
      System.out.println(this.name + " won!");
    }

    else {
      x.win();
      this.lose();
      System.out.println(x.name + " won!");
    }

  }

  public String playNoPrint(team x) {
    double LHS = Math.random();
    double RHS = Math.random();
    if ( ( Double.compare(LHS, RHS)) < 0) {
       this.win();
       x.lose();
       return this.name;
    }

    else {
       x.win();
       this.lose();
       return x.name;
    }
  }

  public double winningpercentage() {
    int total = this.wins + this.losses;
    return (double)(this.wins) / total;

  }

  public static String WRSorter(team[] myList)
  {
    boolean swapped;
    int i, j;
    team temp;


    for (i = 0; i < myList.length - 1; i++)
    {
        swapped = false;
        for (j = 0; j < myList.length - i - 1; j++)
        {
            if (myList[j].wins> (myList[j + 1].wins) )
            {
                temp = myList[j];
                myList[j] = myList[j + 1];
                myList[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped)
        {
            break;
        }
    }


    String sortedList = "";
    for (int k = myList.length-1; k>0; k--)
    {
        sortedList += myList[k].name + "\n";
    }

    return sortedList;
  }

// HERE --------------------------------------------------------

  public static void gameTimeBaby() {
    System.out.println("Time for a tournament who are your bets on? Heres our teams... ");
    String[] fbn = {"Giants","Jets","Rams","Patriots","Falcons","Steelers","Packers","Eagles",
    "Chiefs","Bills","Seahawks","Cowboys","Chargers","Raiders","Dolphins","Saints","49ers","Broncos"};
    team[] myList = new team[fbn.length];
    for (int i=0; i<fbn.length; i++) {
      myList[i] = new team(fbn[i]);
      System.out.println(fbn[i]);
    }

    for (int i=0; i<fbn.length; i++) {
      for (int j=0; j<fbn.length; j++) {
        if (i != j) {
          myList[i].playNoPrint( myList[j] );
        }

      }
    }
    team tempTeam = myList[0];
    for (int i=0; i<myList.length; i++) {
      if (Double.compare( ( myList[i].winningpercentage() ), ( tempTeam.winningpercentage() ) ) > 0 ) {
        tempTeam = myList[i];
      }
    }
    System.out.println("------------Here are the results!--------------");
    System.out.println("Team with the highest win rate is: " + tempTeam.name);

    System.out.println("The teams in order of highest win rate is: \n" + WRSorter(myList) );
  }


  public static void main(String[] args) {
    System.out.println("--------Part 1!--------");
    team team1 = new team("Testgiants");
    team team2 = new team("Testjets");
    team1.lose();
    team2.win();
    team2.lose();
    team2.printrecord(); // should print "W-L: 1-1"
    team1.play(team2); // should print "giants win" or "jets win"
    System.out.println(team1.winningpercentage()); // prints .000 to 1.00
    System.out.println("-------Part 1 End!------ \n");
    gameTimeBaby();

  }

}
