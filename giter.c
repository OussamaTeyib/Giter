// git commands automation

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CMD 100

void die(const char *msg)
{
    fprintf(stderr, "%s", msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    if (argc != 3 && argc != 4)
        die("Usage: giter <input-files> <message> [-n]\n");

    char *cmd = malloc(MAX_CMD);
    if (!cmd)
        die("Cannot allocate memory for cmd string!\n");
    
    // if no flags passed (argc is 3), argv[3] is NULL. so, passing it to strcmp() causes a segfault.
    // We check if it isn't not NULL (if argc is 4), and then compare it with '-n'.
    if (argc == 4 && !strcmp(argv[3], "-n"))
    {  
        char *name = malloc(MAX_CMD);
        if (!name)
        {
            free(cmd);
            die("Cannot allocate memory for the name of the repo!\n");
        }

        printf("Enter the name of the repository: ");
        fgets(name, MAX_CMD, stdin);
        name[strlen(name) - 1] = '\0';

        int public;
        printf("Make the repository public? (1/0): ");
        if (scanf("%d", &public) != 1 || public < 0 || public > 1)
        {
            free(cmd);
            free(name);            
            die("Invalid input!\n");
        }

        // create the repository
        snprintf(cmd, MAX_CMD, "gh repo create %s %s\n", name, public? "--public" : "--private");
        if (system(cmd))
        {
            free(cmd);
            free(name);
            die("Failed to create repository!\n");
        }
        printf("Repository is created!\n");

        // initialize this dir as .git repository
        if (system("git init"))
        {
            free(cmd);
            free(name);
            die("Failed to initialize the directory!\n");
        }
        printf("Directory is initialized!\n");

        // set remote URL
        snprintf(cmd, MAX_CMD, "git remote add origin https://github.com/OussamaTeyib/%s.git", name); 
        if (system(cmd))
        {
            free(cmd);
            free(name);
            die("Failed to set remote URL!\n");
        }
        printf("Remote URL is set!\n");

        free(name);
    }

    // set default name of the branch
    if(system("git branch -m main"))
    {
        free(cmd);
        die("Failed to set default name!\n");
    } 
    printf("Deafult name is set!\n");
   
    // add files to staging zone     
    snprintf(cmd, MAX_CMD, "git add %s", argv[1]);
    if (system(cmd))
    {
        free(cmd);
        die("Failed to add the files to staging zone!\n");
    }
    printf("Files are added!\n");

    // commit the changes
    snprintf(cmd, MAX_CMD, "git commit -m \"%s\"", argv[2]);
    if (system(cmd))
    {
        free(cmd);
        die("Failed to commit the changes!\n");
    }
    printf("Changes are commited!\n");

    // push the changes
    if (system("git push origin main"))
    {
        free(cmd);
        die("Failed to push the changes!\n");
    }
    printf("Changes are pushed!\n");

    free(cmd);
    return EXIT_SUCCESS;
}