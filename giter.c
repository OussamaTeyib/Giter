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

    snprintf(cmd, 100, "git commit -m \"%s\"", argv[2]);
    system(cmd);

    system("git push origin main");

    free(cmd);
    return 0;
}