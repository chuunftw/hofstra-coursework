import java.util.HashMap;
import java.util.Comparator;
import java.util.stream.Stream;

/*
==========================   PART 2   ==========================

Now for the main event: you have to implement a hybrid data structure
that combines the advantages of a priority heap with that of a hashmap.

The one glaring problem with binary heaps is that Search remains O(n),
whereas for a hash table, it's (average-case) O(1).  The theoretical
worst-case is O(n) but such cases are rarely encountered in practice.

We want to associate each value in a heap with a key that can be hashed
to look up the location of the value in the heap tree (its array index).
This will make search average-case O(1). We can then also write functions
to modify the priority of objects, or to remove objects, in (average case) 
O(log n) time.

Entries in the heap come in the form of "key-value pairs":
*/

record KVPair<KT,VT>(KT key, VT val) {
    @Override
	public String toString() { return key+":"+val; }
}

/*
The keys of type KT are to be hashed, while the values of type VT 
are to be Comparable (see skeleton below).  The idea is to keep a
hashmap, not from keys directly to the values but from keys to the
*indices* of where in heap the values are located.  The trick is to
keep this information consistent when values are swapped up and down
the tree.  Each time a swap operation is made, you must also change
the association between the keys and the indices of each pair of values.
Since the basic hashing operations are practically O(1), this is an
acceptable overhead.

You will need to study my implementation of the Heap data structure and
adopt the code accordingly.

You will complete the implementation of the following class, with dummy
procedures currently implemented (please don't leave any dummies).
*/

public class HashedHeap<KT,VT extends Comparable<? super VT>> {

  KVPair<KT,VT>[] Entries;  // the heap tree (I call it "H").
  int size=0;
  public int size() {return size;}

  Comparator<KVPair<KT,VT>> cmp = (a,b) -> a.val().compareTo(b.val());
  // comparator is set to behave for a maxheap by default.

  HashMap<KT,Integer> keymap;  // maps keys to indices in Entries array

  @SuppressWarnings("unchecked")
  KVPair<KT,VT>[] makearray(int cap) {
  return (KVPair<KT,VT>[]) new KVPair[cap];	
  }

  // write reasonable constructor(s) that allow both max and min heaps:
  public HashedHeap(boolean maxheap) {
    keymap = new HashMap<KT,Integer>();
    Entries = makearray(16);
    if (maxheap) {
      cmp = (x, y) -> x.val().compareTo(y.val()); 
  } else {
      cmp = (x, y) -> y.val().compareTo(x.val());
  }
  /* this is just a skeleton. You'll have to fill in the details */
  }

  // write a resize function that double capacity when needed.
  public int resize(int percent) {
    int newcap = Math.max(1, (int) ((long) Entries.length * percent / 100));
    if (newcap < size || percent < 1) {
        return Entries.length;
    }
    
   
    KVPair<KT, VT>[] newEntries = makearray(newcap);
    System.arraycopy(Entries, 0, newEntries, 0, size);
    Entries = newEntries; 

    
    HashMap<KT, Integer> newkeymap = new HashMap<>(keymap.size() * 2);
    newkeymap.putAll(keymap);
    keymap = newkeymap;
    
    return newcap;
}
  // Complete the following, which are currently dummies:

  private int left(int i) { return 2 * i + 1; }
  private int right(int i) { return 2 * i + 2; }
  private int parent(int i) { return (i - 1) / 2; }

  private int swapup(int i) {
      int pi = parent(i);
      while (i > 0 && cmp.compare(Entries[i], Entries[pi]) > 0) {
          KVPair<KT, VT> tmp = Entries[i];
          Entries[i] = Entries[pi];
          Entries[pi] = tmp;

          keymap.put(Entries[i].key(), i);
          keymap.put(Entries[pi].key(), pi);

          i = pi;
          pi = parent(i);
      }
      return i;
  }

  private int swapdown(int i) {
      int sc = 0; // swap candidate index, initially 0 to start while loop
      while (sc >= 0) {
          sc = -1; // this means stop swapdown
          int li = left(i);
          int ri = right(i);
          if (li < size && cmp.compare(Entries[i], Entries[li]) < 0) sc = li;
          if (ri < size && cmp.compare(Entries[li], Entries[ri]) < 0 && cmp.compare(Entries[i], Entries[ri]) < 0) sc = ri;
          if (sc >= 0) { // swap candidate is valid
              KVPair<KT, VT> tmp = Entries[i];
              Entries[i] = Entries[sc];
              Entries[sc] = tmp;
              keymap.put(Entries[i].key(), i);
                keymap.put(Entries[sc].key(), sc);
                i = sc;
            }
        }
        return i; // final position of i
    }


    private void push(KT key, VT val) {
      if (key == null || val == null) return;
  
      // Step 1: Resize if Entries is full
      if (size == Entries.length) {
          resize(200); // Resize with a 200% increase
      }
  
      // Step 2: Add new element to Entries
      KVPair<KT, VT> newPair = new KVPair<>(key, val);
      Entries[size] = newPair; // Place at the end of the array
      keymap.put(key, size);   // Update keymap with the index
  
      // Step 3: Heapify up to maintain heap order
      swapup(size);
      
      // Step 4: Increment the size
      size++;
  }
  /*
    This function should push a new KVPair<KT,VT>(key,val) into
    the heap, and record in the HashMap called keymap where in the
    Entries array it's located.  When this information changes for
    any entry due to swapping, the keymap must be updated.
    */
    // must run in amortized, average-case O(1) time, worst-case O(log n)
      // This function is private: see the public version "set" below:

  public KVPair<KT,VT> pop() {
  KVPair<KT,VT> answer = null; // returned if heap is empty
  /*
    This function should remove the key-value pair that has the
    highest priority, and return it.  This dummy always returns null.
    The keymap must always be update accordingly.
    */
    if(Entries.length <= 0 || size<=0) return answer;
    answer = Entries[0];
    keymap.remove(answer.key());
    size--;
    if (size > 0) {
        Entries[0] = Entries[size];
        keymap.put(Entries[0].key(), 0);
        swapdown(0);
    }
    Entries[size] = null;

  return answer;
  }  // must run in O(log n) time

  public KVPair<KT,VT> peek() {
    
  /*  This function should return the highest priority pair without delete
    */
    if (size<=0) return null;
    return Entries[0];


  }

  public VT get(KT key) {
    /*
      Find and return the value associated with the key, return 
            null if not found.  This dummy can't find anything but you can.
     */
          Integer index = keymap.get(key);
          if (size<=0 || index == null || Entries[index].val() == null ) return null;
  
    return Entries[index].val();
      } // must run in (average case) O(1) time.

      public VT remove(KT key) {
        if (keymap.get(key) == null) return null;
        
        int heapNode = keymap.get(key);
        VT val = Entries[heapNode].val();
        
        // Move the last element to the position of the removed element
        size--;
        keymap.remove(key);
        if (heapNode < size) {
            Entries[heapNode] = Entries[size];
            keymap.put(Entries[heapNode].key(), heapNode);
            swapdown(swapup(heapNode));
        }
        Entries[size] = null;

        return val;
    } // must run in O(log n) time

  public VT set(KT key, VT val) {
    if (key == null || val == null) return null;
  /*
    Change the value associated with the key.  Return the
    previous value.  First locate the entry using the
    keymap. After changing the value, you will need to either
    swap it up or down the tree.

    If there is no such key in the structure, this function should
    behave like push.  Note that push is private and should not
    be called externally, lest it introduces conflicting keys into
    the structure.  Users must call set, which should guarantee that
    there are no duplicate keys.
    */
    if (keymap.get(key) == null) {
      this.push(key, val);
      return null;
    }
    int heapNode = keymap.get(key);
    VT val1 = Entries[heapNode].val();
    Entries[heapNode] = new KVPair<KT, VT>(key,val);
    
    if (cmp.compare(Entries[heapNode], Entries[parent(heapNode)] ) > 0)
    {
      swapup(heapNode);
    }
    else if ((left(heapNode) < size && cmp.compare(Entries[heapNode], Entries[left(heapNode)]) < 0) || (right(heapNode) < size && cmp.compare(Entries[heapNode], Entries[right(heapNode)]) < 0)) 
    {
        swapdown(heapNode);
    }


    return val1;

} // must run in amortized worst-case O(log n) time.

  // The following will create a consuming stream in order of
  // priority, after you've completed the implementation
  public Stream<KVPair<KT,VT>> priority_stream() {
  return Stream.generate( () -> pop() ).limit(size);
  }

  

  public static void main(String[] args) {
  // the default constructor should create a maxheap
  var GPA = new HashedHeap<String,Double>(true); 
  String[] names = {"Mary","Larz","Narx","Parv","Haten","Isa","Nev"};
  for(var n:names) GPA.set(n, ((int)(Math.random()*401))/100.0);

  //  this should print from highest to lowest GPA
  //GPA.priority_stream().forEach(System.out::println);
  //  but GPA will be empty afterwards.

  GPA.set("Nev",0.0);
  GPA.set("Mary",4.0);
  GPA.remove("Isa");  

  System.out.println(GPA.get("Mary"));
  System.out.println(GPA.get("Narx"));	
  System.out.println(GPA.get("Isa"));	

  GPA.priority_stream().forEach(System.out::println);
  // should reflect new priorities ...
  }//main
    
}//HashedHeap

