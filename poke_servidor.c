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
        if (num_pokemon <= 0 || dex == NULL)
        {
            printf("Error");
            return 1;
        }
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
                if (n < 0 || n > num_pokemon)
                {
                    printf("index fora de rang.\n");
                }
                else
                {
                    printf("Volen el pokemon %d\n", n);

                if (comprova_evolucio(dex, n))
                {
                    
                    if (n == 133)
                    {
                        sprintf(paquet, "Numero de la pokedex: %d Fase: %d Nom del Pokemon: %s Tipo 1: %s Tipo 2: %s\n
                        Evolucions:\n
                        Numero de la Pokédex: %d Fase: %d Nom del Pokémon: %s Tipo 1: %s Tipo 2: %s\n
                        Numero de la Pokédex: %d Fase: %d Nom del Pokémon: %s Tipo 1: %s Tipo 2: %s\n
                        Numero de la Pokédex: %d Fase: %d Nom del Pokémon: %s Tipo 1: %s Tipo 2: %s\n",
                        dex[n - 1].id, dex[n - 1].fase, dex[n - 1].nom, dex[n - 1].tipo1, dex[n - 1].tipo2, 
                        dex[n].id, dex[n].fase, dex[n].nom, dex[n].tipo1, dex[n].tipo2, 
                        dex[n + 1].id, dex[n + 1].fase, dex[n + 1].nom, dex[n + 1].tipo1, dex[n + 1].tipo2,
                        dex[n + 2].id, dex[n + 2].fase, dex[n + 2].nom, dex[n + 2].tipo1, dex[n + 2].tipo2);
                    }
                    else
                    {
                        sprintf(paquet, "Numero de la pokedex: %d Fase: %d Nom del Pokemon: %s Tipo 1: %s Tipo 2: %s\n
                        Evolucio:\n
                        Numero de la Pokédex: %d Fase: %d Nom del Pokémon: %s Tipo 1: %s Tipo 2: %s\n", 
                        dex[n - 1].id, dex[n - 1].fase, dex[n - 1].nom, dex[n - 1].tipo1, dex[n - 1].tipo2, 
                        dex[n].id, dex[n].fase, dex[n].nom, dex[n].tipo1, dex[n].tipo2);
                    }

                }
                else
                {
                    sprintf(paquet, "Numero de la pokedex: %d Fase: %d Nom del Pokemon: %s Tipo 1: %s Tipo 2: %s\n",
                            dex[n - 1].id, dex[n - 1].fase, dex[n - 1].nom, dex[n - 1].tipo1, dex[n - 1].tipo2);
                    printf(paquet);
                }
                }
                /* Enviem el paquet a l'adreça i port on està esperant el client */
                sendto(s, paquet, sizeof(paquet), 0, (struct sockaddr *)&contacte_client, contacte_client_mida);
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
    allibera_memoria(&dex);
    return 0;
}