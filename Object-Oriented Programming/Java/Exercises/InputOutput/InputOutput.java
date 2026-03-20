import java.io.IOException;

public class InputOutput {

	public static void main(String[] args) throws Exception  {
		System.out.printf("Digite um inteiro: ");
		int k = EntradaTeclado.leInt();
		System.out.printf("Numero lido: %d\n", k);
	}

}
