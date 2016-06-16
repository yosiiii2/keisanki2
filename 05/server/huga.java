import java.net.*;
import java.io.*;

class SerMain{
	public static void main(String[] args) {
		if (args.length < 1) return;
		try {
			ServerSocket serverS = new ServerSocket(Integer.parseInt(args[0]));
			while (true) {
				new ServerThread(serverS.accept()).start();
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
	int sleepTime = 100;

	public ServerThread(Socket acceptedS) {
		clientS = acceptedS;
	}

	public void run() {
		try {
			PrintStream out = new PrintStream(clientS.getOutputStream(), true);
			BufferedReader in = new BufferedReader(new InputStreamReader(clientS.getInputStream()));
			String[] buf = {" "," "," "," "};
			int i=0;

			
			// receive requests from client (until an empty line)
			while(null != (buf[i] = in.readLine())) {
			    if(buf[i].equals("")) {
					break;
			    } else {
					i++;
			    }
			}

			String req[] = buf[0].split(" ",0);
			String dir = req[1];
		    dir = dir.substring(1);

			try {
				FileInputStream fis = new FileInputStream(dir);
				InputStreamReader isr = new InputStreamReader(fis);
				BufferedReader br = new BufferedReader(isr);
				String msg;
				while ( ( msg = br.readLine()) != null ) {
					try {
						sleep(sleepTime);
					} catch (InterruptedException e) {}
					out.println(msg);
				}
				br.close();     
			} catch(Exception e) {
				e.printStackTrace();
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
