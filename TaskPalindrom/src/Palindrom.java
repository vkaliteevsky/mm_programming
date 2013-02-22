/**
 * @author vkaliteevskiy
 * Palindrome
 * (c)2012
 */



abstract class Palindrom {
	public boolean isPalindrom(String s) {
		int j = s.length() - 1;
		int i = 0;
		int avr = (int) Math.floor(s.length() / 2) - 1;
		while (i < j) {

			while (!(Character.isLetterOrDigit(s.charAt(i)))) {
				i++;
				if (i == j) return true;
			}
			
			while (!(Character.isLetterOrDigit(s.charAt(j)))) {
				j--;
			}
			
			
			if (!equals(s.charAt(i), s.charAt(j))){
				return false;
			}
			i++;
			j--;
			
		}
		
		return true;
	}
	
	abstract boolean equals(Character a, Character b);
	
}
