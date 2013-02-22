/**
 * @author vkaliteevskiy
 * Calc
 * (c)2012
 */

import java.util.ArrayList;
import java.util.List;

public class HashTable<type> {
	private List<List<Entry<type>>> table = new ArrayList<List<Entry<type>>>();
	private int TableSize;
	
	public HashTable(int size){
		TableSize = size;
		for (int i = 0; i < size; i++){
			table.add(new ArrayList<Entry<type>>());
		}
	}
	//
	public int HashFunction(String s){
        long hash = 5381;
        int len = s.length();
        for(int i = 0; i < len; i++) {
            hash = ((hash << 5) + hash) + s.charAt(i);
        }
        
        return Integer.parseInt(Long.toString(Math.abs(hash % TableSize)));
	}
	
	public void add(String s, type _t){
		if (s != null){ 
			int key = HashFunction(s);
			if (table.get(key).isEmpty()){
				table.get(key).add(new Entry<type>(s, _t));
			} else {
				for(Entry<type> entry : table.get(key)){
					if (s.equals(entry.get_key())){
						entry.set_data(_t);
						return;
					}
					
				}
				table.get(key).add(new Entry<type>(s, _t));
			}
		}
	}
	
	public type find(String s){
		int key = HashFunction(s);
		if (table.get(key).isEmpty()) {
			return null;
		} else {
			for (Entry<type> entry : table.get(key)){
				if (s.equals(entry.get_key())){
					return entry.get_data();
				}
			}
		}
		return null;
	}

	public void delete(String s){
	       if (s != null){
			int key = HashFunction(s);
			if (table.get(key).isEmpty()) return;
			for (Entry<type> entry : table.get(key)){
				if (s.equals(entry.get_key())){
					int index = (table.get(key).indexOf(entry));
					table.get(key).remove(index);
				}
			}
			return;
		}
	}
	
	  public boolean isInTable(String s){
	       if (s != null){
	           int key = HashFunction(s);
	           if(table.get(key).isEmpty()){
	               return false;
	           } else {
	              List<Entry<type>> list = table.get(key); 
	              for(Entry<type> entry:list){
	                  if (s.equals(entry.get_key())) {
	                        return true;
	                  }
	              }
	              return false;
	           }
	       }
	       return false;
	    }	
	
	public void results(){
		int max = 0, min = 0;
		int i = 0;
		int word_count = 0;
		if (!table.isEmpty()){
			while (table.get(i).isEmpty()){
				i++;
			}
			min = table.get(i).size();
			max = table.get(i).size();
		}
        for(List<Entry<type>> list : table)
        {
        	int tmp = list.size();
        	word_count += tmp;
           // wordsNumb.add(n);
            if (tmp > max)
            {
                max = tmp;
            }
            if (tmp < min)
            {
                min = tmp;
            }
            tmp = 0;
        }
        System.out.print("min = " + min + "\n");
        System.out.print("max = " + max + "\n");
        System.out.print("Количество слов: = " + word_count + "\n");
        for(List<Entry<type>> list : table) for(Entry<type> entry : list) System.out.print("word, count = " + entry.get_key() + "," + entry.get_data() + "\n"); 

        
	}
	
}
