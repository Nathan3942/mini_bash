#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd;
    int stdout_backup;

    // Sauvegarder le descripteur de fichier de la sortie standard
    stdout_backup = dup(STDOUT_FILENO);
    if (stdout_backup == -1) {
        perror("dup");
        exit(EXIT_FAILURE);
    }

    // Ouvrir (ou créer) le fichier output.txt avec des permissions d'écriture
    fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Dupliquer le descripteur de fichier fd vers STDOUT_FILENO
    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("dup2");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Fermer l'ancien descripteur de fichier car il n'est plus nécessaire
    close(fd);

    // Toutes les sorties suivantes vers stdout iront dans le fichier output.txt
    printf("Ceci sera écrit dans le fichier output.txt\n");

    // Restaurer la sortie standard
    if (dup2(stdout_backup, STDOUT_FILENO) == -1) {
        perror("dup2");
        close(stdout_backup);
        exit(EXIT_FAILURE);
    }

    // Fermer le descripteur de fichier sauvegardé car il n'est plus nécessaire
    close(stdout_backup);

    // Toutes les sorties suivantes vers stdout iront de nouveau dans le terminal
    printf("Ceci sera écrit dans le terminal\n");

    return 0;
}
