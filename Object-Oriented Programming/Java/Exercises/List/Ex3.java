
public class Ex3 {

	public static void main(String[] args) throws Exception {
		System.out.printf("Digite um numero inteiro: ");
		int num = EntradaTeclado.leInt();
		
		for(int i = num; i > 0; i--) {
			for(int j = i; j > 0; j--) {
				System.out.printf("*");
			}
			System.out.printf("\n");
		}
	}

}
