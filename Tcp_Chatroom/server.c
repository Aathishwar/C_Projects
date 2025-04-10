#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024
#define SECRET_KEY 0x5A

int clients[MAX_CLIENTS];
char usernames[MAX_CLIENTS][50];
const char *colors[] = {
    "\033[1;31m", "\033[1;32m", "\033[1;33m",
    "\033[1;34m", "\033[1;36m", "\033[1;35m"
};
#define COLOR_RESET "\033[0m"

void xor_encrypt_decrypt(char *data) {
    for (int i = 0; data[i] != '\0'; i++) {
        data[i] ^= SECRET_KEY;
    }
}

void broadcast_message(const char *message, int sender_fd) {
    for (int i = 0; i < MAX_CLIENTS; ++i) {
        if (clients[i] != 0 && clients[i] != sender_fd) {
            char encrypted[BUFFER_SIZE];
            strncpy(encrypted, message, sizeof(encrypted));
            xor_encrypt_decrypt(encrypted);
            send(clients[i], encrypted, strlen(encrypted), 0);
        }
    }
}

int main() {
    int server_fd, new_socket, max_sd, sd, activity;
    struct sockaddr_in address;
    fd_set readfds;
    char buffer[BUFFER_SIZE];
    socklen_t addrlen = sizeof(address);

    for (int i = 0; i < MAX_CLIENTS; i++) clients[i] = 0;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 5);

    printf("Server started on port 8080\n");

    while (1) {
        FD_ZERO(&readfds);
        FD_SET(server_fd, &readfds);
        max_sd = server_fd;

        for (int i = 0; i < MAX_CLIENTS; i++) {
            sd = clients[i];
            if (sd > 0) FD_SET(sd, &readfds);
            if (sd > max_sd) max_sd = sd;
        }

        activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);

        if (FD_ISSET(server_fd, &readfds)) {
            new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);
            char username[50] = {0};
            recv(new_socket, username, sizeof(username), 0);
            for (int i = 0; i < MAX_CLIENTS; i++) {
                if (clients[i] == 0) {
                    clients[i] = new_socket;
                    strncpy(usernames[i], username, sizeof(usernames[i]) - 1);
                    printf("[+] %s connected.\n", username);
                    break;
                }
            }
        }

        for (int i = 0; i < MAX_CLIENTS; i++) {
            sd = clients[i];
            if (FD_ISSET(sd, &readfds)) {
                int valread = recv(sd, buffer, BUFFER_SIZE - 1, 0);
                if (valread <= 0) {
                    printf("[-] %s disconnected.\n", usernames[i]);
                    close(sd);
                    clients[i] = 0;
                    usernames[i][0] = '\0';
                } else {
                    buffer[valread] = '\0';
                    xor_encrypt_decrypt(buffer);
                    char message[BUFFER_SIZE + 100];
                    snprintf(message, sizeof(message), "%s[%s]%s %s",
                             colors[i % 6], usernames[i], COLOR_RESET, buffer);
                    printf("%s", message);
                    broadcast_message(message, sd);
                }
            }
        }
    }

    return 0;
}
