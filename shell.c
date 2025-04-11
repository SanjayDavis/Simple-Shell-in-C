#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void execute(char **args, int i);
void parse(char *test_command, char *start);

int check(const char *token) {
    if (token == NULL) return 2;
    if (strcmp(token, "start") == 0) return 0;
    else if (strcmp(token, "exit") == 0 || strcmp(token, "logout") == 0) return 1;
    else return 2;
}

char *take_line() {
    char temp[256];
    size_t size = 256;
    size_t len = 0;

    char *command = malloc(size);
    if (!command) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    command[0] = '\0';

    while (fgets(temp, sizeof(temp), stdin)) {
        size_t temp_len = strlen(temp);

        if (len + temp_len + 1 > size) {
            size *= 2;
            char *new_command = realloc(command, size);
            if (!new_command) {
                free(command);
                perror("realloc failed");
                exit(EXIT_FAILURE);
            }
            command = new_command;
        }

        strcat(command, temp);
        len += temp_len;

        if (temp[temp_len - 1] == '\n') break;
    }

    return command;
}

void add(char *start, char add) {
    int len = strlen(start);

    if (len >= 2 && start[0] == '"' && start[len - 1] == '"') {
        start[len - 1] = '\0';
        memmove(start, start + 1, len - 1);
        len -= 2;
    }

    if (start[len - 1] != ':') {
        start[len] = add;
        start[len + 1] = '\0';
    }
}

void parse(char *test_command, char *start) {
    const char *delim = " \t\n\a";
    char *token = strtok(test_command, delim);
    int i = 0;
    char *args[100];

    switch (check(token)) {
        case 0: {
            token = strtok(NULL, delim);
            token = strtok(NULL, delim);
            if (token) {
                strcpy(start, token);
                add(start, ':');
            }
            return;
        }
        case 1:
            exit(0);
        case 2:
        default: {
            while (token != NULL && i < 99) {
                args[i++] = token;
                token = strtok(NULL, delim);
            }
            args[i] = NULL;

            if (i > 0)
                execute(args, i);
            break;
        }
    }
}

void execute(char *args[], int i) {
    pid_t pid = fork();
    if (pid == 0) {
        execvp(args[0], args);
        perror("exec failed");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        wait(NULL);
    } else {
        perror("fork failed");
    }
}

int main() {
    char start[100];
    strcpy(start, ">:");

    while (true) {
        printf("%s", start);
        char *command = take_line();
        if (!command) continue;
        parse(command, start);
        free(command);
    }

    return 0;
}
