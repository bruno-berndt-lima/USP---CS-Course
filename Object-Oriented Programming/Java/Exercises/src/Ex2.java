import java.lang.Math;

public class Ex2 {

	public static void main(String[] args) {
		int a, b, c;
		System.out.printf("Digite os coeficientes a, b, c, respectivamente: ");
		
		// tratamento feito para leitura do imput ser um int
		try {
			a = EntradaTeclado.leInt();
			b = EntradaTeclado.leInt();
			c = EntradaTeclado.leInt();
			
			} catch (Exception e) {
			 System.out.println("O valor que vc digitou não é um número valido");
			 return;
			}
		
		double delta; // delta da equacao do segundo grau
		double x1, x2; // raizes da equacao do segundo grau
		
		delta = Math.pow(b, 2) - 4*a*c;

		if (delta < 0) {
			 System.out.println("A equação não possui raízes reais.\n");
			 return;
		}
		
		x1 = (-b + Math.sqrt(delta))/(2*a);
		x2 = (-b - Math.sqrt(delta))/(2*a);
		
		System.out.printf("As raízes da equação são: %f e %f", x1, x2);

	}
}
