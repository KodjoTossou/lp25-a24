#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>
#include "file_handler.h"
#include "deduplication.h"

// Fonction permettant de lire un élément du fichier .backup_log
log_t read_backup_log(const char *logfile){
    /* Implémenter la logique pour la lecture d'une ligne du fichier ".backup_log"
    * @param: logfile - le chemin vers le fichier .backup_log
    * @return: une structure log_t
    */
    log_t logs = {NULL, NULL};
    FILE *file = fopen(logfile, "r");
    if (!file) {
        perror("Failed to open backup_log");
        return logs;
    }
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        log_element *new_element = malloc(sizeof(log_element));
        if (!new_element) {
            perror("Failed to allocate memory");
            fclose(file);
            return logs;
        }
        char md5_str[MD5_DIGEST_LENGTH * 2 + 1];
        new_element->date = malloc(20);

        sscanf(line, "%ms %s %19s", &new_element->path, md5_str, new_element->date);

        for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
            sscanf(md5_str + i * 2, "%2hhx", &new_element->md5[i]);
        }

        new_element->next = NULL;
        new_element->prev = logs.tail;

        if (logs.tail) {
            logs.tail->next = new_element;
        } else {
            logs.head = new_element;
        }
        logs.tail = new_element;
    }

    fclose(file);
    return logs;
}

// Fonction permettant de mettre à jour une ligne du fichier .backup_log
void update_backup_log(const char *logfile, log_t *logs){
  /* Implémenter la logique de modification d'une ligne du fichier ".bakcup_log"
  * @param: logfile - le chemin vers le fichier .backup_log
  *         logs - qui est la liste de toutes les lignes du fichier .backup_log sauvegardée dans une structure log_t
  */

}

void write_log_element(log_element *elt, FILE *logfile){
  /* Implémenter la logique pour écrire un élément log de la liste chaînée log_element dans le fichier .backup_log
   * @param: elt - un élément log à écrire sur une ligne
   *         logfile - le chemin du fichier .backup_log
   */
}

void list_files(const char *path){
  /* Implémenter la logique pour lister les fichiers présents dans un répertoire
  */
}


