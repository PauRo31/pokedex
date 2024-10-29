#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcions.h"
/* Inclusio de fitxers .h per als sockets */
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MIDA_PAQUET 50

int main(int argc, char **argv)
{
    pokedexcentre_t *dexcen;
    pokedexcosta_t *dexcost;
    pokedexmuntanya_t *dexmun;
    if (argc == 2)
    {
        int num_poke_cen = carregar_centre(&dexcen);
        /*int num_poke_cost = carregar_costa(&pokedexcosta);
        int num_poke_mun = carregar_muntanya(&pokedexmuntanya);*/
        int s;                                                    /* El socket */
        struct sockaddr_in socket_servidor;                       /* Dades del socket on escolta el servidor */
        struct sockaddr_in contacte_client;                       /* Adreça i port des d'on el client envia el paquet */
        socklen_t contacte_client_mida = sizeof(contacte_client); /* Longitud de les dades adreça i port */

        char paquet[MIDA_PAQUET]; /* Per posar les dades a enviar/rebre */

        /* Volem socket d'internet i no orientat a la connexio */
        s = socket(AF_INET, SOCK_DGRAM, 0);

        /* Posem les dades del socket del servidor */
        socket_servidor.sin_family = AF_INET;            /* Socket a Internet */
        socket_servidor.sin_addr.s_addr = INADDR_ANY;    /* Qualsevol NIC */
        socket_servidor.sin_port = htons(atoi(argv[1])); /* Port on estarà escoltant el servidor */

        /* Enllacem el socket */
        int resultat_bind;
        resultat_bind = bind(s, (struct sockaddr *)&socket_servidor, sizeof(socket_servidor));

        if (resultat_bind < 0)
        {
            printf("No s'ha pogut enllaçar el socket\n");
        }
        else
        {
            /* Servidor operatiu! */
            printf("Servidor operatiu al port %d!\n", atoi(argv[1]));

            int n, pokedex; /* Pel desar el número (protocol) */

            while (1)
            {
                printf("Esperant petició d'algun client...\n");
                /* Quan es rep un paquet, a adr_client s'hi anota la IP i port des d'on s'envia */
                recvfrom(s, paquet, MIDA_PAQUET, 0, (struct sockaddr *)&contacte_client, &contacte_client_mida);
                printf("Paquet rebut!\n");

                /* Tractar la petició... */
                sscanf(paquet, "%d", &n);
                do
                {
                    sscanf(paquet, "%d", &pokedex);
                    do
                    {
                        sscanf(paquet, "%d", &n);
                        sprintf(paquet, "La pokedex de muntanya nomes te 151 pokemon");
                    } while (/*(pokedex == 3 && numero > 151) || */n < 1 || n > 153);

                    printf("Volen el pokemon %d de la pokedex de %d\n", n, pokedex);
                    switch (pokedex)
                    {
                    case 1:
                        sprintf(paquet, "Numero de la pokedex: %d Fase: %d Nom del Pokemon: %s Tipo 1: %s Tipo 2: %s\n",  
                        dexcen[n].id, dexcen[n].fase, dexcen[n].nom, dexcen[n].tipo1, dexcen[n].tipo2); 
                        /*if (comprova_evoluciocen(dexcen, numero))
                        {
                            sprintf(paquet, paquet, "Numero de la pokedex: %d Fase: %d Nom del Pokemon: %s Tipo 1: %s Tipo 2: %s\n",  
                        	pokedexcentre[n + 1].id, pokedexcentre[n].fase, pokedexcentre[n].nom, pokedexcentre[n].tipo1, pokedexcentre[n].tipo2);
                        }*/

                        break;
                    /*case 2:
                        if (numero == 77)
                        {
                            sprintf(paquet, mostra_eeveelutions());
                        }

                        sprintf(paquet, mostra_dexcost(dexcost, numero)); // no es pot posar el void aqui
                        if (comprova_evoluciocost(dexcost, numero))
                        {
                            sprintf(paquet, mostra_dexcost(dexcen, numero + 1));
                        }
                        break;
                    case 3:
                        sprintf(paquet, mostra_dexmun(dexmun, numero)); // no es pot posar el void aqui
                        if (comprova_evoluciomun(dexmun, numero))
                        {
                            sprintf(paquet, mostra_dexmun(dexcen, numero + 1));
                        }
                        break;*/
                    }
                } while (n != -1);
                
                /* Enviem el paquet a l'adreça i port on està esperant el client */
                sendto(s, paquet, MIDA_PAQUET, 0, (struct sockaddr *)&contacte_client, contacte_client_mida);
                printf("Càlcul enviat!\n");
            }
        }

        /* Tanquem el socket */
        close(s);
    }
    else
    {
        printf("El nombre de paràmetres no és el correcte!\n");
    }
    return 0;

}
