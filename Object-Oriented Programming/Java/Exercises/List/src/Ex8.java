import java.lang.Math;

public class Ex8 {

	public static void main(String[] args) {
		double X;
		try {
	        System.out.printf("Digite o chute inicial: \n");
			X = EntradaTeclado.leDouble();
			} catch (Exception e) {
			 System.out.println("O valor digitado não é valido.\n");
			 return;
			}
		
		int n_iteracoes = 0;
		double erro = 0.0000001;
		
		double X0 = 0;
		double A, B;
		
		while (Math.abs(X0 - X) >= erro) {
			X0 = X;
			A = f(X);
			B = f_deriv(X);		
            X = X0 - (A / B);
            n_iteracoes++;
		}
        System.out.printf("A raíz encontrada é: %f.\n", X);
        System.out.printf("O número de iterações necessárias foi: %d.\n", n_iteracoes);

	}
	public static double f(double x){
		return Math.pow(x, 3)- Math.pow(x, 2) - 13*x + 8;
	}	
	
	public static double f_deriv(double x){
		return 3*Math.pow(x, 2)- 2*x - 13;
	}	
}
