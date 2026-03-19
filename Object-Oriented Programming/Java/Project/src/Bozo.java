import java.io.IOException;

public class Bozo {

	public static void main(String[] args) throws IOException {
		RolaDados dados = new RolaDados(5);
		Placar placar = new Placar();
		String enter;
				
		for(int i = 0; i < 10; i++) {
			System.out.println("Digite ENTER para começar a rodada");
			enter = EntradaTeclado.leString();
			System.out.println("Rodada " + (i+1) + "\n");

			if(enter.equals("")) {
				dados.rolar();
				System.out.println(dados.toString());
				
				String dados_pra_rolar;
				String[] num_dados_rol = new String[5];
				int[] rolar_dados = new int[5];
				
				for(int k = 0; k < 2; k++) {
					System.out.println("Digite os dados a serem rolados novamente caso queira, separados por espaço");

					dados_pra_rolar = EntradaTeclado.leString();
					if(!dados_pra_rolar.equals("")) {
						num_dados_rol = dados_pra_rolar.split(" ");
						
						for(int j = 0; j < num_dados_rol.length ; j++) {
							rolar_dados[j] = Integer.parseInt(num_dados_rol[j]);
						}
						dados.rolar(dados_pra_rolar);
						System.out.println(dados.toString());

					} else {
						 break;
					}
				}
				
				int[] valor_dados = new int[5];
				for(int l = 0; l < 5; l++) {
					valor_dados[l] = dados.dados[l].lado;
				}
				System.out.println("\n" + placar.toString() + "\n");
				System.out.println("Qual posição do placar deseja ocupar?");
				int posicao = EntradaTeclado.leInt();
				placar.add(posicao, valor_dados);
				System.out.println("\n" + placar.toString() + "\n");
			}	
		}
		System.out.println("\n" + "Fim de jogo! Pontos obtidos:");
		System.out.println(placar.getScore());
	}
}
