#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double calc_dif_dist_ida(double dist_hermann, double dist_euclides) {
    double dif_dist_ida = dist_hermann - dist_euclides;
    return dif_dist_ida;
}
double calc_dif_dist_volta(double dist_hermann, double dist_euclides) {
    double dif_dist_volta = dist_hermann - dist_euclides;
    return dif_dist_volta;
}
double calc_dif_dist_total(double dif_dist_ida, double dif_dist_volta) {
    double dif_dist_total = dif_dist_ida + dif_dist_volta;
    return dif_dist_total;
}

int main() {
    int estabelecimentos, coordenada_x[100], coordenada_y[100], terreno[100], i;
    double dist_euclides, dist_hermann,  dif_dist_ida = 0, dif_dist_volta = 0, dif_dist_total;
    scanf("%d", &estabelecimentos);
    for(i = 0; i < estabelecimentos; i++) {
        scanf("%d %d %d", &coordenada_x[i], &coordenada_y[i], &terreno[i]);
        if(terreno[i] < -1 || terreno[i] > 1) {
            printf("Falha no processamento dos dados.\n");
            exit(0);
        }
    }

    double aux = 0, aux1 = 0; // variaveis auxiliares que incrementarao a diferenca da distancia de ida
    int baldio = 0, residencial = 0, parque = 0;

    if(estabelecimentos > 0) {
        for (i = 0; i < estabelecimentos -1; i++) { //  calculo da diferenca da distancia do caminho de ida passando pelos estabelecimentos
                if (terreno[i] == -1)  // distancia percorrida pelos dois eh igual
                    baldio++;
                else if (terreno[i] == 0)  // distancia percorrida pelos dois eh igual
                    residencial++;
                else if (terreno[i] == 1) {  // unico terreno em que a distancia percorrida por cada um eh diferente
                    dist_euclides = sqrt(pow(coordenada_x[i + 1] - coordenada_x[i], 2) +pow(coordenada_y[i + 1] - coordenada_y[i], 2));
                    dist_hermann =abs(coordenada_x[i + 1] - coordenada_x[i]) + abs(coordenada_y[i + 1] - coordenada_y[i]);
                    dif_dist_ida = (aux1 - aux) + calc_dif_dist_ida(dist_hermann, dist_euclides);
                    aux += dist_euclides;
                    aux1 += dist_hermann;
                    parque++;
                }
        }
            // calculo da diferenca da distancia do caminho da volta direto para o ponto de partida inicial

            if (terreno[i] == -1) {
                dist_euclides = sqrt(pow(coordenada_x[i] - coordenada_x[0], 2) + pow(coordenada_y[i] - coordenada_y[0], 2));
                dist_hermann = sqrt(pow(coordenada_x[i] - coordenada_x[0], 2) + pow(coordenada_y[i] - coordenada_y[0], 2));
                dif_dist_volta = calc_dif_dist_volta(dist_hermann, dist_euclides);
                baldio++;
            }
            else if (terreno[i] == 0) {
                dist_euclides = abs(coordenada_x[i] - coordenada_x[0]) + abs(coordenada_y[i] - coordenada_y[0]);
                dist_hermann = abs(coordenada_x[i] - coordenada_x[0]) + abs(coordenada_y[i] - coordenada_y[0]);
                dif_dist_volta = calc_dif_dist_volta(dist_hermann, dist_euclides);
                residencial++;
            }
            else if (terreno[i] == 1) {
                dist_euclides = sqrt(pow(coordenada_x[i] - coordenada_x[0], 2) + pow(coordenada_y[i] - coordenada_y[0], 2));
                dist_hermann = abs(coordenada_x[i] - coordenada_x[0]) + abs(coordenada_y[i] - coordenada_y[0]);
                dif_dist_volta = calc_dif_dist_volta(dist_hermann, dist_euclides);
                parque++;
            }

            dif_dist_total = calc_dif_dist_total(dif_dist_ida, dif_dist_volta);
            printf("Ao todo, foi passado por %d terrenos baldios, %d terrenos residenciais e %d parques.\n", baldio,
                   residencial, parque);
            printf("A diferenca total de distancia percorrida foi de %.2lf metros.\n", dif_dist_total);
        }
    else
        printf("Falha no processamento dos dados.\n");

    return 0;
}

