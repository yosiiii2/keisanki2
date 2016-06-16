import java.io.*;

class PrintFile {
    public static void main(String[] args) {
	try {
	    String filename = new BufferedReader(new InputStreamReader(System.in)).readLine();
	    String line;
	    BufferedReader filein = new BufferedReader(new FileReader(filename));
	    while (null != (line = filein.readLine())) {
		System.out.println(line);
	    }
	    filein.close();
	} catch (IOException e) {}
    }
}
