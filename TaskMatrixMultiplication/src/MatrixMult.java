import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;


public class MatrixMult {
	private int [][] A;
	private int [][] B;
	private int [][] C;
	
	MatrixMult(int [][] A_, int [][] B_){
		A = A_;
		B = B_;
		C = new int [A.length][B[0].length];
	}
    private class Thread implements Runnable{        
        int i, j;
    	Thread(int n,int m){
        	 i = n;
        	 j = m;
        }
    	
    	public void run() {
          // System.out.print("run");
            int tmp = 0;
            int res = 0;

            for(int n = 0; n < A[0].length; n++){
                    tmp += A[i][n]*B[n][j];
            }

            res = tmp;
            C[i][j] = res;
            
    	}
    
    }
	
	private boolean resolution (int [][] A, int[][] B){
        int tmp_A = A[0].length;
        int tmp_B = B[0].length;
        int length_A = A.length;
        int length_B = B.length;
		if ((length_A == 0) || (length_B == 0)) {
			return false;
        }
        for(int i = 1; i < length_A; i++) {
            if (tmp_A != A[i].length) {
                return false;
            }
        }

        for(int i = 1; i < length_B; i++) {
            if (tmp_B != B[i].length) {

                return false;
            }
        }
        if (A[0].length != B.length) {
            return false;
        }
        return true;
	}

	public void multiply() throws InterruptedException{
		if (!(resolution(A, B))){
			throw new IllegalArgumentException();
		}

        ExecutorService ex;
        ex = Executors.newCachedThreadPool();
        
        
        for(int i = 0; i < A.length; i++) {
        	for(int j = 0; j < B[0].length; j++) {
        		ex.submit(new Thread(i, j));
        	}
        }
        
        try {
            ex.awaitTermination(2, TimeUnit.SECONDS);
        }catch (InterruptedException e) {
             e.printStackTrace();
        }
        return;
        
	}
	
	public void show(){
        for(int i = 0; i < C.length; i++) {
        	for(int j = 0; j < C[0].length; j++) {
        		System.out.print(C[i][j] + " ");
        		if(j == C[0].length - 1){
        			System.out.print("\n");
        		}
        	}
        }
	}
	
	public int [][] getResult(){
		return C;
	}
}
