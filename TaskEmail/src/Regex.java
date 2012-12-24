import java.util.regex.*;

/*
 * 002D -
 * 005F _
 * 002E .
 * 0040 @
 */
public class Regex {   		
    public static boolean check(String s){   	
    	String s1 = "([a-zA-Z]|[\u005F]){1}[a-zA-Z[0-9][\u005F\u002D]{1}]*";
    	String s2 = s1 + "[\u002E" + s1 + "]*";
    	String s3 = "([a-zA-Z]+\\u002E)*";
    	String s4 = "((name)|(asia)|(mobi)|(info)|(travel)|(jobs)|(aero)|(museum)|(coop)|([a-zA-Z]{2,3}))";

       	Pattern p = Pattern.compile(s2 + "@" +s3 +s4);
    	
    	Matcher m = p.matcher(s);   	
        return (m.matches());
    }
}