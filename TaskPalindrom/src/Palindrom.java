/**
 * @author vkaliteevskiy
 * Palindrome
 * (c)2012
 */



abstract class Palindrom {
	public boolean isPalindrom(String s) {
		int j = s.length() - 1;
		int i = 0;
		while (i < j) {

			if (!(Character.isLetterOrDigit(s.charAt(i)))) {
				i++;

			}

			if (!(Character.isLetterOrDigit(s.charAt(j)))) {
				j--;
			}

			if (!equals(s.charAt(i), s.charAt(j))) {
				return false;
			}
			i++;
			j--;

		}

		return true;
	}

	abstract boolean equals(Character a, Character b);

}
