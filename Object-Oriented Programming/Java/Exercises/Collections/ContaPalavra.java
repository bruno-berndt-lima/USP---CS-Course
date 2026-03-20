import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import java.util.TreeMap;


public class ContaPalavra {
	
	private String fileName;


	public ContaPalavra(String fileName) throws IOException {
		this.fileName = fileName;
	}
	
	public static Map<String, Integer> createMap(List<String> words) {
		int i = 0;
		Map<String, Integer> map = new TreeMap<String, Integer>();
		while(i < words.size()) {	
			int occurrences = Collections.frequency(words, words.get(i));
			map.put(words.get(i), occurrences);
			i++;			
		}
		return map;
	}
	
	public static void showMap(Map<String, Integer> map) {
		for (Map.Entry<String, Integer> entry : map.entrySet()) {
		    System.out.println(entry.getKey()+": "+entry.getValue());
		}
	}
	
	
	
	public static void main(String[] args) throws IOException {
		String fileName;
		List<String> wordsList = new ArrayList<String>();
		
		System.out.printf("Digite o nome do arquivo:\n> ");
		fileName = EntradaTeclado.leString();

		ContaPalavra counter = new ContaPalavra(fileName);
		
		File f = new File("/home/bruno/ssc103 - POO - Java/Collections/src/" + counter.fileName);
		Scanner sc = new Scanner(f);
		while (sc.hasNext()) {
			wordsList.add(sc.next());
        }
        sc.close();
        
        Map<String, Integer> map = createMap(wordsList);

        showMap(map);
		
	}
}
