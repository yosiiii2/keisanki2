import java.io.*;
import java.util.regex.*;

class FindFromFile {
    public static void main(String[] args) {
	if(args.length < 2) return;
	try {
	    String filename = new BufferedReader(new InputStreamReader(System.in)).readLine();
	    Pattern pat = Pattern.compile(args[0] + ".*?" + args[1]);
	    String line;
	    BufferedReader filein = new BufferedReader(new FileReader(filename));
	    while (null != (line = filein.readLine())) {
		Matcher mat = pat.matcher(line);
		while(mat.find()) {
		    System.out.println(mat.group(0));
		}
	    }
	    filein.close();
	} catch (IOException e) {}
    }
}
