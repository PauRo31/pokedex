#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "funcions.h"

int carregar_centre(pokedexcentre_t **pokedexcentre)
{
    FILE *fit;
    int num_poke = -1;
    fit = fopen("Kalos_Centro.txt", "r");
    if (fit != NULL)
    {
        fscanf(fit, "%d\n", &num_poke);
        *pokedexcentre = malloc(num_poke * sizeof(pokedexcentre_t));
        if ((*pokedexcentre) != NULL)
        {
            for (int i = 0; i < num_poke; i++)
            {
                fscanf(fit, "%d\n %d %d %s %s %s %d\n", &(((*pokedexcentre)[i]).id), &(((*pokedexcentre)[i]).fase),
                       (*pokedexcentre)[i].nom, (*pokedexcentre)[i].tipo1, (*pokedexcentre)[i].tipo2, &(((*pokedexcentre)[i]).fase));
            }
            fclose(fit);
        }
        else
            num_poke = -1;
    }
    return num_poke;
}

/*int carregar_costa(pokedexcosta_t **pokedexcosta)
{
    FILE *fit;
    int num_poke = -1;
    fit = fopen("Kalos_Costa.txt", "r");
    if (fit != NULL)
    {
        fscanf(fit, "%d\n", &num_poke);
        *pokedexcosta = malloc(num_poke * sizeof(pokedexcosta_t));
        if ((*pokedexcosta) != NULL)
        {
            for (int i = 0; i < num_poke; i++)
            {
                fscanf(fit, "%d\n %d %d %s %s %s %d\n", &(((*pokedexcosta)[i]).id), &(((*pokedexcosta)[i]).fase),
                       (*pokedexcosta)[i].nom, (*pokedexcosta)[i].tipo1, (*pokedexcosta)[i].tipo2, &(((*pokedexcosta)[i]).fase));
            }
            fclose(fit);
        }
        else
            num_poke = -1;
    }
    return num_poke;
}

int carregar_muntanya(pokedexmuntanya_t **pokedexmuntanya)
{
    FILE *fit;
    int num_poke = -1;
    fit = fopen("Kalos_Montaña.txt", "r");
    if (fit != NULL)
    {
        fscanf(fit, "%d\n", &num_poke);
        *pokedexmuntanya = malloc(num_poke * sizeof(pokedexmuntanya_t));
        if ((*pokedexmuntanya) != NULL)
        {
            for (int i = 0; i < num_poke; i++)
            {
                fscanf(fit, "%d\n %d %d %s %s %s %d\n", &(((*pokedexmuntanya)[i]).id), &(((*pokedexmuntanya)[i]).fase),
                       (*pokedexmuntanya)[i].nom, (*pokedexmuntanya)[i].tipo1, (*pokedexmuntanya)[i].tipo2, &(((*pokedexmuntanya)[i]).fase));
            }
            fclose(fit);
        }
        else
            num_poke = -1;
    }
    return num_poke;
}

void mostra_dexcen(pokedexcentre_t *pokedexcentre, int n)
{
    sprintf("Numero de la pokedex: %d\n", pokedexcentre[n].id);
    sprintf("Fase: %d\n", pokedexcentre[n].fase);
    sprintf("Nom del Pokemon: %s\n", pokedexcentre[n].nom);
    sprintf("Tipo Primari: %s\n", pokedexcentre[n].tipo1);
    sprintf("Tipo Secundari: %s\n", pokedexcentre[n].tipo2);
}

void mostra_dexcost(pokedexcosta_t *pokedexcosta, int n)
{
    sprintf("Numero de la pokedex: %d\n", pokedexcosta[n].id);
    sprintf("Fase: %d\n", pokedexcosta[n].fase);
    sprintf("Nom del Pokemon: %s\n", pokedexcosta[n].nom);
    sprintf("Tipo Primari: %s\n", pokedexcosta[n].tipo1);
    sprintf("Tipo Secundari: %s\n", pokedexcosta[n].tipo2);
}

void mostra_dexmun(pokedexmuntanya_t *pokedexmuntanya, int n)
{
    sprintf("Numero de la pokedex: %d\n", pokedexmuntanya[n].id);
    sprintf("Fase: %d\n", pokedexmuntanya[n].fase);
    sprintf("Nom del Pokemon: %s\n", pokedexmuntanya[n].nom);
    sprintf("Tipo Primari: %s\n", pokedexmuntanya[n].tipo1);
    sprintf("Tipo Secundari: %s\n", pokedexmuntanya[n].tipo2);
}

bool comprova_evoluciocen(pokedexcentre_t *pokedexcentre, int n)
{
    bool evo = false;
    if (pokedexcentre[n].fase < pokedexcentre[n + 1].fase) // n es un pokemon basic
    {
        evo = true;
    }
    return evo;
}

int fases_repes_cen(pokedexcentre_t *pokedexcentre, int n)
{
    int repe = 0;
    if (pokedexcentre[n].fases_repes == 1)
    {
        repe = 1;
    }
    else if (pokedexcentre[n].fases_repes == 2)
    {
        repe = 2;
    }
    return repe;
}

bool comprova_evoluciocost(pokedexcosta_t *pokedexcosta, int n)
{
    bool evo = false;
    if (pokedexcosta[n].fase < pokedexcosta[n + 1].fase) // n es un pokemon basic
    {
        evo = true;
    }
    return evo;
}

void mostra_eeveelutions(pokedexcosta_t *pokedexcosta, int n)
{
    for (int i = n + 1; i < 19; i++)
    {
        printf("Numero de la pokedex: %d\n", pokedexcosta[n].id);
        printf("Fase: %d\n", pokedexcosta[n].fase);
        printf("Nom del Pokemon: %s\n", pokedexcosta[n].nom);
        printf("Tipo Primari: %s\n", pokedexcosta[n].tipo1);
        printf("Tipo Secundari: %s\n", pokedexcosta[n].tipo2);
    }
}

int fases_repes_cost(pokedexcosta_t *pokedexcosta, int n)
{
    int repe = 0;
    if (pokedexcosta[n].fases_repes == 1)
    {
        repe = 1;
    }
    else if (pokedexcosta[n].fases_repes == 2)
    {
        repe = 2;
    }
    return repe;
}

bool comprova_evoluciomun(pokedexmuntanya_t *pokedexmuntanya, int n)
{
    bool evo = false;
    if (pokedexmuntanya[n].fase < pokedexmuntanya[n + 1].fase) // n es un pokemon basic
    {
        evo = true;
    }
    return evo;
}

int fases_repes_mun(pokedexmuntanya_t *pokedexmuntanya, int n)
{
    int repe = 0;
    if (pokedexmuntanya[n].fases_repes == 1)
    {
        repe = 1;
    }
    else if (pokedexmuntanya[n].fases_repes == 2)
    {
        repe = 2;
    }
    return repe;
}*/
