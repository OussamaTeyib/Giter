#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 3 && argc != 4)
    {
        fprintf(stderr, "Usage: giter <input-files> <message> <option>\n");
        fprintf(stderr, "Options:\n"
                        "    -n: to create a new repository.\n"
                        "    NOTHING: to push to an existant repository\n");
        return -1;
    }
    
    char *cmd = malloc(100);
    if (!cmd)
    {
        printf("Cannot allocate memory for cmd string!\n");
        return -1;
    }
    
    // if no flags passed, argv[3] is NULL. so, passing it to strcmp() causes a segfault.
    // We check if it isn't not NULL, and then compare it with '-n'.
    if (argv[3] && strcmp(argv[3], "-n"))
    {  
        char *name = malloc(100);
        if (!cmd)
        {
            printf("Cannot allocate memory for the name of the repo!\n");
            free(cmd);
            return -1;
        }

        printf("Enter the name of the repository: ");
        fgets(name, 100, stdin);
        name[strlen(name) - 1] = '\0';

        int public;
        printf("Make the repository public? (1/0): ");
        scanf("%d", &public);

        // create the repository
        snprintf(cmd, 100, "gh repo create %s %s\n", name, public? "--public" : "--private");
        system(cmd);
        printf("Repository is created!\n");

        // intialize this dir as .git repository
        system("git init");
        printf("Directory is initalized!\n");

        // set remote URL
        snprintf(cmd, 100, "git remote add origin https://github.com/OussamaTeyib/%s.git", name); 
        system(cmd);
        printf("Remote URL is set!\n");

        free(name);
    }

    // set default name of the branch
    system("git branch -m main");  
    printf("Deafult name is set!\n");
   
    // add files to staging zone     
    snprintf(cmd, 100, "git add %s", argv[1]);
    system(cmd);
    printf("Files are added!\n");

    // commit the changes
    snprintf(cmd, 100, "git commit -m \"%s\"", argv[2]);
    system(cmd);
    printf("Changes are commited!\n");

    // push the changes
    system("git push origin main");
    printf("Changes are pushed!\n");

    free(cmd);
    return 0;
}