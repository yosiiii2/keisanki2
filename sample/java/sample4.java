import java.io.*;

class ClassSample {
    public static void main(String[] args) {
	Switch s1 = new Switch();
	Switch s2 = new Switch();

	s1.flip();
	System.out.println(s1.check());
	System.out.println(s2.check());
    }
}

class Switch {
    // instance variable
    private int flag;

    // constructor
    Switch() { flag = 0; }

    // methods
    public boolean check() { return (flag % 2 == 0); }
    public void flip() { flag++; }
}
