import java.util.Optional;
import java.util.function.Supplier;

interface BijectiveMap<TA,TB> //bijective map between types TA and TB
{
   void set(TA x, TB y);  // insert or change pair, x,y must be non-null.

   Optional<TB> get(TA x); // gets corresponding TB value given TA value x
                 // returns null if no association is present

   Optional<TA> reverse_get(TB x); // get TA value given TB value x

   Optional<TB> removeKey(TA x); // remove pair associated with TA x as key,
                                 // returns TB value if present
   Optional<TA> removeVal(TB y); // remove pair associated with TB y as key,
                                 // returns TA value if present
   int size();   // number of pairs in map. (equal to number of keys)

   //You may find these useful:

   static <T> Optional<T> on_behalf(Supplier<? extends T> s) {
       if (s==null) return Optional.empty();
       else return Optional.ofNullable(s.get());
       // .ofNullable will return Optional.empty() if argument is null
   }// on_behalf: call as BijectiveMap.on_behalf outside of interface

   static <T> Optional<T> try_on_behalf(Supplier<? extends T> s) {
       Optional<T> answer = Optional.empty();
       try {
	   answer = on_behalf(s);
       }
       catch (Exception e) {}
       return answer;
   }//try_on_behalf
   
}
