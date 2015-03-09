import java.util.Hashtable;


public class hw1 {

	public static String xorHex(String a, String b) {
	    // TODO: Validation
	    char[] chars;
	    if(a.length() <= b.length()) 
	    	chars = new char[a.length()];
	    else
	    	chars = new char[b.length()];
	    for (int i = 0; i < chars.length; i++) {
	        chars[i] = toHex(fromHex(a.charAt(i)) ^ fromHex(b.charAt(i)));
	    }
	    return new String(chars);
	}

	private static int fromHex(char c) {
	    if (c >= '0' && c <= '9') {
	        return c - '0';
	    }
	    if (c >= 'A' && c <= 'F') {
	        return c - 'A' + 10;
	    }
	    if (c >= 'a' && c <= 'f') {
	        return c - 'a' + 10;
	    }
	    throw new IllegalArgumentException();
	}

	private static char toHex(int nybble) {
	    if (nybble < 0 || nybble > 15) {
	        throw new IllegalArgumentException();
	    }
	    return "0123456789ABCDEF".charAt(nybble);
	}
	
	/*
	 * Space XOR letters
	 * 41 - 5A : a - z
	 * 61 - 7A : A - Z
	 */
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		In in = new In("hw1.txt");
		String[] cipherText = new String[11];
		for(int i=0; i<11; i++){
			cipherText[i] = in.readLine();
		}
		
		Hashtable<String, String> numbers = new Hashtable<String, String>();
	    numbers.put("41", "a");	numbers.put("61", "A");
	    numbers.put("42", "b");	numbers.put("62", "B");
	    numbers.put("43", "c");	numbers.put("63", "C");
	    numbers.put("44", "d");	numbers.put("64", "D");
	    numbers.put("45", "e");	numbers.put("65", "E");
	    numbers.put("46", "f");	numbers.put("66", "F");
	    numbers.put("47", "g");	numbers.put("67", "G");
	    numbers.put("48", "h");	numbers.put("68", "H");
	    numbers.put("49", "i");	numbers.put("69", "I");
	    numbers.put("4A", "j");	numbers.put("6A", "J");
	    numbers.put("4B", "k");	numbers.put("6B", "K");
	    numbers.put("4C", "l");	numbers.put("6C", "L");
	    numbers.put("4D", "m");	numbers.put("6D", "M");
	    numbers.put("4E", "n");	numbers.put("6E", "N");
	    numbers.put("4F", "o");	numbers.put("6F", "O");
	    numbers.put("50", "p");	numbers.put("70", "P");
	    numbers.put("51", "q");	numbers.put("71", "Q");
	    numbers.put("52", "r");	numbers.put("72", "R");
	    numbers.put("53", "s");	numbers.put("73", "S");
	    numbers.put("54", "t");	numbers.put("74", "T");
	    numbers.put("55", "u");	numbers.put("75", "U");
	    numbers.put("56", "v");	numbers.put("76", "V");
	    numbers.put("57", "w");	numbers.put("77", "W");
	    numbers.put("58", "x");	numbers.put("78", "X");
	    numbers.put("59", "y");	numbers.put("79", "Y");
	    numbers.put("5A", "z");	numbers.put("7A", "Z"); 
	    
	    String[] partialResult = new String[10];
	    String result;
		for(int i=0; i<10; i++){
			result = xorHex(cipherText[i], cipherText[10]);
			//StdOut.println(result);
			char[] outputStr = new char[result.length()/2];
			for(int j=0; j<result.length(); j=j+2){
				String temp = result.substring(j, j+2);
				
				if(numbers.containsKey(temp)){
					StdOut.print( numbers.get(temp) );
					outputStr[j/2] = numbers.get(temp).charAt(0);
				}
				else{
					StdOut.print( '-' );
					outputStr[j/2] = '-';
				}
			}
			StdOut.println();
			partialResult[i] = outputStr.toString();
		}
		
		
	}

}
