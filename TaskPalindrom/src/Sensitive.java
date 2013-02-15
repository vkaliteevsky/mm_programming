/*
 * Калитеевский В.Н.
 * (с)2012
 * Palindrom
 */

public class Sensitive extends Palindrom {
	public boolean isPalindrom(String s) {
		int j = s.length() - 1;
		int i = 0;
		int avr = (int) Math.floor(s.length() / 2) - 1;
		while (i <= avr) {

			while (!(('a' <= s.charAt(i) && s.charAt(i) <= 'z') || ('A' <= s.charAt(i) && s.charAt(i) <= 'Z') || Character.isDigit(s.charAt(i)))) {
				i++;
			}
			while (!(('a' <= s.charAt(j) && s.charAt(j) <= 'z') || ('A' <= s.charAt(j) && s.charAt(j) <= 'Z') || Character.isDigit(s.charAt(j)))) {
				j--;
			}
			if (s.charAt(i) != s.charAt(j)) {
				System.out.print("It isn't sensitive palindrome\n");
				return false;
			}
		}
		System.out.print("It's sensitive palindrome\n");
		return true;
	}
}
