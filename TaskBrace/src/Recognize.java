//import java.io.PrintWriter;
import java.util.Stack;


public class Recognize {
	public static void recognize(String s){
//		PrintWriter out = new PrintWriter(System.out);
		Stack<Brace> stack = new Stack<Brace>();		

		for (int i = 0; i < s.length(); i++) {
			Brace br = new Brace(); 
			switch(s.charAt(i)){
        	case '(':

        		br.style = 1;
        		br.name = "(";
     		
        		stack.push(br);
        		break;
        	case '[':
//        		Brace br = new Brace(); 
        		br.style = 1;
        		br.name = "[";
     		
        		stack.push(br);
        		break;
        	case ')':
        		if(stack.empty() || !stack.pop().name.equals("(")){
        			System.out.print("Not passed");
        			stack.pop();
        			return;

        		}

        		break;
        	case ']':
        		if(stack.empty() || !stack.pop().name.equals("[")){
        			System.out.print("Not passed");
        			return;
        		}

        		break;        		
        	case '<':
        		if ((s.charAt(i+1)=='/')){//closing brace
//            		Brace br = new Brace(); 
            		br.style = 2;
            		i++;
            		i++;
	        		while (!(s.charAt(i)=='>')){
	        			
	        			br.name = br.name.concat(String.valueOf((char)s.charAt(i)));
	        			i++;
	        		}
//	    			System.out.print(br.name);        	
	    			
	    			if(s.charAt(i)==' '){
	    				while (!(s.charAt(i)=='>')){
	    					i++;
	    				}
	    			}
	        		if(stack.empty() || !stack.pop().name.equals(br.name)){
	        			System.out.print("Not passed");
	        			return;
	        		}	    			
        		} else {//opening brace
//	        		Brace br = new Brace();
	    			br.style = 1;
	        		i++;
	        		while (!(s.charAt(i)==' ')&&!(s.charAt(i)=='>')){
	        			
	        			br.name = br.name.concat(String.valueOf((char)s.charAt(i)));
	        			i++;
	        		}
//	    			System.out.print(br.name);        	
	    			stack.push(br);
	    			if(s.charAt(i)==' '){
	    				while (!(s.charAt(i)=='>')){
	    					i++;
	    				}
	    			}
//	    			System.out.print(s.charAt(i));      			
	        	}
        		break;
        	}

    		
        
        
        }
		if (stack.empty()) {
			System.out.print("Yes");
		} 
		else {
			System.out.print("No");
		}

}
}