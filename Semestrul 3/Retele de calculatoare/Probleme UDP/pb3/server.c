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

        for(int i = 0; i < k; i++)
                if(sir[i] == ' ')
                        a++;

        a = htons(a);
        sendto(s, &a, sizeof(a), MSG_WAITALL, (struct sockaddr*) &client, l);
        printf("[To client] send succesfully\n");

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
