import java.lang.Math;

public class Ex7 {
	public static void main(String[] args) {
		double A, B, C;

		try {
	        System.out.printf("Digite o ponto inicial A do intervalo: \n");
			A = EntradaTeclado.leDouble();
	        System.out.printf("Digite o ponto final B do intervalo: \n");
			B = EntradaTeclado.leDouble();

			} catch (Exception e) {
			 System.out.println("O número digitado não é valido.\n");
			 return;
			}
		
		int n_iteracoes = 0;
		double erro = 0.0000001;
		C = (A + B) / 2;
		
		if ((f(A) * f(B)) < 0) {
			while (Math.abs((B-A)/2) >= erro) {
				n_iteracoes++;
				C = (A + B) / 2;
				if (f(C) == 0) {
			        System.out.printf("A raíz encontrada no intervalo é: %f.	\n", C);
			        break;
				} else {
					if (f(A) * f(C) < 0) {
						B = C;
					} else {
						A = C;
					}
				 }
			}
	        System.out.printf("A raíz encontrada no intervalo é: %f.\n", C);
		} else {
	        System.out.printf("A raíz não foi encontrada nesse intervalo.\n");
		}
        System.out.printf("O número de iterações necessárias foi: %d.\n", n_iteracoes);

	}
	
	public static double f(double x){
		return Math.pow(x, 3)- Math.pow(x, 2) - 13*x + 8;
	}
}


