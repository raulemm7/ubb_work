#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#define STRING_SIZE 1024

void* deservire_client(void* arg) {
    int c = *((int*)arg);    // preiau socketul din argument
    free(arg);

    // primesc sirul
    uint16_t nr1;
    recv(c, &nr1, sizeof(uint16_t), MSG_WAITALL);
    nr1 = ntohs(nr1);

    uint16_t* numere1 = (uint16_t*)malloc(sizeof(uint16_t) * nr1);
    recv(c, numere1, sizeof(uint16_t) * nr1, MSG_WAITALL);

    uint16_t nr2;
    recv(c, &nr2, sizeof(uint16_t), MSG_WAITALL);
    nr2 = ntohs(nr2);

    uint16_t* numere2 = (uint16_t*)malloc(sizeof(uint16_t) * nr2);
    recv(c, numere2, sizeof(uint16_t) * nr2, MSG_WAITALL);

    uint16_t nr_nou = 0;
    uint16_t* numere = (uint16_t*)malloc(sizeof(uint16_t) * nr1);

    printf("[FROM CLIENT] Numere primite cu succes!\n");
    printf("[IN SERVER] Incepere prelucrare date...\n");

    for(int i = 0; i < nr1; i++) {
        bool ok = true;
        for(int j = 0; j < nr2; j++) {
            if(numere1[i] == numere2[j]) {
                ok = false;
                break;
            }
        }
        if(ok) {
            numere[nr_nou] = htons(numere1[i]);
            nr_nou++;
        }
    }
    nr_nou = htons(nr_nou);

    free(numere1);
    free(numere2);

    send(c, &nr_nou, sizeof(uint16_t), 0);
    send(c, numere, sizeof(uint16_t) * ntohs(nr_nou), 0);

    free(numere);

    printf("[TO CLIENT] Numere trimise cu succes!\n");

    close(c);

    pthread_exit(NULL);  // Termin executia threadului curent
    return NULL;
}

int main(int argc, char* argv[]) {
    if(argc < 2) {
        printf("Eroare! Mod utilizare: ./server port_number");
        return 1;
    }

    int s;
    struct sockaddr_in server, client;
    int l;

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        printf("Eroare la crearea socketului server\n");
        return 1;
    }

    memset(&server, 0, sizeof(server));
    server.sin_port = htons(atoi(argv[1]));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;

    if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
        printf("Eroare la bind\n");
        return 1;
    }

    listen(s, 5);

    l = sizeof(client);
    memset(&client, 0, sizeof(client));

    while (1) {
        int c = accept(s, (struct sockaddr *) &client, &l);
        if (c < 0) {
            printf("Eroare la acceptare client\n");
            continue;
        }

        printf("[IN SERVER] S-a conectat un client.\n");

        // aloc memorie pentru socketul clientului pentru a-l putea trece la thread
        int* client_socket = malloc(sizeof(int));
        *client_socket = c;

        pthread_t th;
        // creez un thread pentru fiecare client
        if (pthread_create(&th, NULL, deservire_client, client_socket) != 0) {
            printf("Eroare la crearea threadului\n");
            free(client_socket);
        } else {
            // detach la thread pentru a rula independent, serverul nefiind nevoit sa astepte
            // finalizarea acestuia
            pthread_detach(th);
        }
    }

   
