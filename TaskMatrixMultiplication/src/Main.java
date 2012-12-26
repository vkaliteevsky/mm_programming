

/*Калитеевский В.
 *271 группа
 *Перемножение матриц параллельно
 *(с)2012 
 */
public class Main {
	public static void main(String[] args) {
		int [][] A = {{1,1},{1,1},{1,1}};
		int [][] B = {{1,1,1,1},{1,1,1,1}};
		MatrixMult mm = new MatrixMult(A, B);
		int [][] C = mm.multiply();

	}

}
