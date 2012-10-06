//Регулярные выражения на примере проверки электронного адреса  
//Калитеевский В.Н.
//(с)2012

import java.util.Scanner;


public class Email {
	public static void main(String[] args){
		Scanner sc = new Scanner(System.in);
		String s = sc.next();
		if (Regex.check(s))
			System.out.print("yes");
		else 			
			System.out.print("no");
			
		}

}
