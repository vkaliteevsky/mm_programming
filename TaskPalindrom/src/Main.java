/*
 * Калитеевский В.Н.
 * (с)2012
 * Palindrom
 */

public class Main {
	public static void main(String arg[]) {
		String s;
		s = "abccba";
		s = s.replace(" ", "");
		
		Sensitive str = new Sensitive();
		Insensitive str2 = new Insensitive();
		str.isPalindrom(s);
		str2.isPalindrom(s);
	}	
}

