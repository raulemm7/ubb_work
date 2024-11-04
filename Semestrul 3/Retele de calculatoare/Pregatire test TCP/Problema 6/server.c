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

    // primesc sirul de caractere
    char* sir = (char*)malloc(sizeof(char) * STRING_SIZE);
    int i = 0;
    char car;
    recv(c, &car, sizeof(char), MSG_WAITALL);
    while(car != '\0') {
        sir[i] = car;
        i++;

        recv(c, &car, sizeof(char), MSG_WAITALL);
    }
    int lungime = i;
    sir[i] = '\0';

    // primesc doar caracterul
    recv(c, &car, sizeof(char), MSG_WAITALL);

    printf("[FROM CLIENT] Sirul de caractere a fost primit cu succes!\n");

    // incep taskul in sine
    uint16_t cont = 0;
    uint16_t* pos = (uint16_t*)malloc(sizeof(uint16_t) * lungime);
    for(i = 0; i < lungime; i++) {
        if(sir[i] == car) {
                pos[cont] = htons(i);
                cont++;
        }
    }

    // trimit numarul de numere
    cont = htons(cont);
    send(c, &cont, sizeof(uint16_t), 0);

    // trimit numerele
    send(c, pos, sizeof(uint16_t) * cont, 0);

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

    return 0;
}
