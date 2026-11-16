#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#include <string.h>
#include <windows.h>

#define FOLDER_PATH "C:\\Users\\NEW\\Desktop\\wallpapers"
#define MAX_FILES 500

int main() {
    DIR *dir;
    struct dirent *entry;
    char *images[MAX_FILES];
    int count = 0;

    dir = opendir(FOLDER_PATH);
    if (dir == NULL) {
        printf("Folder not found: %s\n", FOLDER_PATH);
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        char *name = entry->d_name;
        int len = strlen(name);

        if ((len > 4 && strcmp(name + len - 4, ".jpg") == 0) ||
            (len > 5 && strcmp(name + len - 5, ".jpeg") == 0) ||
            (len > 4 && strcmp(name + len - 4, ".png") == 0) ||
            (len > 4 && strcmp(name + len - 4, ".bmp") == 0)) {

            char full_path[1024];
            snprintf(full_path, sizeof(full_path), "%s\\%s", FOLDER_PATH, name);
            images[count] = _strdup(full_path);
            count++;
        }
    }
    closedir(dir);

    if (count == 0) {
        printf("No image found in the folder!\n");
        return 1;
    }

    srand(time(NULL));
    int random_index = rand() % count;
    char *chosen = images[random_index];

    printf("Please wait: %s\n", chosen);

    SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, chosen,
                         SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);

    for (int i = 0; i < count; i++) free(images[i]);

    return 0;
}