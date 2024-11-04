#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>

#define STRING_SIZE 1024

void* deservire_client(void* arg) {
    int c = *((int*)arg);    // preiau socketul din argument
    free(arg);

    uint16_t nr1, nr2;

    // primesc primul sir
    recv(c, &nr1, sizeof(uint16_t), MSG_WAITALL);
    nr1 = ntohs(nr1);

    uint16_t* sir1 = (uint16_t*)malloc(sizeof(uint16_t) * nr1);
    for (int i = 0; i < nr1; i++) {
        uint16_t x;
        recv(c, &x, sizeof(uint16_t), MSG_WAITALL);
        sir1[i] = ntohs(x);
    }

    // primesc cel de-al doilea sir
    recv(c, &nr2, sizeof(uint16_t), MSG_WAITALL);
    nr2 = ntohs(nr2);
  
    uint16_t* sir2 = (uint16_t*)malloc(sizeof(uint16_t) * nr2);
    for (int i = 0; i < nr2; i++) {
        uint16_t x;
        recv(c, &x, sizeof(uint16_t), MSG_WAITALL);
        sir2[i] = ntohs(x);
    }

    printf("[FROM SERVER] Am primit %hu nr in sir1 si %hu nr in sir2\n", nr1, nr2);

    // determin numerele comune folosind un set pentru eficienta
    bool numere_primul_sir[65536] = {false}; // folosesc un array pentru valori unice
    for (int i = 0; i < nr1; i++) {
        numere_primul_sir[sir1[i]] = true;
    }

    // stochez numerele comune intr un array temporar
    uint16_t* sirComune = (uint16_t*)malloc(sizeof(uint16_t) * (nr1 < nr2 ? nr1 : nr2));
    uint16_t poz = 0;

    for (int i = 0; i < nr2; i++) {
        if (numere_primul_sir[sir2[i]]) {
            sirComune[poz++] = htons(sir2[i]); 
            numere_primul_sir[sir2[i]] = false; // evit duplicarea numerelor comune
        }
    }

    // trimit lista de numere comune catre client
    uint16_t pozNetwork = htons(poz);
    send(c, &pozNetwork, sizeof(uint16_t), 0);
    send(c, sirComune, sizeof(uint16_t) * poz, 0);

    printf("[TO CLIENT] Am trimis %hu numere catre client\n", poz);

    // curatare memorie
    free(sir1);
    free(sir2);
    free(sirComune);

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
