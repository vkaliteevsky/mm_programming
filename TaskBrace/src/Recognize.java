import java.util.Stack;


public class Recognize {
	public static boolean recognize(String s){
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
        		br.style = 1;
        		br.name = "[";
           		stack.push(br);
        		break;
        		
        	case ')':
        		if(stack.empty() || !stack.pop().name.equals("(")){
        			System.out.print("Not passed");
        			stack.pop();
        			return false;
        		}
        		break;
        		
        	case ']':
        		if(stack.empty() || !stack.pop().name.equals("[")){
        			System.out.print("Not passed");
        			return false;
        		}

        		break;        		
        	case '<':
        		if ((s.charAt(i+1)=='/')){
            		br.style = 2;
            		i++;
            		i++;
	        		while (!(s.charAt(i)=='>')){
	        			
	        			br.name = br.name.concat(String.valueOf((char)s.charAt(i)));
	        			i++;
	        		}    	
	    			
	    			if(s.charAt(i)==' '){
	    				while (!(s.charAt(i)=='>')){
	    					i++;
	    				}
	    			}
	        		if(stack.empty() || !stack.pop().name.equals(br.name)){
	        			System.out.print("Not passed");
	        			return false;
	        		}	    			
        		} else {
	    			br.style = 1;
	        		i++;
	        		while (!(s.charAt(i)==' ')&&!(s.charAt(i)=='>')){
	        			
	        			br.name = br.name.concat(String.valueOf((char)s.charAt(i)));
	        			i++;
	        		}    	
	    			stack.push(br);
	    			if(s.charAt(i)==' '){
	    				while (!(s.charAt(i)=='>')){
	    					i++;
	    				}
	    			}		
	        	}
        		break;
        	}
		}
		if (stack.empty()) {
			System.out.print("Yes");
			return true;

		} 
		else {
			System.out.print("No");
			return false;

		}

	}
}