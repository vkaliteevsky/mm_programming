import java.util.ArrayList;
import java.util.List;

public class HashTable {
	private List<List<Entry>> table = new ArrayList<List<Entry>>();
	private int TableSize;
	
	public HashTable(int size){
		TableSize = size;
		for (int i = 0; i < size; i++){
			table.add(new ArrayList<Entry>());
		}
	}
	
	public int HashFunction(String s){
        long hash = 5381;
        int len = s.length();
        for(int i = 0; i < len; i++) {
            hash = ((hash << 5) + hash) + s.charAt(i);
        }
        
        return Integer.parseInt(Long.toString(Math.abs(hash % TableSize)));
	}
	
	public void add(String s){
		if (s != null){ 
			int key = HashFunction(s);
			if (table.get(key).isEmpty()){
				table.get(key).add(new Entry(s));
			} else {
				for(Entry entry : table.get(key)){
					if (s.equals(entry.get_key())){
						entry.counter_inc();
					}
					return;
				}
				table.get(key).add(new Entry(s));
			}
		}
	}
	
	public int find(String s){
		int key = HashFunction(s);
		if (table.get(key).isEmpty()) return 0;
		for (Entry entry : table.get(key)){
			if (s.equals(entry.get_key())){
				return entry.get_counter();
			}
		}
		return 0;
	}

	public void delete(String s){
		int key = HashFunction(s);
		if (table.get(key).isEmpty()) return;
		for (Entry entry : table.get(key)){
			if (s.equals(entry.get_key())){
				int index = (table.get(key).indexOf(entry));
				table.get(key).remove(index);
			}
		}
		return;
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
        for(List<Entry> list : table)
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
        for(List<Entry> list : table)
        {
            for(Entry entry : list)
            {
                System.out.print("word, count = " + entry.get_key() + "," + entry.get_counter() + "\n"); 
            }
        }
	}
}
