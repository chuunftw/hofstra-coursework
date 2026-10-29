// Learning notes and practice examples for Part1.
// Run from this folder: java Part1Learning.java
// These examples are separate from your assignment solution.
// Read the numbered topics from top to bottom.
// Printing is for these demonstrations; reuse supplied methods in homework.

public class Part1Learning {
    public static void main(String[] args) {
        ClassesAndObjects.main(args);
        Inheritance.main(args);
        Overriding.main(args);
        Interfaces.main(args);
        CompositionAndDelegation.main(args);
        PackagesAndImports.main(args);
    }

    // Topic 1: Classes and objects
    // A class defines the methods (actions) its objects can perform.
    // An object is an instance of a class, created using new.
    // These are practice examples, separate from your homework solution.
    // Printing is fine here; the assignment requires calling the supplied methods.
    // Run from this folder with: java Part1Learning.java
    
    static class ClassesAndObjects {
        // Keeping example classes inside this class avoids name conflicts
        // with the Animal and Dog examples in the other lesson files.
        static class Animal {
            public void eat() {
                System.out.println("Eating");
            }
        }
    
        public static void main(String[] args) {
            // Animal is the type; pet is the variable referring to the object.
            Animal pet = new Animal();
    
            // The dot lets us call a method on that object.
            pet.eat(); // Output: Eating
        }
    }

    // Topic 2: Inheritance and extends
    // Inheritance is the concept; extends is the Java keyword that creates it.
    // A superclass passes inheritable methods to its subclass.
    // Run from this folder with: java Part1Learning.java
    
    static class Inheritance {
        static class Animal {
            public void eat() {
                System.out.println("Eating");
            }
        }
    
        // Animal is the superclass. Dog is the subclass.
        // A Dog IS AN Animal.
        static class Dog extends Animal {
            public void bark() {
                System.out.println("Woof");
            }
        }
    
        public static void main(String[] args) {
            Dog dog = new Dog();
            dog.eat();  // Output: Eating -- inherited from Animal
            dog.bark(); // Output: Woof -- defined in Dog
    
            Animal animal = new Animal();
            animal.eat(); // Output: Eating
    
            // Uncommenting this(below line) would cause a compile error:
            // animal.bark();
            // Animal does not have a bark() method. Inheritance goes one way.
        }
    
        // Java allows a class to extend only ONE class.
        // class Dog extends Animal, AnotherClass {} // Not allowed
        // In your assignment, C extends A means C inherits methods from A.
    }

    // Topic 3: Overriding an inherited method
    // A subclass can provide its own version of an inherited instance method.
    // The overriding method uses the same name and parameter types.
    // Run from this folder with: java Part1Learning.java
    
    static class Overriding {
        static class Animal {
            public void speak() {
                System.out.println("Animal sound");
            }
        }
    
        static class Dog extends Animal {
            // @Override asks the compiler to check that this method
            // really overrides a method inherited from the superclass.
            @Override
            public void speak() {
                System.out.println("Woof");
            }
        }
    
        public static void main(String[] args) {
            Animal animal = new Animal();
            animal.speak(); // Output: Animal sound
    
            Dog dog = new Dog();
            dog.speak(); // Output: Woof -- Dog's version runs
    
            // If you removed Dog's entire speak() method, Dog would inherit
            // Animal's version, so dog.speak() would print Animal sound.
            // Removing only @Override would NOT remove the override.
        }
    
        // Assignment connection: C inherits g() from A, but needs different
        // behavior for g(). Overriding lets C supply that different behavior.
    }

    // Topic 4: Interfaces and implements
    // An interface states which methods a class must provide.
    // It does not supply an implementation for the methods shown here.
    // extends inherits from a class; implements promises to fulfill an interface.
    // A class can implement multiple interfaces, but extend only one class.
    // Run: java Part1Learning.java
    
    static class Interfaces { //class named Interfaces of Interfaces 
        interface Speaker {
            void speak(); // Implicitly public and abstract
        }
        // contains two interfaces Speaker and Walker
        interface Walker {
            void walk();
        }
    
        static class Dog implements Speaker, Walker { //once called the interfaces, functions can now reference other functions 
                                                    // from referenced interfaces
            @Override
            public void speak() { //speaker is REFERENCED allowing speak to be used
                System.out.println("Woof");
            }
    
            @Override
            public void walk() {
                System.out.println("Walking");
            }
        }
    
        public static void main(String[] args) {
            Dog dog = new Dog();
            dog.speak(); // Woof
            dog.walk();  // Walking
    
            // An interface variable can refer to an object implementing it.
            Speaker speaker = dog;
            speaker.speak(); // Woof
            // speaker.walk(); // Error: Speaker does not declare walk().
        }
    
        // Assignment connection: C must fulfill both Ia and Ib.
        // An inherited public method can fulfill an interface requirement too.
    }

    // Topic 5: Composition and delegation
    // Composition: an object HAS another object stored in a field.
    // Delegation: a method asks that stored object to do the work.
    // This is different from inheritance, which describes an IS-A relationship.
    // Run: java Part1Learning.java
    
    static class CompositionAndDelegation {
        static class Engine {
            public void start() {
                System.out.println("Engine started");
            }
        }
    
        static class Car {
            // A Car HAS an Engine. It does not extend Engine.
            private final Engine engine = new Engine();
    
            public void start() {
                // Delegate the work instead of copying Engine's implementation.
                engine.start();
            }
        }
    
        public static void main(String[] args) {
            Car car = new Car();
            car.start(); // Engine started
        }
    
        // Assignment connection: storing another object lets you reuse its
        // behavior even when you cannot extend its class.
        // If Engine.start() changes, Car still calls the updated implementation.
    }

    // Topic 6: Packages and imports
    // A package groups types under a name, such as java.util or javaasn.
    // An import lets you use a type's short name in this source file.
    // It does not copy code or create inheritance.
    // Run: java Part1Learning.java
    
    
    
    static class PackagesAndImports {
        public static void main(String[] args) {
            // Thanks to the import, we can write java.util.ArrayList instead of
            // java.util.java.util.ArrayList. new still creates the object.
            java.util.ArrayList<String> topics = new java.util.ArrayList<>();
            topics.add("Inheritance");
            System.out.println(topics.get(0)); // Inheritance
        }
    
        // Assignment connection:
        // import javaasn.A; makes the name A available in your source file.
        // Your C.java sits alongside the javaasn folder, not inside that package.
        // Leave package javaasn; OUT of your C.java and C2.java files.
        //
        // From the folder containing C.java and the javaasn folder:
        // javac C.java  -- compiles your source into C.class
        // java C       -- runs C's public static void main(String[] args)
        // These commands are for later, once you have written C.java.
    }
}
