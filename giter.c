#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc < 3 || argc > 5)
    {
        fprintf(stderr, "Usage: giter <input-files> <message> <option>\n");
        fprintf(stderr, "Options:\n"
                        "    -n: to create a new repository.\n"
                        "        You must pass the name!\n"
                        "    NOTHING: to push to an existant repository\n");
        return -1;
    }
   
    char *cmd = malloc(100);
    /* if (!strcmp(argv[3], "-n"))
    {
        if (!argv[4])
        {
            fprintf(stderr, "Pass the name of the repository!\n");
            free(cmd);
            return -1;
        }   
        snprintf(cmd, 100, "gh repo create %s\n", argv[4]);
        system(cmd);    
        snprintf(cmd, 100, "git remote add https://github.com/OussamaTeyib/%s.git", argv[4]); 
        system(cmd);
    } */

    snprintf(cmd, 100, "git add %s", argv[1]);
    system(cmd);

    snprintf(cmd, 100, "git commit -m \"%s\"", argv[2]);
    system(cmd);
    printf("\nCommiting is done!\n");

    system("git push origin main");

    free(cmd);
    return 0;
}