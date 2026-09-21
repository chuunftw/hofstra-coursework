/*                          CSC17 Lab3b.  

                       Enhanced Circular Queue.

    A Circular Queue supports the following amortized O(1) operations:

    push (add to front)
    enqueue  (add to back)

    and the following worst-case O(1) operations:
   
    pop  (remove from font)
    dequeue  (remove from back).
    get(i)   (returns ith value from font)
    set(i,x) (changes ith value to x)

    A circular queue out-performs a doubly linked-list in terms of:

     1. amortized time complexity.
     2. memory overhead
     3. get/set operations are O(1)

    The purpose of this lab is to implement a SORTED circular queue
    by writing a subclass of CQ, with skeleton provided below ...
*/

import java.util.Comparator;
import java.util.Iterator;
import java.util.stream.*;

class OrderedCQ<T extends Comparable<? super T>> extends CQ<T> 
		                                 // implements OrderedQueue<T>
{
    protected boolean sorted = true;
    protected Comparator<T> cmp = (x,y) -> x.compareTo(y);

    public OrderedCQ(int cap) {
      super(cap);
	if (cap<1) cap = 16;
	Q = makearray(cap);
	front = size = 0;
    }

    @SuppressWarnings("unchecked")
    @Override
    T[] makearray(int n) 
    { // create a generic array, get compiler warning
        return (T[]) new Comparable[n];   // this is a weakness of java
    }

    
    //#1
    public boolean is_sorted()
    {
      if (lock) {
        throw new IllegalStateException("Cannot modify the queue during iteration.");
    }
      return sorted;
    }

    @Override
    public boolean push(T x)
    {
      if (lock) {
        throw new IllegalStateException("Cannot modify the queue during iteration.");
    }
        if (x==null) return false;
        super.push(x); 
        if (sorted && size>1 && cmp.compare(Q[aindex(0)],Q[aindex(1)])>0)
        {
            sorted = false;
        }
	      return true;
    }
    
    
    @Override
    public boolean enqueue(T x) 
    {
      if (lock) {
        throw new IllegalStateException("Cannot modify the queue during iteration.");
    }
        if(x==null) return false;
        super.enqueue(x);
        if(sorted && size > 1 && cmp.compare(Q[aindex(size-1)],Q[aindex(size-2)])>0)
        {
            sorted = false;
        }
        return true;
    }

    //#2
    public int search(T x) {
      if (lock) {
          throw new IllegalStateException("Cannot modify the queue during iteration.");
      }
  
      if (!is_sorted()) {
          return -1;
      }
  
      int min = 0;
      int max = size;
      int answer = -1;
  
      
      while (min < max && answer < 0) {
          int mid = (min + max) / 2;
          if (cmp.compare(x, Q[aindex(mid)]) == 0) { 
              answer = mid;
          } else if (cmp.compare(x, Q[aindex(mid)]) < 0) {
              max = mid;
          } else {
              min = mid + 1;
          }
      }
      return answer;
  }
  

    
    //#3
    public int insert_sorted(T x) {
      if (lock) {
        throw new IllegalStateException("Cannot modify the queue during iteration.");
    }
      int i = 0; 
      if (!is_sorted()) {
          return -1;
      }  
      if (size() >= capacity()) {
          resize();
      }
      push(x);
      while(i < size() - 1 && cmp.compare(Q[i], Q[i + 1]) > 0) 
      {
          T temp = Q[i];
          Q[i] = Q[i + 1];
          Q[i + 1] = temp;
          i++;
      }
      return i;
  }
  //#4
  public T remove_at(int i,boolean order)
  {
    if (lock) {
      throw new IllegalStateException("Cannot modify the queue during iteration.");
  }
    if(i<0 || i>=size())
    {
      return null;
    }
    T val = Q[i];
    if(order)
    {
      for(int j =i;j<Q.length-1;j++)
      {
        Q[j] = Q[j+1];
      }
      Q[size()-1] = null;
      size--;
    }
    else
    {
      Q[i] = Q[size()-1];
      Q[size()-1] = null;
      size--;
      sorted = false;
    }
    return val;
  }


  //#5
  private boolean lock = false;
  @Override
  public Iterator<T> iterator() {
    lock = true;  // Lock the queue during iteration
    return new Iterator<T>() {
        private int currentIndex = 0;
        
        public boolean hasNext() {
            return currentIndex < size;
        }
        
        public T next() {
      
            return Q[(front + currentIndex++) % Q.length];
        }
        
    };
}
  


  


}// SortedCQ


/*
=============================================================================

Your assignment is to complete the above skeleton and mplement the following 
interface:
*/
interface OrderedQueue<T> 
{
    boolean is_sorted(); // determines if queue is sorted in increasing order
    int search(T x); // search for x, returns virtual index or -1 if not found
    int insert_sorted(T x); // insert new x into a sorted queue
    T remove_at(int i, boolean order);  // removes ith value (see below)
    default void sort() {
        if (!is_sorted())
          System.err.println("OrderedQueue::sort is not implemented");
    } // (OPTIONAL) sorts queue if it's not sorted
}  // see further details below:
/*
1. public boolean is_sorted():

  This function should return true if the list is sorted (and false
  otherwise).  You could write an O(n) loop to check if the values are
  sorted, but the objective of this assignment is to maximize
  efficiency (and still be correct): it would be faster to maintain a
  boolean flag in your class: protected boolean sorted; which
  initially is set to true.  But as soon as the second value is
  inserted into the Q, we must check if the queue is still sorted.
  This will require you to also @Override the push, enqueue and set
  methods of the superclass CQ.  push needs to check if the new value
  is less than the original front value, and enqueue needs to check if
  the new value is greater than last value, and set the sorted boolean
  flag accordingly.  The set function needs to check if the new value
  is greater than the value to the left and less than the value
  on the right (if either exists).  You don't have to rewrite the
  entire function because you can still invoke the superclass version
  of the function while overriding it.  I will do push for you:

    @Override
    public boolean push(T x) { //assuming CmpCQ is name of your class
    {
        if (x==null) return false;
        super.push(x); // invokes inherited version of push
        if (sorted && size>1 && cmp.compare(Q[aindex(0)],Q[aindex(1)])>0)
            sorted = false;
	return true;
    }
  Once you've modified (@Override) push/enqueue, your is_sorted function can 
  just return the value of the boolean variable.

  Your new versions of push/enqueue should must still run in amortized
  constant time.

  *** Your is_sorted() function must run in O(1) time ***


2. public int search(T x):
  
  This function searches for x in the queue, but more precisely it
  searchs for the presence of a value y such that x.compareTo(y)==0.
  The function should return the (virtual) index at which y was found.  It
  should return -1 if no such y was found.
  
  YOUR FUNCTION MUST:

  * run in O(log n) time if the queue is sorted
  * run in O(n) time if the queue is not sorted

This means you need to implement binary search if the queue is sorted. You
can do a brute force O(n) search if the queue is not sorted.
I'll write binary search for you in Python, which you must adopt not only
to Java but to the circular queue setting:

  def binsearch(x,A): # search for x in sorted array A:
    min,max = 0,len(A)  # range of indices to search, between min and max-1
    answer = -1   # value to be returned
    while min<max and answer<0:
       mid = (min+max)//2   # middle index of partition
       if x==A[mid]: answer=mid
       elif x<A[mid]: max = mid
       else:  min = mid+1
    # end while
    return answer

3. int insert_sorted(T x); // insert new x into a sorted queue

   This function should insert x into a sorted queue, keeping it sorted.
   This function must call resize() first if current capacity is exceeded.
   It should return the virtual index of the inserted value.  If the
   queue is not sorted, the function should not insert x anywhere, and 
   return -1;  By "virtual index" I mean 0 if it's the first element,
   size-1 if it's the last, etc.

   This function should run in O(n) time.

   Hint: the easiest way to implement this function is to first push x
   to the front of the queue (which also resize() if needed).  Then
   swap it with the adjacent value to its right if it's not in the
   right order -- like in bubblesort -- and keep swapping until it's
   in the right position where it's less than or equal the value to
   its right, if there is one.  A more efficient way to implement it,
   however, is to first find the index where it should be inserted,
   then shuffle values to the right or left, depending on whether the
   index is closer to the front or end.  Both algorithms are O(n) but
   one will have fewer memory writes, which are more expensive then
   memory reads.

4. T remove_at(int i, boolean order); // remove and return ith value

   This function should return the ith value and remove it from the queue.
   If the index i is invalid, return null.  The boolean flag order 
   indicates whether it's necessary to keep the values in the queue in their
   current order. If order is false, you can just take a value from the
   front or back and plug it into the "hole."  However, if order is true,
   then you must shuffle other values into place.  If order is false, this
   function may also affect the sorted flag.
   This operation is therefore O(1) if order==false and O(n) if order==true.
   Note that it's possible to set order=true even for an unsorted queue.

5. The Iterator implementation of the superclass CQ does not adequately 
   protect against concurrent modification.  One should not be able to
   modify the queue in any way while iterating over it.  Checking the
   size is not enough.  It's not enough to defend against using the set
   method, nor against something like:

      for(var x:queue) {
         queue.add(x);
	 queue.pop();
      }
 
   This won't change the size of the queue between iterations but it still
   distorts the queue and makes the iteration invalid.  You need to prevent
   this from happening.  The idea is to insert a boolean flag `lock` into the
   class (your subclass).  Then all methods that modify the queue must
   check this flag, and if it is locked, then an exceptiong should be thrown.

6. public void sort(): (OPTIONAL)

  This function sorts the Queue (destructively, in place).  This
problem is optional.  However, if you do implement it you must use an
algorithm with average-case time complexity of at most O(n log n). You
need to adopt the algorithm to the circular queue setting.  Of course,
if the boolean sorted flag is already true, sort() should do nothing.  
If you choose not to do this option, the interface does contain a default
dummy implementation just so your program will still compile.

---
To test that your program is working correctly, you also need a function
(not in the interface) that brute-forces a check of if the queue is sorted
using a O(n) loop

Be sure to test your implementions with appropriate test code.
*/



public class lab3b {
  public static void main(String[] args) {
      OrderedCQ<Integer> q = new OrderedCQ<>(1);
      
      //#1 test
      for (var x:new Integer[]{2, 4, 6, 8, 10}) q.enqueue(x);
      for (var x:new Integer[]{1, 3, 5, 7, 9}) q.push(x);

      
      System.out.println("sorted after adding? " + q.is_sorted());

     
      q.enqueue(15);
      
      
      System.out.println("Current queue contents:");
      for (int x = 0; x < q.size(); x++) {
          System.out.print(q.get(x) + " ");
      }
      System.out.println();
      System.out.println("Is sorted after enqueuing? " + q.is_sorted());

      //#2 test
      
      Integer searchValue = 5;
      int searchResult = q.search(searchValue);
      System.out.print("Searching for " + searchValue + ": ");
      if (searchResult >= 0) 
      {
          System.out.println("Found at index " + searchResult);
      } 
      else 
      {
          System.out.println("Not found");
      }      

      // #3 test
      System.out.println("Inserting # into sorted queue:");
      q.insert_sorted(4);
      for (int i = 0; i < q.size(); i++) 
      {
          System.out.print(q.get(i) + " ");
      }
      System.out.println();

      //#4 test
      int removeIndex = 3;
      System.out.println("Removing value at index " + removeIndex + ": " + q.remove_at(removeIndex, true));
      for (int i = 0; i < q.size(); i++) 
      {
          System.out.print(q.get(i) + " ");
      }
      System.out.println();

      //#5 test 
      System.out.println("Lock test");
      Iterator<Integer> iterator = q.iterator();
      while (iterator.hasNext()) {
          System.out.println(iterator.next());
          try {
              q.push(20); 
          } catch (IllegalStateException e) 
          {
              System.out.println("Exception: " + e.getMessage());
          }
      }
      
      
  }
}



