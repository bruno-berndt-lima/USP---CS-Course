
public class RolaDados extends java.lang.Object {
	public Dado[] dados;
	public int n_dados = 0;

	public RolaDados(int n) {
		n_dados = n;
		dados = new Dado[n];
		for(int i = 0; i < n; i++) {
			dados[i] = new Dado();
		}	
	}
	
	public int[] rolar() {
		int i = 0;
		int[] lados = new int[n_dados];

		for(Dado dado : dados) {
			dado.rolar();
			lados[i] = dado.lado;
			i++;
		}
		
		return lados;
	}
	
	public int[] rolar(boolean[] quais) {
		int[] lados = new int[n_dados];

		for(int i = 0; i < n_dados; i++) {
			if (quais[i] == true) {
				dados[i].rolar();
				lados[i] = dados[i].lado;
			}
		}
		
		return lados;
	}
	
	public int[] rolar(java.lang.String s) {
		int[] lados = new int[n_dados];
		
		String[] temp_array = s.split(" ");
				
		int count = 0;
		while (count < temp_array.length) {
		    int x = Integer.parseInt(temp_array[count]);
		    if (x > 0 && x <= n_dados) {
		    	dados[x - 1].rolar();
		    	lados[x - 1] = dados[x - 1].lado;
		    }
	    	count++;
		}
		
		return lados;
	}
	
	public String toString() {
		String temp_array[][] = new String[n_dados][5];
		String temp = new String();
		
		for(int i = 1; i <= n_dados; i++) {
			System.out.print(i + "\t\t");
		}
		System.out.print("\n");

		
		for(int i = 0; i < n_dados; i++) {
			for(int j = 0; j < 5; j++) {
				temp_array[i] = dados[i].toString().split("\n");
			}
		}
		
		for(int i = 0; i < n_dados; i++) {
			for(int j = 0; j < 5; j++) {
				temp += temp_array[j][i] + "\t";
			}
			temp += "\n";
		}	
  		
		return temp;
	}
}
