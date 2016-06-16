import java.net.*;
import java.io.*;

class Client {
	public static void main(String[] args) {
		if (args.length < 2) return;
		try {
			Socket s = new Socket(args[0], Integer.parseInt(args[1]));
			BufferedReader in = new BufferedReader(new InputStreamReader(s.getInputStream()));
			PrintWriter out = new PrintWriter(s.getOutputStream(),true);
			String buf;

			// send request to server
			out.print(InetAddress.getLocalHost().getHostName() + "\r\n");
			out.println("\r\n");

			// receive contents from server
			while (null != (buf = in.readLine())) {
			    System.out.println(buf);
			}
			in.close();
			out.close();
			s.close();
		} catch (UnknownHostException e) {
			System.out.println("Unknown host.");
			System.exit(1);
		} catch (IOException e) {
			System.out.println("IO exception.");
			System.exit(1);
		}
	}
}
