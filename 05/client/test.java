import java.util.*;


class URL{

	String all = "http://www.hoge:8000/huga/";
	String scheme = new String();
	String host = new String();
	int port;
	String path = new String();

	void cutUrl(){

		int schemeEnd = all.indexOf("://");
		scheme = all.substring(0,schemeEnd);

		int hostBegin = schemeEnd + 3;
		String schemeless = all.substring(hostBegin);

		//System.out.println(schemeless);
		
		String urls[] = schemeless.split("/",2);//split the path
		path = urls[1];
		
		int pathBegin = urls[0].indexOf(":");
		
		if(pathBegin == -1){
			//path doesn't exist
			host = urls[0];
			port = 80;
		}else{
			//path exists
			host = urls[0].substring(0,pathBegin);
			port = Integer.parseInt(urls[0].substring(pathBegin+1));
		}		
		   	
	}
	
}


class Main{

	public static void main(String[] args) {
		// String str = "abcdefghijklmn";
		// String hoge = str.substring(1,5);//substring(start,number)
		// //		str++;
		// System.out.println(str);
		//		System.out.println(hoge);
		URL using = new URL();
		using.cutUrl();
		System.out.println(using.scheme);
		System.out.println(using.host);
		System.out.println(using.port);
		System.out.println(using.path);

	}


}
