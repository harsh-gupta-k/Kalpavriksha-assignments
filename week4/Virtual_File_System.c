#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BLOCK_SIZE 512
#define NUM_BLOCKS 10

struct FreeBlock
{
    int index;
    struct FreeBlock *next;
    struct FreeBlock *prev;
};

char virtualDisk[NUM_BLOCKS][BLOCK_SIZE];
struct FreeBlock *freeListHead = NULL;

void initializeFreeBlocks()
{
    struct FreeBlock *prevNode = NULL;
    for (int i = 0; i < NUM_BLOCKS; i++)
    {
        struct FreeBlock *node = (struct FreeBlock *)malloc(sizeof(struct FreeBlock));
        node->index = i;
        node->next = NULL;
        node->prev = prevNode;

        if (prevNode != NULL)
        {
            prevNode->next = node;
        }
        else
        {
            freeListHead = node;
        }
        prevNode = node;
        strcpy(virtualDisk[i], "");
    }
    printf("Free block list initialized\n");
}

int allocateBlocks()
{
    if (freeListHead == NULL)
    {
        return -1;
    }

    int index = freeListHead->index;
    struct FreeBlock *tempNode = freeListHead;
    freeListHead = freeListHead->next;
    if (freeListHead)
    {
        freeListHead->prev = NULL;
    }
    free(tempNode);
    return index;
}

void freeBlocks(int index)
{
    struct FreeBlock *node = (struct FreeBlock *)malloc(sizeof(struct FreeBlock));
    node->index = index;
    node->next = NULL;
    node->prev = NULL;

    if (freeListHead == NULL)
    {
        freeListHead = node;
        return;
    }

    struct FreeBlock *tempNode = freeListHead;
    while (tempNode->next != NULL)
    {
        tempNode = tempNode->next;
    }
    tempNode->next = node;
    node->prev = tempNode;
}

struct FileNode
{
    char name[20];
    int isDirectory;
    int blockIndex;
    struct FileNode *child;
    struct FileNode *next;
    struct FileNode *parent;
};

struct FileNode root;
struct FileNode *cwd;

void initializeRoot()
{
    strcpy(root.name, "/");
    root.isDirectory = 1;
    root.blockIndex = -1;
    root.next = NULL;
    root.child = NULL;
    root.parent = NULL;
    cwd = &root;

    printf("Root directory created \n");
}

void createDirectory(struct FileNode *parent, char *folderName)
{
    struct FileNode *newDir = (struct FileNode *)malloc(sizeof(struct FileNode));
    strcpy(newDir->name, folderName);
    newDir->isDirectory = 1;
    newDir->blockIndex = -1;
    newDir->child = NULL;
    newDir->next = NULL;
    newDir->parent = parent;

    if (parent->child == NULL)
    {
        parent->child = newDir;
        newDir->next = newDir;
    }
    else
    {
        struct FileNode *tempNode = parent->child;
        while (tempNode->next != parent->child)
        {
            tempNode = tempNode->next;
        }
        tempNode->next = newDir;
        newDir->next = parent->child;
    }
    printf("Directory %s created inside %s.\n", folderName, parent->name);
}

void createFile(struct FileNode *parent, char *fileName)
{
    int block = allocateBlocks();
    if (block == -1)
    {
        printf("No free disk blocks\n");
        return;
    }

    struct FileNode *newFile = (struct FileNode *)malloc(sizeof(struct FileNode));
    strcpy(newFile->name, fileName);
    newFile->isDirectory = 0;
    newFile->blockIndex = block;
    newFile->child = NULL;
    newFile->next = NULL;
    newFile->parent = parent;

    if (parent->child == NULL)
    {
        parent->child = newFile;
        newFile->next = newFile;
    }
    else
    {
        struct FileNode *tempNode = parent->child;
        while (tempNode->next != parent->child)
        {
            tempNode = tempNode->next;
        }
        tempNode->next = newFile;
        newFile->next = parent->child;
    }
    // freeBlock[block] = 1;
    printf("File %s created inside %s using block %d.\n", fileName, parent->name, block);
}

void listDirectory(struct FileNode *dir)
{
    if (dir->child == NULL)
    {
        printf("%s is empty.\n", dir->name);
        return;
    }

    printf("Contents of %s\n", dir->name);
    struct FileNode *tempNode = dir->child;
    do
    {
        if (tempNode->isDirectory)
        {
            printf("[DIR] %s\n", tempNode->name);
        }
        else
        {
            printf("[FILE] %s\n", tempNode->name);
        }
        tempNode = tempNode->next;

    } while (tempNode != dir->child);
}

void deleteFile(struct FileNode *parent, char *fileName)
{
    if (parent->child == NULL)
    {
        printf("No files here\n");
        return;
    }
    struct FileNode *curr = parent->child;
    struct FileNode *prev = NULL;
    do
    {
        if (!curr->isDirectory && strcmp(curr->name, fileName) == 0)
        {
            if (curr == parent->child && curr->next == curr)
                parent->child = NULL;
            else
            {
                struct FileNode *tempNode = parent->child;
                while (tempNode->next != curr)
                    tempNode = tempNode->next;
                tempNode->next = curr->next;
                if (curr == parent->child)
                    parent->child = curr->next;
            }
            freeBlocks(curr->blockIndex);
            free(curr);
            printf("File '%s' deleted successfully.\n", fileName);
            return;
        }
        curr = curr->next;
    } while (curr != parent->child);
    printf("File %s is not found in %s folder\n", fileName, parent->name);
}

void deleteDirectory(struct FileNode *parent, char *folderName)
{
    if (parent->child == NULL)
    {
        printf("No directories here\n");
        return;
    }
    struct FileNode *curr = parent->child;
    do
    {
        if (curr->isDirectory && strcmp(curr->name, folderName) == 0)
        {
            if (curr->child != NULL)
            {
                printf("Cannot delete '%s' — folder not empty.\n", folderName);
                return;
            }

            if (curr == parent->child && curr->next == curr)
                parent->child = NULL;
            else
            {
                struct FileNode *tempNode = parent->child;
                while (tempNode->next != curr)
                    tempNode = tempNode->next;
                tempNode->next = curr->next;
                if (curr == parent->child)
                    parent->child = curr->next;
            }
            free(curr);
            printf("Directory '%s' removed successfully.\n", folderName);
            return;
        }
        curr = curr->next;
    } while (curr != parent->child);

    printf("Folder %s not found in %s", folderName, parent->name);
}

void writeFile(struct FileNode *file, char *data)
{
    if (file->isDirectory)
    {
        printf("Cannot write data in a folder\n");
        return;
    }

    int block = file->blockIndex;
    strncpy(virtualDisk[block], data, BLOCK_SIZE - 1);
    virtualDisk[block][BLOCK_SIZE - 1] = '\0';

    printf("Data written to %s: %s\n", file->name, virtualDisk[block]);
}

void readFile(struct FileNode *file)
{
    if (file->isDirectory)
    {
        printf("Cannot read data from a folder\n");
        return;
    }
    int block = file->blockIndex;

    printf("Reading %s : %s\n", file->name, virtualDisk[block]);
}

void changeDirectory(char *folderName)
{
    if (strcmp(folderName, "..") == 0)
    {
        if (cwd->parent != NULL)
        {
            cwd = cwd->parent;
            printf("Moved to parent directory: \n");
        }
        else
        {
            printf("Already in root directory:\n");
        }
        return;
    }

    struct FileNode *tempNode = cwd->child;
    do
    {
        if (tempNode->isDirectory && strcmp(tempNode->name, folderName) == 0)
        {
            cwd = tempNode;
            printf("Changed directory to %s\n", cwd->name);
            return;
        }
        tempNode = tempNode->next;
    } while (tempNode != cwd->child);

    printf("Folder %s not found.\n", folderName);
}

void printWorkingDirectory(struct FileNode *dir)
{
    if (dir->parent == NULL)
    {
        printf("/");
        return;
    }
    printWorkingDirectory(dir->parent);
    printf("%s/", dir->name);
}

int main()
{

    initializeFreeBlocks();
    initializeRoot();

    char command[20], name[20], data[100];

    printf("\n--- Virtual File System (Linux-like) ---\n");
    printf("Commands: mkdir, create, ls, rm, rmdir, cd, pwd, write, read, exit\n");

    while (1)
    {
        printf("\n%s>", cwd->name);
        scanf("%s", command);

        if (strcmp(command, "mkdir") == 0)
        {
            scanf("%s", name);
            createDirectory(cwd, name);
        }
        else if (strcmp(command, "create") == 0)
        {
            scanf("%s", name);
            createFile(cwd, name);
        }
        else if (strcmp(command, "ls") == 0)
        {
            listDirectory(cwd);
        }
        else if (strcmp(command, "rm") == 0)
        {
            scanf("%s", name);
            deleteFile(cwd, name);
        }
        else if (strcmp(command, "rmdir") == 0)
        {
            scanf("%s", name);
            deleteDirectory(cwd, name);
        }
        else if (strcmp(command, "cd") == 0)
        {
            scanf("%s", name);
            changeDirectory(name);
        }
        else if (strcmp(command, "write") == 0)
        {
            scanf("%s", name);
            struct FileNode *tempNode = cwd->child;
            do
            {
                if (!tempNode->isDirectory && strcmp(tempNode->name, name) == 0)
                {
                    printf("Enter data: ");
                    scanf(" %[^\n]", data);
                    writeFile(tempNode, data);
                    break;
                }
                tempNode = tempNode->next;
            } while (tempNode != cwd->child);
            if (tempNode == NULL)
            {
                printf("File not found\n");
            }
        }
        else if (strcmp(command, "read") == 0)
        {
            scanf("%s", name);
            struct FileNode *tempNode = cwd->child;
            do
            {
                if (!tempNode->isDirectory && strcmp(tempNode->name, name) == 0)
                {
                    readFile(tempNode);
                    break;
                }
                tempNode = tempNode->next;
            } while (tempNode != cwd->child);
            if (tempNode == NULL)
            {
                printf("File not found\n");
            }
        }
        else if (strcmp(command, "pwd") == 0)
        {
            printWorkingDirectory(cwd);
            printf("\n");
        }
        else if (strcmp(command, "exit") == 0)
        {
            printf("Exiting Virtual File System...\n");
            break;
        }

        else
        {
            printf("Unknown command: %s\n", command);
        }
    }
}