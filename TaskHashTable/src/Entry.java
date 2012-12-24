
public class Entry {
	private String key;
	private int counter;

	public Entry(String _key){
		key = _key;
		counter = 1;
	}
	
	public String get_key(){
		return key;
	}
	
	public int get_counter(){
		return counter;
	}
	
	public void counter_inc(){
		counter++;
	}
}
