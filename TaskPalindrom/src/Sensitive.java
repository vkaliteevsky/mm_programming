/**
 * @author vkaliteevskiy
 * Palindrome
 * (c)2012
 */


public class Sensitive extends Palindrom {

	
	@Override
	boolean equals(Character a, Character b){ 
		if (a.equals(b)) {
			return true;
		} else {
			return false;
		}		
	}
}
