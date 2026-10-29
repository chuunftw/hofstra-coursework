// Learning notes and practice examples for Part2.
// Run from this folder: java Part2Learning.java
// These examples are separate from your assignment solution.
// Read Part1Learning.java first, then these additional Part 2 topics.

public class Part2Learning {
    public static void main(String[] args) {
        AccessModifiers.main(args);
        SuperKeyword.main(args);
    }

    // Topic 7: Access modifiers
    // public: accessible wherever the containing type is accessible.
    // private: accessible within the enclosing top-level class in this example.
    // No modifier (package-private): accessible within the same package.
    // protected: accessible in the same package, plus special subclass access
    // from other packages.
    // Run: java Part2Learning.java
    
    static class AccessModifiers {
        static class Device {
            protected void activate() {
                System.out.println("Device activated");
            }
        }
    
        static class Phone extends Device {
            public void turnOn() {
                activate(); // A subclass can call its inherited protected method.
            }
        }
    
        public static void main(String[] args) {
            Phone phone = new Phone();
            phone.turnOn(); // Device activated
        }
    
        // Important: both example classes are in the SAME package here.
        // This runnable example alone does not demonstrate a cross-package error.
        // Suppose Device were public in another package. In a Phone method:
        //     activate();                 // Allowed: inherited method
        //     new Device().activate();    // Not allowed across packages
        // Extending Device does not grant access through every Device object.
        //
        // Assignment connection: your new files are outside package javaasn.
        // A helper subclass can provide a public method that calls an inherited
        // protected method. We will build that idea step by step for Part 2.
    }

    // Topic 8: super
    // super.method() calls the superclass implementation from a subclass.
    // This is useful when an override still needs the inherited behavior.
    // Run: java Part2Learning.java
    
    static class SuperKeyword {
        static class Animal {
            public void speak() {
                System.out.println("Animal sound");
            }
        }
    
        static class Dog extends Animal {
            @Override
            public void speak() {
                super.speak(); // Calls Animal's implementation
                System.out.println("Woof");
            }
        }
    
        public static void main(String[] args) {
            Dog dog = new Dog();
            dog.speak(); // Prints Animal sound, then Woof
        }
    
        // Calling speak() instead of super.speak() inside Dog.speak()
        // would call the same override repeatedly until a stack overflow.
        // Assignment connection: super lets an override reuse supplied behavior.
    }
}
