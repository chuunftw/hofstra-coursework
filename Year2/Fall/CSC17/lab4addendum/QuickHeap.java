import java.util.Optional;
import java.util.function.Function;
import java.util.stream.Stream;

interface QuickHeap<KT,VT> {
    int size();
    Optional<KVPair<KT,VT>> pop();
    Optional<KVPair<KT,VT>> peek();
    Optional<VT> get(KT key);
    Optional<VT> remove(KT key);
  
    // but set should be implemented using a more general function
    Optional<VT> find_n_modify(KT key, VT default_val,
             Function<? super VT, ? extends VT> modifier);
    // This function should behave as follows: if the key isn't found, 
    // insert and associate it with the supplied default_val.
    // If the key currently maps to value v, change it to modifier.apply(v),
    // which will then entail readjusting the position of the entry in the
    // heap.  The function should return the previous value associated with
    // the key, if it exists.  For example, if key k is associated with 
    // Integer 2 then find_n_modify(k,default_val, (x->x+1)) should change
    // the value to Integer 3 and return Optional.of(2);
  
    default Optional<VT> set(KT key, VT val) {
  return this.find_n_modify(key, val, (x->val));
    } // then set can be implemented this way.
  
    // because the signature of the pop function has changed, the 
    // priority_stream function has to be implemented differently:
    default Stream<KVPair<KT,VT>> priority_stream() {
  //return Stream.generate( () -> pop().get() ).limit(size());
  return Stream.generate( () -> pop() )
      .flatMap(option -> option.stream()) //option can become stream
      .limit(size());   // Stream is also a monad, hence flatMap
    }//new priority_stream implementation (delete your old one)
  
  }// new QuickHeap interface.