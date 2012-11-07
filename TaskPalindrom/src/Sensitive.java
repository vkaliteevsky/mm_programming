/*
 * Калитеевский В.Н.
 * (с)2012
 * Palindrom
 */

public class Sensitive extends Palindrom {
	public boolean isPalindrom (String s1, String s2) {
		if (s1.equals(s2))
			System.out.print("It's sensitive palindrome\n");
		else
			System.out.print("It isn't sensitive palindrome\n");
		return false;
	}
}
