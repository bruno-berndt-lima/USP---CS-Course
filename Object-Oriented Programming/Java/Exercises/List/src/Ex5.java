public class Ex5 {

	public static void main(String[] args) {
		System.out.printf("Digite um numero inteiro: ");
		int num;
		
		try {
			num = EntradaTeclado.leInt();
			} catch (Exception e) {
			 System.out.println("O número digitado não é valido.\n");
			 return;
			}

		int i, j;
		int previous_prime = -1;
		boolean is_prime = true;
		for (i = num - 1; i > 1; i--) {
			for (j = 2; j < i; j++) {
				if (i % j == 0) {
					is_prime = false;
					break;
				}
				is_prime = true;
			}
			if (is_prime == true) {
				previous_prime = i;
				break;
			}
		}
		
		if (previous_prime != -1) {
			System.out.printf("O primeiro número primo menor que o número informado é: %d.\n", previous_prime);
		} else {
			System.out.printf("Não existe número primo menor que o número informado.\n");
		}
	}
}
