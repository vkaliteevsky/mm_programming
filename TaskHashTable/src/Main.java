/*
 * Калитеевский
 * (с)2012
 */

import java.io.IOException;


public class Main {


	public static void main(String[] args) throws IOException {
		TextAnalysis text = new TextAnalysis();
		text.analize("file.txt");
//		System.out.print("Ok");
		text.results();
	}

}
