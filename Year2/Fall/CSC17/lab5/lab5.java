/*      CSC 17 Lab: Better Programming with Data Structures.


You're expected to use the right data structure to rewrite the following 
programs so that they're as efficient as possible in terms of running time.
Select structures from the java.util package and read their documentation.

*/
import java.util.Optional;
import java.util.Arrays;
import java.util.stream.Stream;
import java.util.HashMap;
import java.lang.Math;
import java.util.PriorityQueue;
import java.util.HashSet;



record pair(int x, int y) {
    @Override
    public String toString() { return "("+x+","+y+")"; }
}


public class lab5 {

    /* Problem 0:
       A permutation of length n can be represented by an array of length
       n that contains the number 0 ... n-1.  For example, {1,0,3,2} is
       a permutation of length 4.  {1,4,2,2} is not a permutation of length
       4. Write a function to determine if an array represents a permutation
       of its length.  The naive solution is O(n*n).  A better solution might
       use a hashset, but the best solution would not require any special
       data structure.  Find a solution that's worst-case O(n).
    */
    public static boolean is_permutation(int[] A) {
        HashSet<Integer> check = new HashSet<>(A.length);
        for(int i =0;i<A.length;i++)
        {
            int num = A[i];
            if (num<0 || num>=A.length){
                return false;
            }
            if(check.contains(num)){
                return false;
            }
            check.add(num);
            }
            return true;
    }


    //is_permutation: naive solution


    /* Problem 1: 
       Given an array of Integers and an Integer M, determine if there
       are two distinct integers in the array that adds up to M.
       for example, if the array is {3,1,8,4,6} and M is 5, then the
       answer is yes, because 1+4= 5.  But if M = 2 the answer is no.

       The following solution works but is not efficient: it's O(n*n).
       Your task is to find a solution that takes O(n) time, at least 
       on theoretical average.  You may use up to O(n) extra memory
       (n refers to the length of the array).  Your function must
       take the same type of arguments and return same type.
    */
    public static Optional<pair> findpair(int[] A, int M) {
        int s = A.length;
        HashMap<Integer, Integer> map = new HashMap<>(s);
        for (int i= 0;i<s; i++)
         {
            map.put(A[i], i);
        }
        for (int j = 0; j < s; j++) 
        {
            int diff = M - A[j];
            if (map.containsKey(diff) && map.get(diff) != j)
            {
                return Optional.of(new pair(j, map.get(diff)));        
            }
        }
    
        return Optional.empty();
    }
    
    
    /* Problem 2:
       Given an array of Comparable values, find the Kth smallest value.
       for Example, for an array of Integers {5,4,9,7,1,2,8}, the 3rd 
       smallest value is 4.

       The following solution uses the built-in Arrays::sort function,
       which implements a version of mergesort and takes worst-case 
       O(n*log n) time.  Your task is to find a solution that runs in
       O(n*log K) time.  Since K<n, it will be a better solution.
    */
    public static <T extends Comparable<? super T>>  Optional<T> Kthsmallest(T[] A, int K) {

        //T[] ksizeheap = Arrays.copyOf(A,K);
        PriorityQueue<T> maxHeap = new PriorityQueue<>((a,b)->b.compareTo(a));
        if(K<1 || K>A.length)
        {
            return Optional.empty();
        }
        
        for (int i = 0; i < K; i++) {
            maxHeap.add(A[i]);
        }
        for(int i =K;i<A.length;i++)
        {
            if(A[i].compareTo(maxHeap.peek())<0){
                maxHeap.poll();
                maxHeap.add(A[i]);
            }
        }

        return Optional.of(maxHeap.peek());


    }//Kthsmallest







    /* Problem 3 (harder):
       Find and print the median number in a running stream of numbers.
       If the number of numbers is even, the median is average of the
       two middle values. The naive solution inserts the numbers into a
       sorted queue, but is horribly inefficient ...
       Hint: the better solution is to use two heaps, a maxheap and a
       minheap.  Study the docs on java.util.PriorityQueue to learn
       how to create a maxheap as well as a minheap.
    */
    public static void median(Stream<Double> numbers) {
        PriorityQueue<Double> minHeap = new PriorityQueue<>();
        PriorityQueue<Double> maxHeap = new PriorityQueue<>((a,b)-> b.compareTo(a));
        
        //List<Double> listofNums = numbers.collect(Collectors.toList());
        

        numbers.forEach(n->
        {
            if(!maxHeap.isEmpty() && n <= maxHeap.peek()){
                maxHeap.add(n);

            }
            else{
                minHeap.add(n);
            }
            
            if(maxHeap.size()>minHeap.size()+1)
            {
                minHeap.add(maxHeap.poll());
            }
            else if(minHeap.size()>maxHeap.size()){
                
                maxHeap.add(minHeap.poll());
            }
        });

        Double median = 0.0;

        if(maxHeap.size() == minHeap.size())
        {
            median = (maxHeap.peek() + minHeap.peek())/ 2.0;
        }
        else{
            median = maxHeap.peek();
        }
        System.out.println(median);
    }

    public static void main(String[] args) {
        median(Stream.generate(() -> Math.random()*1000).limit(100));
        median(Arrays.stream(new Double[]{2.0,5.0,8.0,6.0,7.0,9.0,1.0})); //should return 6.0
        
        System.out.println(is_permutation(new int[]{1,0,3,2}));
        System.out.println(is_permutation(new int[]{1,2,4,2}));
        System.out.println(findpair(new int[]{3,1,8,4,6}, 5));
        System.out.println(findpair(new int[]{3,1,8,4,6}, 15));
        System.out.println(Kthsmallest(new Integer[]{5,4,9,7,1,2,8}, 3)); // should return 4
            // ... construct other test cases ...
        
        } //main
}//lab5

