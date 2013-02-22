/**
 * @author vkaliteevskiy
 * Palindrome
 * (c)2012
 */



public class Insensitive extends Palindrom {
	@Override
	boolean equals(Character a, Character b){ 
		Character.toLowerCase(a);
		Character.toLowerCase(b);
		if (a.equals(b)) {
			return true;
		} else {
			return false;
		}		
	}
}
