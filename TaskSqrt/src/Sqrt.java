
public class Sqrt {
	public static double sqrt(double d){
		double a = d/2;
		double tmp;
		for(;;){
			tmp = a;
			a = (a + d/a)/2;			
			if (a == tmp){
				break;
			}
		}
		return a;
	}


}
