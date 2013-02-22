/**
 * @author vkaliteevskiy
 * MatrixMult
 * (c)2012
 */


public class Main {
	public static void main(String[] args) throws InterruptedException {
		//int [][] A = {{1,1},{1,1},{1,1}};
		//int [][] B = {{1,1,1,1},{1,1,1,1}};
		int [][] A = {{1,2},{6,2},{5,2}};
		int [][] B = {{1, 6, 8, 4, 84, 35, 35},{1, 13, 4, 23, 4, 3, 35}};
		MatrixMult mm = new MatrixMult(A, B);
		mm.multiply();
		mm.show();

	}

}
