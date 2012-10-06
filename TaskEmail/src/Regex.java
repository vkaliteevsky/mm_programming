import java.util.regex.*;

public class Regex {
    private static String 
    		s1 = "[a-zA-Z]{1}[a-zA-Z[0-9]\u005F\u002E\u002D]*";
    private static String 
			s2 = "[a-zA-Z]{2,3}|(name)|(info)|(asia)|(mobi)";
    public static final Pattern p = Pattern.compile
    		(s1 + "\u0040" + s1 + "\u002E" +s2);
    		
    public static boolean check(String s){
        Matcher m = p.matcher(s);   	
        return (m.matches());
    }
}