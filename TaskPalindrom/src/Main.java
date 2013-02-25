/**
 * @author vkaliteevskiy
 * Palindrome
 * (c)2012
 */


public class Main {
	public static void main(String arg[]) {
		String s;
		s = "jJ";
		s = s.replace(" ", "");
		
		Sensitive str = new Sensitive();
		Insensitive str2 = new Insensitive();
		if (str.isPalindrom(s)){
			System.out.print("It is sensitive palindrome\n");
		} else {
			System.out.print("It isn't sensitive palindrome\n");
		}
		if (str2.isPalindrom(s)){
			System.out.print("It is insensitive palindrome\n");
		} else {
			System.out.print("It isn't insensitive palindrome\n");
		}
	}	
}

