/*
 * Калитеевский В.Н.
 * (с)2012
 * Palindrom
 */

public class Sensitive extends Palindrom {
	public boolean isPalindrom (String s) {
		String s1;
		String s2;
		s1 = s.substring(0, s.length() / 2);
		s2 = s.substring(s.length() - s.length() / 2, s.length());
		s2 = new StringBuffer(s2).reverse().toString();
		if (s1.equals(s2))
			System.out.print("It's sensitive palindrome\n");
		else
			System.out.print("It isn't sensitive palindrome\n");
		return false;
	}
}
