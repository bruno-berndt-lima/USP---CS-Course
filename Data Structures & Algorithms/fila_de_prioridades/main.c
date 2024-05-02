// Bruno Berndt Lima - 12542550

#include <stdio.h>
#include <string.h>
#include "fila.h"

typedef struct people {
    char name[20];
    int age;
    int health_condition;
} people_t;

int main() {
    queue_t *q[4];  // uma lista para atender cada prioridade
    people_t p;
    q[0] = create(sizeof(people_t));    // lista de maior prioridade (60+ anos e comorbidade)
    q[1] = create(sizeof(people_t));    // (comorbidade)
    q[2] = create(sizeof(people_t));    // (60+ anos)
    q[3] = create(sizeof(people_t));    // lista de menor prioridade (60- anos s/ comorbidade)

    int n_actions;
    scanf("%d", &n_actions);

    int i = 0;
    char action[10];
    while (i < n_actions) {
        scanf(" %s", action);

        if (strcmp(action, "SAI") == 0) {   // se o comando do imput for "SAI"
            // se a lista de maior prioridade nao estiver vazia,
            // a pessoa eh atendida e consequentemente sai da lista,
            // da mesma forma para as outras prioridades
            if (!is_empty(q[0])) {
                remove_elem(q[0], &p);
                printf("%s %d %d\n", p.name, p.age, p.health_condition);

            }
            else if (!is_empty(q[1])) {
                remove_elem(q[1], &p);
                printf("%s %d %d\n", p.name, p.age, p.health_condition);
            }
            else if (!is_empty(q[2])) {
                remove_elem(q[2], &p);
                printf("%s %d %d\n", p.name, p.age, p.health_condition);

            }
            else if (!is_empty(q[3])) {
                remove_elem(q[3], &p);
                printf("%s %d %d\n", p.name, p.age, p.health_condition);

            }
            else {
                printf("FILA VAZIA\n");
            }
        }
        if (strcmp(action, "ENTRA") == 0) { // se o comando do imput for "ENTRA"

            scanf(" %s", p.name);

            scanf("%d", &p.age);

            scanf("%d", &p.health_condition);

            // se a pessoa lida no input for de maior prioridade, ela eh inserida na lista q[0]
            // e assim para cada tipo de prioridade
            if (p.age >= 60 && p.health_condition == 1) {
                insert_elem(q[0], &p);
            }
            else if (p.age <= 60 && p.health_condition == 1) {
                insert_elem(q[1], &p);
            }
            else if (p.age >= 60 && p.health_condition == 0) {
                insert_elem(q[2], &p);
            }
            else if (p.age <= 60 && p.health_condition == 0) {
                insert_elem(q[3], &p);
            }
        }

        i++;
    }

    return 0;
}
