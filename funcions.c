#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "funcions.h"

int carregar(pokedex_t **pokedex)
{
    FILE *fit;
    int num_poke = -1;
    fit = fopen("pokedex_kanto.txt", "r");
    if (fit != NULL)
    {
        fscanf(fit, "%d\n", &num_poke);
        *pokedex = malloc(num_poke * sizeof(pokedex_t));
        if ((*pokedex) != NULL)
        {
            for (int i = 0; i < num_poke; i++)
            {
                fscanf(fit, "%d\n %d %d %s %s %s %d\n", &(((*pokedex)[i]).id), &(((*pokedex)[i]).fase),
                       (*pokedex)[i].nom, (*pokedex)[i].tipo1, (*pokedex)[i].tipo2, &(((*pokedex)[i]).fases_repes));
            }
            fclose(fit);
        }
        else
            num_poke = -1;
    }
    return num_poke;
}

/*void mostra_dex(pokedex_t *pokedex, int n)
{
    printf("Numero de la pokedex: %d\n", pokedex[n].id);
    printf("Fase: %d\n", pokedex[n].fase);
    printf("Nom del Pokemon: %s\n", pokedex[n].nom);
    printf("Tipo Primari: %s\n", pokedex[n].tipo1);
    printf("Tipo Secundari: %s\n", pokedex[n].tipo2);
}*/

bool comprova_evolucio(pokedex_t *pokedex, int n)
{
    bool evo = false;
    if (pokedex[n].fase < pokedex[n + 1].fase) // n es un pokemon basic
    {
        evo = true;
    }
    return evo;
}

/*int fases_repes(pokedex_t *pokedex, int n)
{
    int repe = 0;
    if (pokedex[n].fases_repes == 1)
    {
        repe = 1;
    }
    return repe;
}*/

void allibera_memoria(pokedex_t **pokedex)
{
    free(pokedex);
}

/*void mostra_eeveelutions(pokedex_t *pokedex, int n)
{
    for (int i = n + 1; i < 19; i++)
    {
        printf("Numero de la pokedex: %d\n", pokedex[n].id);
        printf("Fase: %d\n", pokedex[n].fase);
        printf("Nom del Pokemon: %s\n", pokedex[n].nom);
        printf("Tipo Primari: %s\n", pokedex[n].tipo1);
        printf("Tipo Secundari: %s\n", pokedex[n].tipo2);
    }
}*/