
#include "pipex.h"

int main() {
    int	pipe[2]; //array que vai armazenar os fds fd[0]->leitura e fd[1]->escrita
    pid_t pid;

    pid = fork(); // Cria um novo processo

    if (pid < 0) {
        // Erro ao criar o processo
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Código executado pelo processo filho
        printf("Sou o processo filho, meu PID é %d\n", getpid());
    } else {
        // Código executado pelo processo pai
        printf("Sou o processo pai, meu PID é %d, e meu filho tem PID %d\n", getpid(), pid);
    }

    return 0;
}