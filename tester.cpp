//
// Created by Vitaliy Vorobyov on 2019-04-07.
//

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

int main() {
    const char* server_name = "localhost";
    const int server_port = 8001;

    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    inet_pton(AF_INET, server_name, &server_address.sin_addr);

    server_address.sin_port = htons(server_port);

    int sock;
    if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        printf("could not create socket\n");
        return 1;
    }

    if (connect(sock, (struct sockaddr*)&server_address,
                sizeof(server_address)) < 0) {
        printf("could not connect to server\n");
        return 1;
    }

    const char* data_to_send = "Test message\n";
    int maxlen = 100;
    char buffer[maxlen];

    for (int i = 0; i < 10; ++i) {
        send(sock, data_to_send, strlen(data_to_send), 0);
        recv(sock, buffer, maxlen, 0);
        printf("received: %s", buffer);
    }

    close(sock);
    return 0;
}