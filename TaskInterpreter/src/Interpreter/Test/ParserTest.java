package Interpreter.Test;

import static org.junit.Assert.*;

import org.junit.Test;

import Interpreter.Nodes.Node;
import Interpreter.Parser.Parser;

public class ParserTest {

	@Test
	public void testParseExpr() throws Exception {
		String text = "let f = fun x -> fun y -> x + y in f 1 (f 1 (f 1 1))";
		Parser instance = new Parser();
		String expResult = "(let f = ((fun x -> (fun y -> (x+y)))) in ((call (call f (1)) ((call (call f (1)) ((call (call f (1)) (1))))))))";
		String result = instance.ParseExpr(text).toString();
		assertEquals(expResult, result);
	}

}
