interface Twowaymap<TA,TB> //bijective map between types TA and TB
{
   void set(TA x, TB y);  // insert or change pair, x,y must be non-null.

   TB get(TA x); // gets corresponding TB value given TA value x
                 // returns null if no association is present

   TA reverse_get(TB x); // get TA value given TB value x

   TB removeKey(TA x); // remove pair associated with TA x as key,
                                 // returns TB value if present
   TA removeVal(TB y); // remove pair associated with TB y as key,
                                 // returns TA value if present
   int size();   // number of pairs in map. (equal to number of keys)\
}
