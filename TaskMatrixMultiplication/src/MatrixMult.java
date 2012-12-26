import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;


public class MatrixMult {
	private int [][] A;
	private int [][] B;
	private int [][] C;
	
	MatrixMult(int [][] A_, int [][] B_){
		A = A_;
		B = B_;
	}
    private class Thread implements Runnable{        
        int i, j;
    	Thread(int n,int m){
        	 i = n;
        	 j = m;
        }
    	
    	public void run() {
           System.out.print("run");
            int tmp = 0;
            int res = 0;

            for(int n = 0; i < A[0].length; n++){
                for(int m = 0; j < A[0].length; m++){
                    tmp += A[i][n]*B[m][j];
                }
                res = tmp;
            }
            C[i][j] = res;
    	}
    
    }
	
	private boolean resolution (int [][] A, int[][] B){
        int tmp_A = A[0].length;
        int tmp_B = B[0].length;
        int length_A = A.length;
        int length_B = B.length;
		if ((length_A == 0) || (length_B == 0)) {
         System.out.print("length_A == 0) || (length_B == 0");
			return false;
        }
        for(int i = 1; i < length_A; i++) {
            if (tmp_A != A[i].length) {
                System.out.print("tmp_A != A[i].length");
                return false;
            }
        }

        for(int i = 1; i < length_B; i++) {
            if (tmp_B != B[i].length) {
                System.out.print("tmp_B != B[i].length");

                return false;
            }
        }
        if (A[0].length != B.length) {
            System.out.print("A[0].length != B.length");	
            return false;
        }
        return true;
	}
	public int[][] multiply(){
		int[][]C = null;
		if (!(resolution(A, B))){
			return C;
		}

        ExecutorService ex;
        ex = Executors.newCachedThreadPool();
        
        
        for(int i = 0; i < A.length; i++) {
        	for(int j = 0; j < B[0].length; j++) {
        		ex.submit(new Thread(i, j));
        	}
        }
        for(int i = 0; i < C.length; i++) {
        	for(int j = 0; j < C[0].length; j++) {
        		System.out.print(C[i][j]);
        	}
        }
        ex.shutdown();
        return C;
	}
}
