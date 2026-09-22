import java.util.HashMap;

public class Bimap2<TA, TB> implements Twowaymap<TA,TB> {

    private HashMap<TA, TB> keystoval;
    private HashMap<TB,TA> valstokey;



    public Bimap2()
    {
        keystoval =new HashMap<TA,TB>();
        valstokey = new HashMap<TB,TA>();
    }
    @Override
public void set(TA x, TB y) {
    java.util.Objects.requireNonNull(x);
    java.util.Objects.requireNonNull(y);
    
    if(keystoval.containsKey(x)) {
        TB previous_value = keystoval.get(x);
        valstokey.remove(previous_value); 
    }

   
    if(valstokey.containsKey(y)) {
        TA previous_key = valstokey.get(y);
        keystoval.remove(previous_key);  
    }

    
    keystoval.put(x, y);
    valstokey.put(y, x);
}
  // insert or change pair, x,y must be non-null.
   @Override
   public TB get(TA x) {
    return keystoval.get(x);
   }// gets corresponding TB value given TA value x
    // returns null if no association is present

   @Override
   public TA reverse_get(TB x) {
    return valstokey.get(x);
   } // get TA value given TB value x

   @Override
   public TB removeKey(TA x) {
    TB value = keystoval.get(x);
    if(value !=null){
        keystoval.remove(x);
        valstokey.remove(value);
    }
    return value;
   }// remove pair associated with TA x as key,
    // returns TB value if present

    @Override
   public TA removeVal(TB y) {
    TA value = valstokey.get(y);
    if(value !=null)
    {
        valstokey.remove(y);
        keystoval.remove(value);
    }
    return value;
   }// remove pair associated with TB y as key,
    // returns TA value if present

   @Override
   public int size() {
    return valstokey.size();
}// number of pairs in map. (equal to number of keys)

    public static void main(String[] args)
    {
	// bijective map between letter grades and grade point values
	Bimap2<String,Double> GP = new Bimap2<String,Double>();
	String[] Grades = {"A","A-","B+","B","B-","C+","C","C-","D+","D","F"};
	Double[] Points = {4.0,3.7,3.3,3.0,2.7,2.3,2.0,1.7,1.3,1.0,0.0};
	for(int i=0;i<Grades.length;i++) GP.set(Grades[i],Points[i]);
	
    System.out.println("BEFORE: -------------------------------");
    for(String g:Grades) System.out.print(GP.get(g) + " ");
    System.out.println("");
	for(Double p:Points) System.out.print(GP.reverse_get(p)+ " ");	

	GP.set("A-",3.75); // CHANGE value of A- from 3.7 to 3.75
	GP.set("B+",3.25); // change value of B+ from 3.3 to 3.25
	GP.removeVal(1.3); // remove the D+ grade

    System.out.println("\nAFTER: --------------------------------");
    for(String g:Grades) System.out.print(GP.get(g) + " ");
    System.out.println("");
	for(Double p:Points) System.out.print(GP.reverse_get(p)+ " ");	

	System.out.println("\nThis should print 3.75: " + GP.get("A-")); // should print 3.75
	System.out.println("This should print A-: " + GP.reverse_get(3.75)); // should print A-
	System.out.println("This should print null: " + GP.get("D+")); // should print null
	System.out.println("This should print null: " + GP.reverse_get(1.3)); // null

	/// THIS ONE IS THE MOST IMPORTANT, EASY TO GET WRONG: ****

	System.out.println("3.7: "+GP.reverse_get(3.7)); 

        // This MUST PRINT null
	// because you already changed A- to correspond to 3.75, there
	// should be no value associated with 3.7.

        // Also be sure the check this one:  ****
	GP.set("A+",4.0); // this will also erase value for "A". why?
	System.out.println("This should print 10: " + GP.size());  // should print 10

	// Pay special attention to cases marked with **** above
    }//test

    /*
You can place this main in your public calss
public class Bimap<TA,TB> 
{ ...
}
                PART I IS DUE ONE WEEK FROM DATE ASSIGNED
*/

}
