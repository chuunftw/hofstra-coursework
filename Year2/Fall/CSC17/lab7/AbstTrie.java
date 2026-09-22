import java.util.HashMap;
import java.util.Optional;
import java.util.function.Function;

record SVPair<V>(String key, V val) {
    @Override
    public String toString() {
        return key + " : " + val;
    }
}

public abstract class AbstTrie<KT, KCT, VT> {
    protected abstract int key_length(KT key);
    protected abstract KCT key_char(KT key, int idx);

    public class Node {
        Optional<VT> item = Optional.empty();
        HashMap<KCT, Node> children = new HashMap<>();

        Node() {}
        Node(VT x) {
            item = Optional.ofNullable(x);
        }
    }

    int size = 0;
    int nodes = 1;
    Node root = new Node();

    public int size() {
        return size;
    }

    public double load_factor() {
        return size * 1.0 / nodes;
    }

    public Optional<VT> and_modify(KT key, Function<Optional<VT>, ? extends VT> modifier) {
        if (key == null || modifier == null) {
            return Optional.empty();
        }

        Node current = root;
        int k = 0;
        while (k < key_length(key)) {
            KCT keyComponent = key_char(key, k);
            current = current.children.computeIfAbsent(keyComponent, p -> {
                nodes++;
                return new Node();
            });
            k++;
        }

        Optional<VT> previousValue = current.item;
        current.item = Optional.ofNullable(modifier.apply(current.item));
        if (previousValue.isEmpty() && current.item.isPresent()) {
            size++;
        } else if (previousValue.isPresent() && current.item.isEmpty()) {
            size--;
        }
        return previousValue;
    }

    public Optional<VT> set(KT key, VT val) {
        return and_modify(key, x -> val);
    }

    public Optional<VT> search(KT key, boolean delete) {
        if (key == null) {
            return Optional.empty();
        }

        Optional<VT> result = Optional.empty();
        Node current = root;
        int k = 0;
        while (k < key_length(key)) {
            KCT keyComponent = key_char(key, k);
            current = current.children.get(keyComponent);
            if (current == null) {
                return result;
            }
            k++;
        }

        result = current.item;
        if (delete && result.isPresent()) {
            current.item = Optional.empty();
            size--;
        }

        return result;
    }

    public Optional<VT> get(KT key) {
        return search(key, false);
    }

    public Optional<VT> remove(KT key) {
        return search(key, true);
    }



	public static void main(String[] args) {
		var GPA = new StringTrie<Double>();
		String[] Roster={"Alex","Tyrone","Alexi","Alexander","Alexandra","Al","Tyler"};
		for(String n:Roster)
			GPA.set(n,((int)(Math.random()*401))/100.0);
	
		GPA.remove("Alexi");
		GPA.set("Alexander",3.5);
		System.out.println("size: "+GPA.size());		
		for(String n:Roster)
			System.out.println(n+" has a GPA of "+GPA.get(n));
		GPA.set("Alexi",1.0);
		
			GPA.stream("Alex",2).forEach(System.out::println);
	
		GPA.remove("Alexander");
		GPA.remove("Alexandra");
		System.out.println("size: "+GPA.size());	
		System.out.println("load factor: "+GPA.load_factor());
		int cleaned = GPA.cleanup();
		System.out.println("cleaned: "+cleaned);
		System.out.println("load factor: "+GPA.load_factor());	
		
		}
}
