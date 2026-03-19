
public class Ex4 {

	public static void main(String[] args) throws Exception {
		System.out.printf("Digite um inteiro: ");
		int num = EntradaTeclado.leInt();
		// variavel space para controlar quantos 
		//espacos em branco tera em cada linha e
		// tmp como variavel temporaria de controle
		int space = 0, tmp = 0; 
		
		for(int i = num; i > 0; i--) {
			for(int j = i; j > 0; j--) {
				// se houver espacos em branco
				// para serem colocados
				if (space != 0) { 
					// enquanto tmp nao se igualar a 
					// qtd de espacos necessarios
					while (tmp < space) {
						System.out.printf(" ");
						tmp++;
					}
				}
				System.out.printf("*");
			}
			space++;
			tmp = 0;
			System.out.printf("\n");
		}
	}
}
