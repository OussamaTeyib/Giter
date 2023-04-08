#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: giter <input-files> <message>\n");
        return -1;
    }

    char *cmd = malloc(100);
    snprintf(cmd, 100, "git add %s", argv[1]);
    system(cmd);
    printf("\nAdding is done!\n");

    snprintf(cmd, 100, "git commit -m \"%s\"", argv[2]);
    system(cmd);
    printf("\nCommiting is done!\n");

    system("git push origin main");
    printf("\nPushing is done!\n");

    free(cmd);
    return 0;
}