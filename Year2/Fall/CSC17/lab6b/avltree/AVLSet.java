package avltree;

import java.util.Comparator;
import java.util.Iterator;
import java.util.stream.Stream;

public class AVLSet<T extends Comparable<? super T>> extends BstSet<T>
implements Iterable<T> {

    // Constructor for AVLSet with default comparator
    public AVLSet() {
        super();
        Empty = new AVLNil();
        root = Empty;
    }

    // Constructor for AVLSet with custom comparator
    public AVLSet(Comparator<T> comparator) { 
        super(comparator); 
        Empty = new AVLNil();  
        root = Empty;
    }  

    // Removes an item from the tree, returns true if removed
    public boolean remove(T element) {
        if (element == null) return false;
        int previousSize = size;
        root = root.remove(element);
        return size < previousSize;
    }

    // Returns a stream of the elements in the tree
    public Stream<T> stream() {
        return root.stream();
    }

    // Returns an iterator for the elements in the tree
    public Iterator<T> iterator() {
        return root.stream().iterator();
    }

    // Searches for an item in the tree
    public boolean search(T element) {
        if (element == null) return false;
        Tree<T> currentNode = root;
        while (!currentNode.is_empty()) {
            var activeNode = (AVLNode)currentNode;
            int comparison = cmp.compare(element, activeNode.item);
            if (comparison == 0) return true;
            else if (comparison < 0) currentNode = activeNode.left;
            else currentNode = activeNode.right;
        }
        return false;
    }

    // Represents an empty node in the AVL tree
    class AVLNil extends Nil {
        @Override    
        public Tree<T> insert(T value) {
            size++;
            return new AVLNode(value, Empty, Empty);
        }

        @Override
        public String toString() {
            return "";
        }
    }

    // Represents a node in the AVL tree
    class AVLNode extends Node {
        int nodeHeight;

        @Override
        public int depth() {
            return nodeHeight;
        }

        // Sets the height of the current node and returns balance factor
        int updateHeight() {
            int leftDepth = left.depth();
            int rightDepth = right.depth();
            nodeHeight = 1 + Math.max(leftDepth, rightDepth);
            return rightDepth - leftDepth;
        }

        // Constructor for AVLNode
        public AVLNode(T value, Tree<T> leftChild, Tree<T> rightChild) { 
            super(value, leftChild, rightChild); 
            updateHeight();
        }

        @Override
        public String toString() {
            return item + "";
        }

        @Override 
        public Tree<T> clone() {
            return new AVLNode(item, left.clone(), right.clone());
        }

        // Creates a stream of the elements in the tree
        public Stream<T> stream() {
            return Stream.generate(() -> left.stream()).limit(1)
                   .map(leftStream -> Stream.concat(leftStream, Stream.of(this.item)))
                   .flatMap(mergedStream -> Stream.concat(mergedStream, right.stream()));
        }

        // Removes an item from the tree
        public Tree<T> remove(T value) {
            int comparison = cmp.compare(value, item);
            if (comparison < 0) left = left.remove(value);
            else if (comparison > 0) right = right.remove(value);
            else {
                size--;
                if (left.is_empty()) return right;
                else {
                    left = ((AVLNode)left).removeMax(this);
                }
            }
            rebalance();
            return this;
        }

        // Deletes the maximum value node and adjusts the tree
        Tree<T> removeMax(Node parentNode) {
            if (right.is_empty()) {
                parentNode.item = this.item;
                return left;
            } else {
                right = ((AVLNode)right).removeMax(parentNode);
                rebalance();
                return this;
            }
        }

        // Adjusts the balance of the tree
        @Override
        void adjust() {
            rebalance();
        }

        void rebalance() {
            int balanceFactor = updateHeight();

            if (balanceFactor < -1) {
                var leftSubtree = (AVLNode) left;
                if (leftSubtree.left.depth() >= leftSubtree.right.depth()) {
                    rotateLeft();
                } else {
                    leftSubtree.rotateRight();
                    rotateLeft();
                }
            } else if (balanceFactor > 1) {
                var rightSubtree = (AVLNode) right;
                if (rightSubtree.right.depth() >= rightSubtree.left.depth()) {
                    rotateRight();
                } else {
                    rightSubtree.rotateLeft();
                    rotateRight();
                }
            }
        }

        // Performs a left-left rotation
        void rotateLeft() {
            var leftSubtree = (AVLNode) this.left;
            T oldItem = this.item;
            this.item = leftSubtree.item;
            leftSubtree.item = oldItem;
            this.left = leftSubtree.left;
            leftSubtree.left = leftSubtree.right;
            leftSubtree.right = this.right;
            this.right = leftSubtree;
            leftSubtree.updateHeight();
            this.updateHeight();
        }

        // Performs a right-right rotation
        void rotateRight() {
            var rightSubtree = (AVLNode) this.right;
            T oldItem = this.item;
            this.item = rightSubtree.item;
            rightSubtree.item = oldItem;
            this.right = rightSubtree.right;
            rightSubtree.right = rightSubtree.left;
            rightSubtree.left = this.left;
            this.left = rightSubtree;
            rightSubtree.updateHeight();
            this.updateHeight();
        }
    }
}

