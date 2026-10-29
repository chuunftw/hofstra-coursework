// CSC 123/252 Object Oriented Programming Assignment
// Emulating Multiple Inheritance
//
// ASSIGNMENT TEXT -- Part 2 (provided by your professor)
// This time there are no interfaces Ia, Ib to give you a clue. Instead you
// just know that there are class A2 and B2:
//
// public class A2 {
//     protected void f()  { ... }
//     protected void g()  { ... }
//     protected void h1() { ... }
// }
// public class B2 {
//     protected void f()  { ... }
//     protected void g()  { ... }
//     protected void h2() { ... }
// }
//
// Protected items are only visible to subclasses outside the package.
//
// Once again, you are to assume that the code in A2, B2 are generic and you may
// not just write println statements.
//
// Write a public class C2 that inherits all the functionality of A2 and
// B2, with the same stipulation that it should take f() from A2 and g()
// from B2.
//
// Hint: you may define other interfaces, classes to help you, but YOU
// MAY NOT CHANGE A2, B2.
//
// Hint: to call the superclass version of a function, call super.function(..)
//
// Write a main that calls all methods on your subclass.
// END OF ASSIGNMENT TEXT

import javaasn.A2;
import javaasn.B2;

// TUTOR GUIDANCE -- the comments below are suggested steps, not assignment quotes.
// Part 2: Reuse A2's f() and h1(), and B2's g() and h2().
// The supplied methods are protected. Do not modify A2 or B2.
public class C2 extends A2 {
    // Define a helper subclass to access the needed B2 behavior.

    // Store an instance of your helper.

    // Override the inherited method whose behavior must come from B2.

    // Provide access to the additional behavior from B2.

    public static void main(String[] args) {
        // Create a C2 object.
        // Call f(), g(), h1(), and h2() on it.
    }
}
