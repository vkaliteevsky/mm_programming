/**
 * @author vkaliteevskiy
 * MatrixMult
 * (c)2012
 */

import static org.junit.Assert.*;

import org.junit.Test;

public class MatrixMultTest {

	@Test
	public void testMatrix() throws InterruptedException {
		int[][] A = { { 1, 1 }, { 1, 1 }, { 1, 1 } };
		int[][] B = { { 1, 1, 1, 1 }, { 1, 1, 1, 1 } };
		int[][] res = { { 2, 2, 2, 2 }, { 2, 2, 2, 2 }, { 2, 2, 2, 2 } };
		MatrixMult mm = new MatrixMult(A, B);
		mm.multiply();
		assertArrayEquals(res, mm.getResult());
	}

	@Test
	public void testMatrix2() throws InterruptedException {
		int[][] A = { { 1 } };
		int[][] B = { { 1 } };
		int[][] res = { { 1 } };
		MatrixMult mm = new MatrixMult(A, B);
		mm.multiply();
		assertArrayEquals(res, mm.getResult());
	}

	@Test
	public void testMatrix3() throws InterruptedException {
		int[][] A = { { 1, 2 }, { 6, 2 }, { 5, 2 } };
		int[][] B = { { 1, 6, 8, 4, 84, 35, 35 }, { 1, 13, 4, 23, 4, 3, 35 } };
		int[][] res = { { 3, 32, 16, 50, 92, 41, 105 },
			         	{ 8, 62, 56, 70, 512, 216, 280, },
				        { 7, 56, 48, 66, 428, 181, 245 } };
		MatrixMult mm = new MatrixMult(A, B);
		mm.multiply();
		assertArrayEquals(res, mm.getResult());
	}
}
