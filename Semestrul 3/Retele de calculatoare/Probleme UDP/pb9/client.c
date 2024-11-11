#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define STRING_SIZE 256

void trimite_server(int c, struct sockaddr_in server) {
        char sir[100] = "Da-mi data si ora\n";

        uint16_t lg = strlen(sir) + 1;
        lg = htons(lg);
        sendto(c, &lg, sizeof(uint16_t), 0, (struct sockaddr*) &server, sizeof(server));

        sendto(c, &sir, ntohs(lg), 0, (struct sockaddr*) &server, sizeof(server));
        printf("sent\n");

        int l = sizeof(server);

        time_t times;
        recvfrom(c, &times, sizeof(time_t), MSG_WAITALL, (struct sockaddr*) &server, &l);
        times = ntohl(times);
        struct tm *local_time = localtime(&times);

        printf("[from server] timpul e: %02d/%02d/%04d %02d:%02d\n",
                local_time->tm_mday,
                local_time->tm_mon + 1,
                local_time->tm_year + 1900,
                local_time->tm_hour,
                local_time->tm_min);

}

int main(int argc, char* argv[]) {
        int c;
        struct sockaddr_in server;
        uint16_t a, b, suma, i, k;


        c = socket(AF_INET, SOCK_DGRAM, 0);
        if (c < 0) {
                printf("Eroare la crearea socketului client\n");
                return 1;
        }

        memset(&server, 0, sizeof(server));
        server.sin_port = htons(atoi(argv[1]));
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = inet_addr("127.0.0.1");

        trimite_server(c, server);

        close(c);
}
