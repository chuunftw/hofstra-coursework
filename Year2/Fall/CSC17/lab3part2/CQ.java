/*  Circular Queue Implementation

    Includes demonstration of Iterable and Iterator and Stream interfaces
*/
import java.util.stream.Stream;
import java.util.stream.StreamSupport;
import java.util.Iterator;
import java.util.Optional;   // lightly used here
//import java.util.function.*;

public class CQ<T> implements Iterable<T> {
    protected T[] Q; // the underlying array.  Q.length is capacity
    protected int front=0; // index of first value, actual index of virtual 0
    int size = 0;

    public CQ(){ this(16); }
    public CQ(int n) {
        if (n<1) n = 16; // default cap
        Q = makearray(n);
    }  // constructor

    @SuppressWarnings("unchecked")
    T[] makearray(int n) { // create a generic array, get compiler warning
        return (T[]) new Object[n];   
    }

    // virtual to actual index
    protected int aindex(int vindex) {
        return (front+vindex) % Q.length;
    }
    // actual index to the "right" of actual index ai
    protected int right(int ai) {
        return (ai+1) % Q.length;
    }
    // actual index to the "left" of actual index ai
    protected int left(int ai) {
        return (ai+Q.length-1) % Q.length;
    }

    // first actual index is aindex(0);
    // last actual index in Q is aindex(size-1)
    // actual and virtual indices are the same if front==0
    // call the front "left", end "right".

    // get ith element (unchecked)
    public T get(int i) { return Q[aindex(i)]; } // may throw exception

    // change value at virtual index i to x, return previous value.
    // bounds checked.
    public T set(int i, T x) {
        if (i<0 || i>=size || x==null) {
            System.err.println("CQ::set called on invalid args"); //to stderr
            return null; // don't allow
        }
        int ai = aindex(i);
        T answer = Q[ai];
        Q[ai] = x;
        return answer;
    }

    // checked version of get, will not return null
    public Optional<T> try_get(int i) {
	if (i<0 || i>=size) return Optional.empty();
	else return Optional.ofNullable(Q[aindex(i)]);
    }

    protected void resize() { // double capacity
        T[] Q2 = makearray(Q.length*2);
        for(int i = 0;i<size; i++) 
            Q2[i] = Q[aindex(i)];
        Q = Q2;  // previous array GC'ed.
        front = 0; // reset front to zero
    }

    // add to right end, returns true if x is not null
    public boolean add(T x) {
        if (x==null) return false; // don't allow null
        if (size>=Q.length) resize();
        size++;
        Q[aindex(size-1)] = x;
        return true;
    }//add
    public boolean enqueue(T x) { return add(x); } // alias for add

    // delete from right end
    public T dequeue() {
        if (size<1) return null; // using null to represent something
        T answer = Q[aindex(size-1)];
        Q[aindex(size-1)] = null; // inform GC
        size--;
        return answer;
    }

    // push in front, returns true on success
    public boolean push(T x) {
        if (x==null) return false; // don't allow null
        if (size>=Q.length) resize();
        front = left(front); // possible wrap around to left.
        Q[front] = x;
        size++;
        return true;
    }

    // pop from front
    public T pop() {
        if (size<1) return null;
        T answer = Q[front];
        Q[front] = null; // inform garbage collector.
        front = right(front);
        size--;
        return answer;
    }

    public int size() { return size; }
    public int capacity() { return Q.length; }

    // out-performs a doubly linked-list in terms of:
    // 1. amortized time complexity.
    // 2. memory overhead
    // 3. get/set operations are O(1)
    // 4. can do binary search if sorted.
    // But is not better if need to insert/delete from MIDDLE of queue.

    // for Iterable<T> interface:
    public Iterator<T> iterator() { return new CQiterator<T>(this); }

    // once we have an iterable object, we can create an even more
    // powerful abstraction called a STREAM.
    public Stream<T> stream(boolean parallel) {
        return StreamSupport.stream(this.spliterator(),parallel);
    }

    // Consuming stream: pops from queue as it streams (not parallelizable):
    public Stream<T> toStream() {
        return Stream.generate( ()->pop() ).limit(size);
    }

    //////////// note this is "main0", not main
    public static void main0(String[] args) {
        CQ<Integer> q = new CQ<Integer>(1);
        for(var x:new Integer[]{2,4,6,8,10}) q.add(x);
        for(var x:new Integer[]{1,3,5,7,9}) q.push(x);
        /*
        while (q.size()>1) {
            System.out.println(q.pop());
            System.out.println(q.dequeue());            
        }
        */        
        // what's wrong with this loop????
        /*
        for(var x:q) {
           q.push(x);
        }

        for(var x:q) {
            System.out.println(x);
        }
        */
        /*
        var A = new java.util.Vector<Integer>();
        A.add(2); A.add(3);
        for(var x:A) A.add(x);
        */

        //q.set(6,q.get(6)*10+1);
	
        q.stream(true)// only set to true for very large queues (>1000000)
            .map(x -> x*x)
            .filter(x -> x%2 == 1)
            .forEach(System.out::println);
        // and don't change anything (no side effects, ideally not even print)
        
        var allpositive = 
        q.stream(false)
            .allMatch(x -> x>0);
        System.out.println("all positive: "+allpositive);
        q.stream(false)
            .filter(x -> x%3==0)
            .findAny()  // returns Optional<Integer>
            .ifPresent(x -> System.out.println("found "+x));

    }//main0
}//CQ


// iterator class for a CQ (can be internal class)
class CQiterator<T> implements Iterator<T> {
    CQ<T> q; // pointer to q to interate.
    int i = 0; // current index
    int size;
    public CQiterator(CQ<T> q) { this.q=q; size=q.size();}

    public boolean hasNext() {
        //return size==q.size() && i<q.size();
        if (size!=q.size())
            throw new java.util.ConcurrentModificationException();
	    //consistent with behavior of other Java List/Queue structures.
        return i<q.size();
    }
    public T next() { return q.get(i++);    }
}
////// Warning: this iterator does not check against modifying the queue
////// via set.  requires more OVERHEAD.
