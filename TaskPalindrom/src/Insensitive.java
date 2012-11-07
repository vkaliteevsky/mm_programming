/*
 * Калитеевский В.Н.
 * (с)2012
 * Palindrom
 */

public class Insensitive extends Palindrom {
	public boolean isPalindrom (String s1, String s2) {
		String str_1="";
		String str_2="";
		for (int i = 0; i < s1.length() - 1; i++) {
			str_1 += Character.toLowerCase(s1.charAt(i));
			str_2 += Character.toLowerCase(s2.charAt(i));
		}
		if (str_1.equals(str_2))
			System.out.print("It's insensitive palindrome\n");
		else
			System.out.print("It isn't insensitive palindrome\n");
		return false;
	}
}
