
public class Placar extends java.lang.Object {
	int[] placar = new int[10];
	
	public void add(int posicao, int[] dados) throws java.lang.IllegalArgumentException {
		int x1 = 0, x2 = 0;
		int count = 0, count2 = 0;
		
		if(placar[posicao - 1] == 0 && posicao > 0 && posicao <= 10) {
			if(posicao >= 1 && posicao <= 6) {
				for(int i = 0; i < 5; i++) {
					if(dados[i] == posicao) {
						count++;
					}
				}
				placar[posicao - 1] = posicao * count;
			} else {
				switch(posicao) {
				case 7:
					x1 = dados[0];
					for(int i = 1; i < 5; i++) {
						if(dados[i] != x1) {
							x2 = dados[i];
							break;
						} 
					}
					
					for(int i = 0; i < 5; i++) {
						if(dados[i] == x1) {
							count++;
						} else if(dados[i] == x2) {
							count2++;
						} else {
							placar[posicao - 1] = 0;
							break;
						}
					}
					
					if((count == 2 && count2 == 3) || (count == 3 && count2 == 2) || count == 5) {
						placar[posicao - 1] = 15;
					} else {
						placar[posicao - 1] = 0;
					}
					break;
					
				case 8:
					int[] seq = {1, 2, 3, 4, 5, 6};
					
					for(int i = 0; i < 5; i++) {
						for(int j = 0; j < 6; j++) {
							if(dados[i] == seq[j]) {
								seq[j] = 0;
								count++;
								break;
							}
						}
					}
					
					if((count == 5 && seq[0] == 1) || (count == 5 && seq[5] == 6)) {
						placar[posicao - 1] = 20;
					} else {
						placar[posicao - 1] = 0;
					}
					break;
					
				case 9:
					x1 = dados[0];										
					for(int i = 1; i < 5; i++) {
						if(dados[i] != x1) {
							x2 = dados[i];
							break;
						}
					}
					for(int i = 0; i < 5; i++) {
						if(dados[i] == x1) {
							count++;
						} else if(dados[i] == x2) {
							count2++;
						} else {
							placar[posicao - 1] = 0;
							break;
						}
					}
					
					if(count == 4 || count2 == 4) {
						placar[posicao - 1] = 30;
					}
					break;

				case 10:
					x1 = dados[0];
					for(int i = 0; i < 5; i++) {
						if(dados[i] == x1) {
							count++;
						} else {
							placar[posicao - 1] = 0;
							break;
						}
					}
					
					if(count == 5) {
						placar[posicao - 1] = 40;
					}
					break;
				}
			}
		} else {
	         throw new java.lang.IllegalArgumentException("Posição inválida.\n");
		}
	}
	
	public int getScore() {
		int score = 0;
		for(int i = 0; i < 10; i++) {
			if(placar[i] != 0) {
				score += placar[i];
			}
		}
		return score;
	}
	
	public String toString() {
	    String board =  "       |          |       \n" + 
						"--------------------------\n" + 
						"       |          |       \n" + 
						"--------------------------\n" + 
						"       |          |       \n" + 
						"--------------------------\n" + 
						"       |         |\n" + 
						"       +----------+       ";
		    
		String temp_array[] = new String[1];
		
		temp_array = board.split("|");
			
		for(int i = 0; i < 207; i++) {
			switch(i) {
				case 3:
					if(placar[0] == 0) {
						temp_array[i - 1] = "(";
						temp_array[i] = "1";
						temp_array[i + 1] = ")";
					} else {
						temp_array[i] = Integer.toString(placar[0]);
					}
					break;
					
				case 12:
					if(placar[6] == 0) {
						temp_array[i - 1] = "(";
						temp_array[i] = "7";
						temp_array[i + 1] = ")";
					} else {
						temp_array[i] = Integer.toString(placar[6]);
					}
					break;
					
				case 22:
					if(placar[3] == 0) {
						temp_array[i - 1] = "(";
						temp_array[i] = "4";
						temp_array[i + 1] = ")";
					} else {
						temp_array[i] = Integer.toString(placar[3]);
					}
					break;
					
				case 57:
					if(placar[1] == 0) {
						temp_array[i - 1] = "(";
						temp_array[i] = "2";
						temp_array[i + 1] = ")";
					} else {
						temp_array[i] = Integer.toString(placar[1]);
					}
					break;
				
				case 66:
					if(placar[7] == 0) {
						temp_array[i - 1] = "(";
						temp_array[i] = "8";
						temp_array[i + 1] = ")";
					} else {
						temp_array[i] = Integer.toString(placar[7]);
					}
					break;
					
				case 76:
					if(placar[4] == 0) {
						temp_array[i - 1] = "(";
						temp_array[i] = "5";
						temp_array[i + 1] = ")";
					} else {
						temp_array[i] = Integer.toString(placar[4]);
					}
					break;
					
				case 111:
					if(placar[2] == 0) {
						temp_array[i - 1] = "(";
						temp_array[i] = "3";
						temp_array[i + 1] = ")";
					} else {
						temp_array[i] = Integer.toString(placar[2]);
					}
					break;
					
				case 120:
					if(placar[8] == 0) {
						temp_array[i - 1] = "(";
						temp_array[i] = "9";
						temp_array[i + 1] = ")";
					} else {
						temp_array[i] = Integer.toString(placar[8]);
					}
					break;
					
				case 130:
					if(placar[5] == 0) {
						temp_array[i - 1] = "(";
						temp_array[i] = "6";
						temp_array[i + 1] = ")";
					} else {
						temp_array[i] = Integer.toString(placar[5]);
					}
					break;
					
				case 174:
					if(placar[9] == 0) {
						temp_array[i - 1] = "(";
						temp_array[i] = "10";
						temp_array[i + 1] = ")";
					} else {
						temp_array[i] = Integer.toString(placar[9]);
					}
					break;
			}	
		}
		String b = new String();
		for(int i = 0; i < 207; i++) {
			b += temp_array[i];
		}
		return b;
	}
}
