import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;


public class TextAnalysis {
	private HashTable table;
	
	TextAnalysis() {
		table = new HashTable(500);

		
	}
	private void add(String s){
		table.add(s);
	}
	
	public void analize(String path) throws IOException{
		BufferedReader br = new BufferedReader(new FileReader(path));
		String word="";
		int c;
		while (br.ready()){
			c = br.read();
			String a = Character.toString((char) c);
			while (Character.isLetterOrDigit(c)){
				word = word + Character.toString((char) c);
				word = word.toLowerCase();
				c = br.read();
			}
			if (!word.equals("")) add(word);
			word = "";
		}
		br.close();
	}
	
	public void results(){
		table.results();
	}
}
