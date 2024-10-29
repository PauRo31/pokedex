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
}pokedexcentre_t;

typedef struct 
{
    int id;
    int fase;
    char nom[25];
    char tipo1[25];
    char tipo2[25];
    int fases_repes;
}pokedexcosta_t;

typedef struct 
{
    int id;
    int fase;
    char nom[25];
    char tipo1[25];
    char tipo2[25];
    int fases_repes;
}pokedexmuntanya_t;

extern int carregar_centre(pokedexcentre_t **pokedexcentre);

int carregar_costa(pokedexcosta_t **pokedexcosta);

int carregar_muntanya(pokedexmuntanya_t **pokedexmuntanya);

void mostra_dexcen(pokedexcentre_t *pokedexcentre, int n);

void mostra_dexcost(pokedexcosta_t *pokedexcosta, int n);

void mostra_dexmun(pokedexmuntanya_t *pokedexmuntanya, int n);

bool comprova_evoluciocen(pokedexcentre_t *pokedexcentre, int n);

bool comprova_evoluciocost(pokedexcosta_t *pokedexcosta, int n);

bool comprova_evoluciomun(pokedexmuntanya_t *pokedexmuntanya, int n);

#endif
