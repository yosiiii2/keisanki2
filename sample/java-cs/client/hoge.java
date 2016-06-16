import java.net.*;
import java.io.*;
import java.util.*;

//constractor
//tyr catch

class URL{

	String all = new String();
	String scheme = new String();
	String host = new String();
	int port;
	String path = new String();
	int success = 1;
	
	void cutUrl(){
		int schemeEnd = all.indexOf("://");
		if(schemeEnd == -1){
			System.out.println("Wrong URL! at scheme");
			success = 0;
			return;
		}
		
		scheme = all.substring(0,schemeEnd);
	   
		int hostBegin = schemeEnd + 3;
		String schemeless = all.substring(hostBegin);

		//System.out.println(schemeless);
		
		String urls[] = schemeless.split("/",2);//split the path
		path = urls[1];

		if(path.indexOf(":") != -1){
			System.out.println("Wrong URL!! at path");
			success = 0;
			return;
		}
		
		int pathBegin = urls[0].indexOf(":");
		
		if(pathBegin == -1){
			//port doesn't exist
			host = urls[0];
			port = 80;
		}else{
			//port exists

			host = urls[0].substring(0,pathBegin);

			if(intCheck(urls[0].substring(pathBegin+1))){
				System.out.println("Wrong URL!!! at port");
				success = 0;
				return;
			}

			port = Integer.parseInt(urls[0].substring(pathBegin+1));
		}				   	
	}

	boolean intCheck(String str){
		for (int i = 0; i < str.length(); i++) {
			if(str.charAt(i)<'0'||str.charAt(i)>'9') return true;
		}
		return false;
	}
	
	boolean isHtml(){
		int is = scheme.compareToIgnoreCase("http");
		return (is == 0);
	}

}



class ClientMain {
	public static void main(String[] args) {
		while(true){
			System.out.println("Input URL");
			System.out.println("This program ends with 'end'");
			Scanner sc = new Scanner(System.in);
			URL using = new URL();
			using.all = sc.next();

			if((using.all.compareToIgnoreCase("end")) == 0) break;

			using.cutUrl();

			if(using.success==0) continue;
			if(using.isHtml() == false){
				System.out.println("Its scheme isn't http");
				continue;
			}

			try {
				Socket s = new Socket(using.host, using.port);
				BufferedReader in = new BufferedReader(new InputStreamReader(s.getInputStream()));
				PrintWriter out = new PrintWriter(s.getOutputStream(),true);
				String buf;

				// send request to server
			
				out.print("GET /" + using.path + " HTTP/1.1\r\n");
				out.print("Host: " + using.host + "\r\n");
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
}
