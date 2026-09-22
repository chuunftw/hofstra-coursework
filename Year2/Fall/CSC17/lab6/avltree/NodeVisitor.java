package avltree;

import java.util.function.BiConsumer;
import java.util.function.Consumer;

// A helper class for visiting nodes in preorder
public class NodeVisitor<T> implements Consumer<T> {
    Tree<T> parentTree;
    final BiConsumer<Tree<T>, T> nodeVisitor;

    public NodeVisitor(Tree<T> parentNode, BiConsumer<Tree<T>, T> visitor) {
        parentTree = parentNode;
        this.nodeVisitor = visitor;
    }

    public NodeVisitor<T> withParent(Tree<T> newParent) {
        parentTree = newParent;
        return this;
    }

    public void accept(T element) {
        nodeVisitor.accept(parentTree, element);
    }
}
