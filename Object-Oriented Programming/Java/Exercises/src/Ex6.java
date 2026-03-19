
public class Ex6 {

	public static void main(String[] args) {
		
		int tmp = 0;
		double maior = 0, menor = 0;
		double x = -1.0;
		try {
			while (x != 0) {
				x = EntradaTeclado.leDouble();
				
				if (tmp == 0) {
					maior = x;
					menor = x;
				}
				
				if (x > maior && x != 0) {
					maior = x;
					
				} else if (x < menor && x != 0) {
					menor = x;
				}
				tmp++;
			}
			} catch (Exception e) {
			 System.out.println("O valor digitado não é valido.\n");
			 return;
			}
		
		 System.out.printf("O maior número digitado é %f e o menor é %f .\n", maior, menor);

	}

}
