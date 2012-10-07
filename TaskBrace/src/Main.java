//Проверка скобочной последовательности на правильное расположение
//Калитеевский В.Н.
//(с)2012

import java.util.Scanner;

public class Main {

	@SuppressWarnings("resource")
	public static void main(String[] args) {

		Scanner sc = new Scanner(System.in);
		String s = sc.nextLine(); 	
		Recognize.recognize(s);
	}

}
