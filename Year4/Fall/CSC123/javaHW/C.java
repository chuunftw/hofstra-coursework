// CSC 123/252 Object Oriented Programming Assignment
// Emulating Multiple Inheritance
//
// ASSIGNMENT TEXT -- Part I (provided by your professor)
// Java permits only single inheritance. While you may implement multiple
// interfaces, you can only extend one class.
// We just need to store an instance of the "superclass" inside the subclass
// and rebuild the interface.
//
// The package contains the following setup:
// public interface Ia { void f(); void g(); void h1(); }
// public interface Ib { void f(); void g(); void h2(); }
// public class A implements Ia { ... }
// class B implements Ib { ... }
//
// You are to show how to construct a class
//     class C extends A implements Ia, Ib
// That inherits from A but implements both interfaces by "faking" the
// additional inheritance from B. This class should inherit both h1 from
// A and h2 from B. FURTHERMORE, C MUST inherit f() from class A and g()
// from class B, so some overriding would be needed.
//
// Just outside the javaasn directory, create a C.java program with the
// imports and class declaration below.
//
// Your implementation must work with any implementation of class A and B.
// Decompiling the class files is strictly not allowed.
//
// Anyone who writes System.out.println statements in their code will lose
// 10000 points.
//
// This doesn't mean you can't define f, g and h1/h2 in your subclasses
// It means that you cannot copy the "System.out.println" code, because it
// really represents arbitrarily complex code. Your solution must work in
// general, regardless of how these functions are implemented.
//
// Write a main that calls all 4 functions, f, g, h1, and h2 on your C class.
// You can put the main inside the public C class.
// END OF ASSIGNMENT TEXT

import javaasn.A;
import javaasn.B;
import javaasn.Ia;
import javaasn.Ib;
import javaasn.A2;
import javaasn.B2;

// TODO: Part 1: Reuse A's f() and h1(), and B's g() and h2().
// Complete the interface requirements using the supplied methods.
// This skeleton will not compile until the missing methods are implemented.
public class C extends A implements Ia, Ib {
// C is a subclass of A that references all functions of Interfaces Ia, Ib
    // Store an object that provides the behavior needed from B.
    // Override the inherited method whose behavior must come from B.
    private final B b = new B(); //composition 
    // Provide the additional method required by Ib.
    @Override 
    public void g(){ 
        b.g();
    }
    @Override 
    public void h2(){ 
        b.h2();
    }
    public static void main(String[] args) {
        // Create a C object.
        C C_object = new C(); 
        // Call f(), g(), h1(), and h2() on it.
        C_object.f(); 
        C_object.h1(); 
        C_object.g();
        C_object.h2();
    }
}
