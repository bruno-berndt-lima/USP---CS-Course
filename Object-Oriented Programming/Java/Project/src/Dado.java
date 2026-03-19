
public class Dado extends java.lang.Object {
	public int n_lados;
	public int lado;
	static Random x = new Random();
	
	public Dado() {
		this.n_lados = 6;
	}
	
	public Dado(int n) {
		this.n_lados = n;
	}
	
	int get_Lado() {
		return this.lado;
	}
	
	int rolar() {
		lado = x.getIntRand(n_lados) + 1;
		return lado;
	}

@Override	
	public String toString() {
		if (n_lados == 6) {
			switch (lado) {
				case 1:
				    return  "+-----+    \n" + 
				    		"|     |    \n" + 
				    		"|  *  |    \n" + 
				    		"|     |    \n" + 
				    		"+-----+ ";
				case 2:
					return  "+-----+    \n" + 
							"|*    |    \n" + 
							"|     |    \n" + 
							"|    *|    \n" + 
							"+-----+ ";		
			    
				case 3:
					return  "+-----+    \n" + 
							"|*    |    \n" + 
							"|  *  |    \n" + 
							"|    *|    \n" + 
							"+-----+ ";		
				
				case 4:
					return  "+-----+    \n" + 
							"|*   *|    \n" + 
							"|     |    \n" + 
							"|*   *|    \n" + 
							"+-----+ ";	
				
				case 5:
					return  "+-----+    \n" + 
							"|*   *|    \n" + 
							"|  *  |    \n" + 
							"|*   *|    \n" + 
							"+-----+ ";	
				
				case 6:
					return  "+-----+    \n" + 
							"|*   *|    \n" + 
							"|*   *|    \n" + 
							"|*   *|    \n" + 
							"+-----+ ";		
				default:
					return "Erro";
			}
		} else {
			return "Não é possível printar a face do dado";
		}
	}
}
