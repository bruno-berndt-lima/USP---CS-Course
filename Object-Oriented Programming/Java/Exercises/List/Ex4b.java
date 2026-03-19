
public class Ex4b {

	public static void main(String[] args) throws Exception {
		System.out.printf("Digite um numero inteiro: ");
		int num;
		
		try {
			num = EntradaTeclado.leInt();
			} catch (Exception e) {
			 System.out.println("O número digitado não é valido.\n");
			 return;
			}

		int smallest_divisor = 1;
		boolean is_prime = true;
		for (int j = 2; j < num; j++) {
		        if (num % j == 0) {
		        	is_prime = false;
		        	smallest_divisor = j;
		        	break;
		        }
		}

		if (!is_prime) {
			 System.out.printf("O número digitado não é primo e seu menor divisor é: %d.\n", smallest_divisor);
		} else {
			 System.out.printf("O número digitado é primo.\n");
		}
	}
}
