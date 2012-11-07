/*
 * Калитеевский В.Н.
 * (с)2012
 * Palindrom
 */

public class Main {
	public static void main(String arg[]) {
		String s;
		s = "A bc cBa ";
		s = s.replace(" ", "");
		String s1;
		String s2;
		s1 = s.substring(0, s.length() / 2);
		s2 = s.substring(s.length() - s.length() / 2, s.length());
		s2 = new StringBuffer(s2).reverse().toString();
		Sensitive str = new Sensitive();
		Insensitive str2 = new Insensitive();
		str.isPalindrom(s1, s2);
		str2.isPalindrom(s1, s2);
	}	
}

