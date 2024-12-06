#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

void copy(char *src, char *dst) {
    int sfd = open(src, O_RDONLY);
    if (sfd == -1) { perror("Source open"); exit(1); }
    int dfd = open(dst, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (dfd == -1) { perror("Dest open"); close(sfd); exit(1); }
    char buffer[BUFFER_SIZE];
    int count;
    while ((count = read(sfd, buffer, BUFFER_SIZE)) > 0)
        if (write(dfd, buffer, count) != count) { perror("Write"); break; }
    if (count == -1) perror("Read");
    close(sfd); close(dfd);
}

int main(int argc, char *argv[]) {
    if (argc != 3) { fprintf(stderr, "Usage: %s <src> <dst>\n", argv[0]); return 1; }
    printf("Copying %s to %s\n", argv[1], argv[2]);
    copy(argv[1], argv[2]);
    return 0;
}

