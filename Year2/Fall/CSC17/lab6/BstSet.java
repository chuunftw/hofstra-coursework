package avltree;
//import java.util.Iterator;
import java.util.Comparator;
//import java.util.Stack;
import java.util.Optional;
import java.util.function.*;

import avltree.BstSet.Nil;
import avltree.BstSet.Node;

public class BstSet<T extends Comparable<? super T>> {

    /*final*/ Tree<T> Empty = new Nil();    // only instance ever needed

    Tree<T> root = Empty;
    int size = 0;
    Comparator<T> cmp = (x,y) -> x.compareTo(y);

    public BstSet() {}
    public BstSet(Comparator<T> cmp) {
	if (cmp!=null) this.cmp = cmp;
    }
    
    ///// wrapper class methods:

    public int size() {return size;}
    public int depth() {return root.depth();}
    public boolean contains(T x) { 
	if (x==null) return false;
	else return root.contains(x); 
    }
    public boolean insert(T x) { 
        if (x==null) return false;
	int previous_size = size;
        root = root.insert(x);
        return size > previous_size;
    } // returns true if something was inserted, false otherwise
    public Optional<T> min() { return root.min(); }
    public Optional<T> max() { return root.max(); }
    public BstSet<T> clone() {
        var bst = new BstSet<T>(cmp);
        bst.root = this.root.clone();
        bst.size = size;
        return bst;
    }
    public Tree<T> successor(T x, Tree<T> ancestor){
        if( x == null || root.is_empty()) return Empty;
        return root.successor(x, Empty);
    }
    public Tree<T> precessor(T x, Tree<T> ancestor){
        if( x == null || root.is_empty()) return Empty;
        return root.predecessor(x, Empty);
    }
    public boolean is_bst(){
        return root.is_bst(Optional.empty(), Optional.empty());
    }
	if (cf != null) root.map_inorder(cf);
    }
    public void ifPresent(Consumer<? super T> cf) {
        root.ifPresent(cf);
    }
    public <U> U match(Function<? super T,? extends U> fn, 
                       Supplier<? extends U> fe)  { 
	return root.match(fn,fe);
    }



  //////////////////////////////// inner classes //////////////////

  class Nil implements Tree<T>
  {
    public boolean is_empty() { return true; }
    public int depth() { return 0; }
    public boolean contains(T x) { return false; }
    public Tree<T> insert(T x) {
      size++;  // advantage of having a wrapper class
      return new Node(x,Empty,Empty);
    }//insert
    public Optional<T> min() { return Optional.empty(); }
    public Optional<T> max() { return Optional.empty(); }
    public Tree<T> clone() { return Empty; }
    public Tree<T> successor(T x, Tree<T> ancestor) { return Empty; }
    public Tree<T> predecessor(T x, Tree<T> ancestor) { return Empty; }
    public boolean is_bst(Optional<T> min, Optional<T> max){ return true; }
    public void map_inorder(Consumer<? super T> cf) {}
    public void ifPresent(Consumer<? super T> cf) {}
    public <U> U match(Function<? super T,? extends U> fn, 
                       Supplier<? extends U> fe)  { 
      return fe.get(); 
    }
  }//Nil

  class Node implements Tree<T>
  {
    T item;
    Tree<T> left;
    Tree<T> right;
    public Node(T i, Tree<T> lf, Tree<T> rt) {
	item = i;  left=lf;  right = rt;
    }
    public boolean is_empty() { return false; }
    public int depth() { return 1 + Math.max(left.depth(),right.depth()); }
    public boolean contains(T x) {
      int c = cmp.compare(x,item);
      return (c==0) || (c<0 && left.contains(x)) || (c>0 && right.contains(x));
      /* for earthlings, the above line is equivalent to:
         if (c==0) return true;
         else if (c<0) return left.contains(x);
         else return right.contains(x);
      */
    }//contains

    @Override
    public Tree<T> insert(T x) {
	int c = cmp.compare(x,item);
        if (c<0) left = left.insert(x);
        else if (c>0) right = right.insert(x);
        // else c==0 and x is a duplicate, ignore
        adjust(); // to be completed later ...
        return this;
    }//insert

    @Override
    public Optional<T> min() { 
	if (left.is_empty()) return Optional.of(this.item);
	else return left.min();
    }

    @Override
    public Optional<T> max(){
        if(right.is_empty()) return Optional.of(this.item);
        else return right.max();
    }

    public void map_inorder(Consumer<? super T> cf) {
	left.map_inorder(cf);
	cf.accept(this.item);
        right.map_inorder(cf);
    }
    
    @Override
    public Tree<T> clone(){
        return new Node(item, left.clone(), right.clone());
    }
    @Override
    public Tree<T> successor(T x, Tree<T> ancestor){
        if(cmp.compare(x, this.item) < 0){ // x is < item so successor could be in the left subtree
            Tree<T> lSuc = this.left.successor(x, this);// searches left subtree
            if(lSuc.is_empty()){
                return this;
            }
            else{
                return lSuc;
            }
        }
        else if(cmp.compare(x, this.item)>0){ // x is > item 
            return this.right.successor(x, ancestor); // serach right subtree
        }
        else{ // x = item
            if(!this.right.is_empty()){
                return this.right; // successor is minimum in the right subtree
            }
            return ancestor; // if theres no successor return an ancestor instead
        }
    }

    @Override
    public Tree<T> predecessor(T x, Tree<T> ancestor){
        if(cmp.compare(x,this.item) > 0){
            Tree<T> rpred = this.right.predecessor(x, this);
            if(rpred.is_empty()){
                return this;
            }
            else{
                return rpred;
            }
        }
            else if(cmp.compare(x, this.item) < 0){
                return this.left.predecessor(x, ancestor);
            }
            else{
                if(!this.left.is_empty()){
                    return this.right;
                }
                return ancestor;
            }
    }

    @Override
    public boolean is_bst(Optional<T> min, Optional<T> max){
        T item = this.item; // gets the current nodes item

        //item is less than or equal to min
        if (min.isPresent() && cmp.compare(item, min.get()) <= 0) return false;

        //item is greater than or equal to max
        if (max.isPresent() && cmp.compare(item, max.get()) >= 0) return false;

        //checks left subtree, item becomes the new max bound for the left child
        boolean isLeftBst = this.left.is_bst(min, Optional.of(item));
        //checks right subtree, item becomes new min bound for the right child
        boolean isRightBst = this.right.is_bst(Optional.of(item), max);

        return isLeftBst && isRightBst; // both have to be valid for it to be bst
    }
    

    /// these functions are not recursive: only works on item ...
    public void ifPresent(Consumer<? super T> cf) { 
         cf.accept(this.item);
    }
    public <U> U match(Function<? super T,? extends U> fn, 
                       Supplier<? extends U> fe)  { 
	return fn.apply(this.item);
    }

    ///// for comparison, non-recursive version of insert
    public void add(T x) {
	Node current = this;
	boolean stop = false;
	while (!stop) {
	    int c = x.compareTo(current.item);
	    if (c<0) {
		if (current.left.is_empty()) {
		    current.left = new Node(x,Empty,Empty);
		    stop = true;
		}
		else current = (Node)current.left;
	    }
	    else if (c>0) {
		if (current.right.is_empty()) {
		    current.right = new Node(x,Empty,Empty);
		    stop = true;
		}
		else current = (Node)current.right;
	    }
	    else stop = true;  // duplicate found
	}//while
    }//add

    void adjust() {} // for now

    void LL(){
        Node y = (Node) this.left;
        this.left = y.right;       // Update the left child of the current node to y's right child
        y.right = this;            // Make the current node the right child of y
        T tempItem = this.item;
        this.item = y.item;
        y.item = tempItem;

        
    } 
    // implement these as part of the lab (see lab description)
    void RR(){
        Node y = (Node) this.right;
        this.right = y.left;
         y.left = this;
        T tempItem = this.item;
        this.item = y.item;
        y.item = tempItem; // changes to left child of current node
    }
  }//Node inner class

}//BstSet wrapper class