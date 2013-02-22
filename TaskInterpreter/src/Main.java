import Interpreter.Nodes.Expression;
import Interpreter.Nodes.Node;
import Interpreter.Nodes.Number;
import Interpreter.Parser.Parser;


/**
 * @author vkaliteevskiy
 * interpreter
 * (c)2012
 */

public class Main {
	public static void main(String[] args) throws Exception {
       
        Parser p = new Parser();
        LazyInterpreter i = new LazyInterpreter();
        Node n = p.ParseExpr("let x = 3 in x+1");
        n = i.evalExpr((Expression)n);
        System.out.print(((Number)n).getValue());
        

	}

}