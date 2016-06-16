import java.net.*;
import java.io.*;

class Server {
	public static void main(String[] args) {
		if (args.length < 2) return;
		try {
			ServerSocket serverS = new ServerSocket(Integer.parseInt(args[0]));
			while (true) {
				new ServerThread(serverS.accept(), Integer.parseInt(args[1])).start();
				System.out.println("New connection.");
			}
		} catch  (IOException e) {
			System.out.println("IO exception.");
			System.exit(1);
		}
	}
}

class ServerThread extends Thread {
	Socket clientS;
	int sleepTime;

	public ServerThread(Socket acceptedS, int msec) {
		clientS = acceptedS;
		sleepTime = msec;
	}

	public void run() {
		try {
			PrintStream out = new PrintStream(clientS.getOutputStream(), true);
			BufferedReader in = new BufferedReader(new InputStreamReader(clientS.getInputStream()));
			String buf;

			// receive requests from client (until an empty line)
			while(null != (buf = in.readLine())) {
			    if(buf.equals("")) {
				break;
			    } else {
				System.out.println(buf);
			    }
			}

			// send contents to client
			for (int n = 0; n < 10; n++) {
				try {
					sleep(sleepTime);
				} catch (InterruptedException e) {}
				out.println(Math.random());
			}
			out.close();
			in.close();
			clientS.close();
		} catch  (IOException e) {
			System.out.println("IO exception.");
			System.exit(1);
		}
	}
}
