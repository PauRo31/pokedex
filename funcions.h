#ifndef funcions_h
#define funcions_h
#include <stdbool.h>
#include <string.h>
typedef struct 
{
    int id;
    int fase;
    char nom[25];
    char tipo1[25];
    char tipo2[25];
    int fases_repes;
}pokedex_t;

int carregar(pokedex_t **pokedex);

void mostra_dex(pokedex_t *pokedex, int n);

bool comprova_evolucio(pokedex_t *pokedex, int n);

#endif