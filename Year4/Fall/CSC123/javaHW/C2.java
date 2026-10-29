// public class A2 {
//     protected void f()  { ... }
//     protected void g()  { ... }
//     protected void h1() { ... }
// }
// public class B2 {
//     protected void f()  { ... }
//     protected void g()  { ... }
//     protected void h2() { ... }

import javaasn.A2;
import javaasn.B2;

// Part 2: Reuse A2's f() and h1(), and B2's g() and h2().
public class C2 extends A2 {
    class B2helper extends B2{
        public void gsuper(){
            super.g();
        }
        public void h2super(){
            super.h2();
        }
    }
    
    B2helper b2helper = new B2helper();
    @Override
    public void g(){
        b2helper.gsuper();
    }

    public void h2(){
        b2helper.h2super();
    }

    public static void main(String[] args) {
        C2 C2_object = new C2();
        C2_object.f(); 
        C2_object.g(); 
        C2_object.h1(); 
        C2_object.h2(); 
    }
}
