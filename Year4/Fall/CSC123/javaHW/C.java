// The package contains the following setup:
// public interface Ia { void f(); void g(); void h1(); }
// public interface Ib { void f(); void g(); void h2(); }
// public class A implements Ia { ... }
// class B implements Ib { ... }

import javaasn.A;
import javaasn.B;
import javaasn.Ia;
import javaasn.Ib;
import javaasn.A2;
import javaasn.B2;

public class C extends A implements Ia, Ib {
    private final B b = new B(); //composition 

    @Override 
    public void g(){ 
        b.g();
    }

    @Override 
    public void h2(){ 
        b.h2();
    }
    
    public static void main(String[] args) {
        C C_object = new C(); 
        C_object.f(); 
        C_object.h1(); 
        C_object.g();
        C_object.h2();
    }
}
