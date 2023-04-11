# Git Commands Automation with Giter

Giter is a command-line tool for simplifying the process of committing and pushing changes to a remote Github repository. It also allows the creation of a new repository and initialization of the local directory as a Git repository.

## Prerequisites
Before using Giter, you must have Git installed on your system. Additionally, if you want to create a new repository, you must have the GitHub CLI installed as well.

## Usage
To use Giter, enter the following command in your terminal:

```
giter <files> <message> [-n]
```

- `files`: a list of files to be added to the repository
- `message`: a commit message.
- `-n`: an optional flag to create a new repository. If this flag is present, Giter will prompt you to enter the name of the new repository and whether to make it public or private..

## Features
Giter offers the following features:
- Adds files to the staging area, commits changes, and pushes them to an existing repository.
- Creates a repository and initializes the directory, setting the remote URL, if the `-n` flag is passed.

## Limitations
Please note the following limitations of Giter:
- Giter only works with GitHub repositories.
- Giter assumes that you have the necessary permissions to create and push to a repository.
- Giter only supports the `main` branch.

## Credits
This tool was written by **Oussama Teyib**.