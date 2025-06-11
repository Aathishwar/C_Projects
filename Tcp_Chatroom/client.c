#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define BUFFER_SIZE 1024
#define SECRET_KEY 0x5A

int sockfd;
char username[50];

void xor_encrypt_decrypt(char *data) {
    for (int i = 0; data[i] != '\0'; i++) {
        data[i] ^= SECRET_KEY;
    }
}

void *receive_messages(void *arg) {
    char buffer[BUFFER_SIZE];
    while (1) {
        int bytes_received = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received <= 0) {
            printf("[-] Disconnected from chat.\n");
            exit(0);
        }
        buffer[bytes_received] = '\0';
        xor_encrypt_decrypt(buffer);
        printf("%s", buffer);
        fflush(stdout);
    }
    return NULL;
}

int main() {
    struct sockaddr_in server_addr;
    pthread_t recv_thread;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connect failed");
        exit(1);
    }

    printf("Enter your name: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';
    send(sockfd, username, strlen(username), 0);

    printf("Connected to chat room as [%s]\n", username);
    pthread_create(&recv_thread, NULL, receive_messages, NULL);

    char message[BUFFER_SIZE];
    while (1) {
        fgets(message, sizeof(message), stdin);
        if (strlen(message) > 1) {
            xor_encrypt_decrypt(message);
            send(sockfd, message, strlen(message), 0);
        }
    }

    close(sockfd);
    return 0;
}
