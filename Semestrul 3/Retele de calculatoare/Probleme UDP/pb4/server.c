#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdlib.h>

#define STRING_SIZE 256

void primeste_client(int s, struct sockaddr_in client) {
        uint16_t a = 0;
        int p = 0;
        char* sir = (char*)malloc(sizeof(char) * STRING_SIZE);
        int l = sizeof(client);

        uint16_t lg;
        recvfrom(s, &lg, sizeof(uint16_t), MSG_WAITALL, (struct sockaddr*) &client, &l);
        lg = ntohs(lg);

        int k = recvfrom(s, sir, lg, MSG_WAITALL, (struct sockaddr*) &client, &l);
        printf("[from client] am primit %d octeti din %hu\n", k, lg);
        sir[k] = '\0';

        char* sir_c = (char*)malloc(sizeof(char) * k);
        strcpy(sir_c, sir);
        int r = 0, t = strlen(sir_c) - 1;
        while(t >= 0)
                sir[r++] = sir_c[t--];
        free(sir_c);

        lg = htons(k);
        sendto(s, &lg, sizeof(uint16_t), 0, (struct sockaddr*) &client, l);
        k = sendto(s, sir, sizeof(char) * k, 0, (struct sockaddr*) &client, l);

        printf("[in server] sir inversat: %s\n", sir);
        printf("[to client] am trimis %d octeti din %hu\n", k, htons(lg));

        free(sir);
}


int main(int argc, char* argv[]) {
        int s;
        struct sockaddr_in server, client;
        int c, l, i;
        uint16_t k, old = 0;

        s = socket(AF_INET, SOCK_DGRAM, 0);
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

        l = sizeof(client);
        memset(&client, 0, sizeof(client));

        while(1)
                primeste_client(s, client);

        close(s);
}
