/* Git Automation Tool      *
 * Written by Oussama Teyib *
 * April 2023               */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CMD 100

void die(const char *msg)
{
    fprintf(stderr, "giter: %s\n", msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    if (argc != 3 && argc != 4)
        die("Usage: giter <input-files> <message> [-n]");

    if (system("git --version > NUL"))
        die("Git is not installed on this system!");

    if (system("gh --version > NUL"))
        die("Github CLI is not installed on this system!");

    char *cmd = malloc(MAX_CMD);
    if (!cmd)
        die("Cannot allocate memory for cmd string!");
    
    // if no flags passed (argc is 3), argv[3] is NULL. so, passing it to strcmp() causes a segfault.
    // We check if it isn't not NULL (if argc is 4), and then compare it with '-n'.
    if (argc == 4 && !strcmp(argv[3], "-n"))
    {  
        char *name = malloc(MAX_CMD);
        if (!name)
        {
            free(cmd);
            die("Cannot allocate memory for the name of the repo!");
        }

        printf("Enter the name of the repository: ");
        fgets(name, MAX_CMD, stdin);
        name[strlen(name) - 1] = '\0';
        if (!strlen(name))
        {
            free(cmd);
            free(name);
            die("Invalid input!");
        }

        int public;
        printf("Make the repository public? (1/0): ");
        if (scanf("%d", &public) != 1 || public < 0 || public > 1)
        {
            free(cmd);
            free(name);            
            die("Invalid input!");
        }

        // create the repository
        snprintf(cmd, MAX_CMD, "gh repo create %s %s > NUL\n", name, public? "--public" : "--private");
        if (system(cmd))
        {
            free(cmd);
            free(name);
            die("Failed to create repository!");
        }
        printf("Repository is created!\n");

        // initialize this dir as .git repository
        if (system("git init > NUL"))
        {
            free(cmd);
            free(name);
            die("Failed to initialize the directory!");
        }

        // set remote URL
        snprintf(cmd, MAX_CMD, "git remote add origin https://github.com/OussamaTeyib/%s.git > NUL", name); 
        if (system(cmd))
        {
            free(cmd);
            free(name);
            die("Failed to set remote URL!");
        }

        free(name);
    }

    // check if the dir is a git repo
    // if '-n' is passed, this check is not necessary because the dir get initialized
    // send stdout (if success) to Dave Null and stderr (if failure) to where stdout is sent to
    if (system("git status > NUL 2>&1"))
    {
        free(cmd);
        die("This directory is not a git repository!");
    }

    // set default name of the branch
    if (system("git branch -m main"))
    {
        free(cmd);
        die("Failed to set default name!");
    } 
   
    // add files to staging zone     
    snprintf(cmd, MAX_CMD, "git add %s", argv[1]);
    if (system(cmd))
    {
        free(cmd);
        die("Failed to add the files to staging zone!");
    }
    printf("Files are added!\n");

    // commit the changes
    snprintf(cmd, MAX_CMD, "git commit -m \"%s\" > NUL", argv[2]);
    if (system(cmd))
    {
        free(cmd);
        die("Failed to commit the changes!");
    }
    printf("Changes are commited!\n");

    // push the changes
    // push -strangely- always send its output to stderr
    if (system("git push origin main 2> NUL"))
    {
        free(cmd);
        die("Failed to push the changes!");
    }
    printf("Changes are pushed!\n");

    free(cmd);
    return EXIT_SUCCESS;
}