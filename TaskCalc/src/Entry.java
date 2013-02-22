/**
 * @author vkaliteevskiy
 * Calc
 * (c)2012
 */


public class Entry<type> {
	private String key;
	private type data;

	public Entry(String _key, type _data){
		key = _key;
		data = _data;
	}
	
	public String get_key(){
		return key;
	}
	
	public type get_data(){
		return data;
	}
	
	public void set_data(type _data){
		data = _data;
	}
}
