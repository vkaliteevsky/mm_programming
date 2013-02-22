/**
 * @author vkaliteevskiy
 * Calc
 * (c)2012
 */

import static org.junit.Assert.*;

import org.junit.Test;

public class ParserTest {

	@Test
	public void test() throws Exception {
		String[] exprs = { "x = 4" };
		Parser parser = new Parser(exprs);
		int[] result = parser.start();
		int[] expectResult = { 4 };
		assertArrayEquals(expectResult, result);
	}

	@Test
	public void test2() throws Exception {
		String[] exprs = { "x = 4", "y = x + x", "z = y + x" };
		Parser parser = new Parser(exprs);
		int[] result = parser.start();
		int[] expectResult = { 4, 8, 12 };
		assertArrayEquals(expectResult, result);
	}
	
	@Test
	public void test3() throws Exception {
		String[] exprs = {"x = 4", "y = x * x", "z = y * x"};
		Parser parser = new Parser(exprs);
		int[] result = parser.start();
		int[] expectResult = { 4, 16, 64 };
		assertArrayEquals(expectResult, result);
	}
}
