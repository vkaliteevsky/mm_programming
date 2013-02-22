/*   Calc
     Kaliteevskiy V.
     (c)2012
*/

import java.io.IOException;

public class Main {
	public static void main(String[] args) throws Exception {
		String[] exprs = { "nn = 4", "a=(2+nn)*14", "a+4" };
		Parser parser = new Parser(exprs);
		int[] result = parser.start();
		for (int i = 0; i < result.length; i++) {
			System.out.println(result[i]);
		}
	}
}