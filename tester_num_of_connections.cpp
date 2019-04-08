//
// Created by Vitaliy Vorobyov on 2019-04-07.
//

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <chrono>
#include <atomic>

inline std::chrono::high_resolution_clock::time_point get_current_time_fenced()
{
    std::atomic_thread_fence(std::memory_order_seq_cst);
    auto res_time = std::chrono::high_resolution_clock::now();
    std::atomic_thread_fence(std::memory_order_seq_cst);
    return res_time;
}

template<class D>
inline long long to_us(const D& d)
{
    return std::chrono::duration_cast<std::chrono::microseconds>(d).count();
}

int main() {
    const char* server_name = "localhost";
    const int server_port = 8001;

    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    inet_pton(AF_INET, server_name, &server_address.sin_addr);

    server_address.sin_port = htons(server_port);

    int sock_1, sock_2, sock_3;
    if ((sock_1 = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("could not create socket 1\n");
        return 1;
    }

    if ((sock_2 = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        printf("could not create socket 2\n");
        return 1;
    }

    if ((sock_3 = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        printf("could not create socket 3\n");
        return 1;
    }

    auto connect_1 = connect(sock_1, (struct sockaddr*)&server_address, sizeof(server_address));
    auto connect_2 = connect(sock_2, (struct sockaddr*)&server_address, sizeof(server_address));
    auto connect_3 = connect(sock_3, (struct sockaddr*)&server_address, sizeof(server_address));

    const char* data_to_send = "Test message\n";
    int maxlen = 100;
    char buffer[maxlen];
    int counter = 0;
    auto start_time = get_current_time_fenced();


    while(to_us(get_current_time_fenced() - start_time) <= 1000000) {
        send(sock_1, data_to_send, strlen(data_to_send), 0);
        recv(sock_1, buffer, maxlen, 0);
        send(sock_2, data_to_send, strlen(data_to_send), 0);
        recv(sock_2, buffer, maxlen, 0);
        send(sock_3, data_to_send, strlen(data_to_send), 0);
        recv(sock_3, buffer, maxlen, 0);
        memset(buffer, 0, maxlen);
        counter++;
    }

    printf("Handled: %d requests\n", counter);

    close(sock_1);
    close(sock_2);
    close(sock_3);
    return 0;
}