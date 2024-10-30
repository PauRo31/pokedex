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
    pokedex_t *dex;
    if (argc == 2)
    {
        int num_pokemon = carregar(&dex);
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

            int n; /* Pel desar el número (protocol) */

            while (1)
            {
                printf("Esperant petició d'algun client...\n");
                /* Quan es rep un paquet, a adr_client s'hi anota la IP i port des d'on s'envia */
                recvfrom(s, paquet, MIDA_PAQUET, 0, (struct sockaddr *)&contacte_client, &contacte_client_mida);
                printf("Paquet rebut!\n");

                /* Tractar la petició... */

                sscanf(paquet, "%d", &n);
                int evolucio_bifurcada = fases_repes(dex);
                    printf("Volen el pokemon %d de \n", n);
                sprintf(paquet, "Numero de la pokedex: %d Fase: %d Nom del Pokemon: %s Tipo 1: %s Tipo 2: %s\n",
                        dex[n].id, dex[n].fase, dex[n].nom, dex[n].tipo1, dex[n].tipo2);
                if (comprova_evoluciocen(dex, num))
                {
                    sprintf("La seva evolucio es:\n");
                    sprintf(paquet, "Numero de la pokedex: %d Fase: %d Nom del Pokemon: %s Tipo 1: %s Tipo 2: %s\n",
                            dex[n + 1].id, dex[n + 1].fase, dex[n + 1].nom, dex[n + 1].tipo1, dex[n + 1].tipo2);
                }
                /*if (evolucio_bifurcada == 1) // comprova si un pokemon te mes de dos evolucions possibles de fase 1
                {
                    sprintf("Aquest pokemon te mes d'una evolucio de la mateixa fase (1):\n");
                    if (numero == 230) //cas especial eevee, pokemon amb 8 evolucions diferents de fase 1
                    {
                        sprintf(paquet, mostra_eeveelutions());
                    }
                    else //numero != 230
                    {
                        
                    }
                    
                }
                else if (evolucio_bifurcada == 2)// comprova si un pokemon te mes de dos evolucions possibles de fase 1
                {
                    sprintf("Aquest pokemon te mes d'una evolucio de la mateixa fase (2):\n");
                }*/

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