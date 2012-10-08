//Количество возможных путей до выбранной точки от начала координат 
//Калитеевский В. Н.
//(с) 2012

import java.util.Scanner;

public class Main {

	public static void main(String arg[]) {
		Path a = new Path();
		Scanner sc = new Scanner(System.in);
		a.x = sc.nextInt();
		a.y = sc.nextInt();	
		int ans = a.binom();
		System.out.print(ans);
	}
}
