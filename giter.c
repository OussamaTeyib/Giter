// git commands automation

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CMD 100

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
    
    char *cmd = malloc(MAX_CMD);
    if (!cmd)
    {
        printf("Cannot allocate memory for cmd string!\n");
        return -1;
    }
    
    // if no flags passed, argv[3] is NULL. so, passing it to strcmp() causes a segfault.
    // We check if it isn't not NULL, and then compare it with '-n'.
    if (argv[3] && strcmp(argv[3], "-n"))
    {  
        char *name = malloc(MAX_CMD);
        if (!cmd)
        {
            printf("Cannot allocate memory for the name of the repo!\n");
            free(cmd);
            return -1;
        }

        printf("Enter the name of the repository: ");
        fgets(name, MAX_CMD, stdin);
        name[strlen(name) - 1] = '\0';

        int public;
        printf("Make the repository public? (1/0): ");
        if (scanf("%d", &public) != 1 || public < 0 || public > 1)
        {
            printf("Invalid input!\n");
            free(cmd);
            free(name);
            return -1;
        }

        // create the repository
        snprintf(cmd, MAX_CMD, "gh repo create %s %s\n", name, public? "--public" : "--private");
        if (system(cmd))
        {
            printf("Failed to create repository!\n");
            free(cmd);
            free(name);
            return -1;
        }
        printf("Repository is created!\n");

        // initialize this dir as .git repository
        if (system("git init"))
        {
            printf("Failed to initialize the directory!\n");
            free(cmd);
            free(name);
            return -1;
        }
        printf("Directory is initialized!\n");

        // set remote URL
        snprintf(cmd, MAX_CMD, "git remote add origin https://github.com/OussamaTeyib/%s.git", name); 
        if (system(cmd))
        {
            printf("Failed to set remote URL!\n");
            free(cmd);
            free(name);
            return -1;
        }
        printf("Remote URL is set!\n");

        free(name);
    }

    // set default name of the branch
    if(system("git branch -m main"))
    {
        printf("Failed to set default name!\n");
        free(cmd);
        return -1;
    } 
    printf("Deafult name is set!\n");
   
    // add files to staging zone     
    snprintf(cmd, MAX_CMD, "git add %s", argv[1]);
    if (system(cmd))
    {
        printf("Failed to add the files to staging zone!\n");
        free(cmd);
        return -1;
    }
    printf("Files are added!\n");

    // commit the changes
    snprintf(cmd, MAX_CMD, "git commit -m \"%s\"", argv[2]);
    if (system(cmd))
    {
        printf("Failed to commit the changes!\n");
        free(cmd);
        return -1;
    }
    printf("Changes are commited!\n");

    // push the changes
    if (system("git push origin main"))
    {
        printf("Failed to push the changes!\n");
        free(cmd);
        return -1;
    }
    printf("Changes are pushed!\n");

    free(cmd);
    return 0;
}