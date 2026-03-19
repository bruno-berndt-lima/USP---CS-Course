
public class Ex1 {

	public static void main(String[] args) throws Exception {
		System.out.printf("Digite um double para se calcular a raiz: ");
		double x = EntradaTeclado.leDouble();
		
		System.out.printf("Digite um double como chute inicial: ");
		double x0 = EntradaTeclado.leDouble();
		
		double xi = x0, prev_xi = x0;
		
		do {
			prev_xi = xi;
			xi = (prev_xi + (x/prev_xi))/2;
	
		} while(xi - prev_xi >= 0.00000001);
			
		System.out.printf("A raiz quadrada de %f é: %f\n", x, xi);
	}
}
