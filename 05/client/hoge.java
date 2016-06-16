import java.net.*;
import java.io.*;
import java.util.*;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

class Browse{
	URL url;
	String contents;
	String[] links = new String[1000];
	int i = 0;
	int links_n;

	//constractor
	
	public Browse(URL hoge){
		url = hoge;
		contents = "";
		links_n = 0;
	}

	//method
	
	public void collectLinks(String line){
		Pattern ptn = Pattern.compile("(?i)<a.*?href=\"(.*?)\".*?>(.*?)</a>", Pattern.DOTALL);
		Matcher matcher = ptn.matcher(line);
		if (matcher.find()) {
			String href = matcher.group(1).replaceAll("\\s", "");
			int file_or = href.indexOf("http://");

			if(file_or == -1){
				contents = url.scheme + "://" + url.host + "/" + href;
			}else{
				contents = href;
			}			
			links[links_n+1]=contents;
			links_n++;
		}
	}

	
	public void printLinks(){
		System.out.println("\n");
		System.out.println("test");

		for(i = 1;i < links_n;i++){
			System.out.println(i+" "+links[i]);
		}
		return;
	}

	
	public String getLink(int n){
		while(n > links_n){
			System.out.println("number error!");
		}
		return links[n];		
	}

}


class URL{

	String scheme = new String();
	String host = new String();
	int port;
	String path = new String();
	int success = 1;

	public URL(String all){
		int schemeEnd = all.indexOf("://");

		//url.pathとかで実装できたことに気づかなかった……
		
		if(schemeEnd == -1){
			System.out.println("Wrong URL! at scheme");
			success = 0;
			return;
		}
		
		scheme = all.substring(0,schemeEnd);
	   
		int hostBegin = schemeEnd + 3;
		String schemeless = all.substring(hostBegin);
		
		String urls[] = schemeless.split("/",2);//split the path

		try{
			path = urls[1];
		}
		catch(java.lang.ArrayIndexOutOfBoundsException e){
			path = "";
		}

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
   
	public boolean intCheck(String str){
		for (int i = 0; i < str.length(); i++) {
			if(str.charAt(i)<'0'||str.charAt(i)>'9') return true;
		}
		return false;
	}
	
	public boolean isHtml(){
		int is = scheme.compareToIgnoreCase("http");
		return (is == 0);
	}

}



class ClientMain {
	public static void main(String[] args) {
		Deque<String> history = new ArrayDeque<>();
		while(true){
			System.out.println("Input URL");
			System.out.println("This program ends with 'end'");
			Scanner sc = new Scanner(System.in);
			String all = sc.next();

			if((all.compareToIgnoreCase("end")) == 0) break;

			while(true){
				//stackに積む
				//backのときはどうしよう
				URL using = new URL(all);
 				if(using.success==0) break;

				Browse page = new Browse(using);
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
						page.collectLinks(buf);
					}
					System.out.println("test");

					page.printLinks();
					
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
				System.out.println("Input number");
				while(true){
					System.out.println("This program ends with 0");
					System.out.println("Goto last page with -1");
					Scanner sc2 = new Scanner(System.in);
					try{
						int num = sc2.nextInt();
						if(num == 0) return;
						if(num == -1) {
							try {
								all = history.removeFirst();
								break;
							} catch (NoSuchElementException e) {
								System.out.println("There isn't any history!");
								continue;
							}
						}
						history.addFirst(all);
						all = page.getLink(num);
						break;
					}
					catch(InputMismatchException e){
						System.out.println("input number!!");
					}
				}

			}
		}
	}
}
