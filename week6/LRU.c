#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 100
#define HASH_SIZE 1000   


struct Node {
    int key;
    char data[MAX_STRING];

    struct Node *prev;
    struct Node *next;
};


struct LRUCache {
    int capacity;
    int count;

    struct Node *head;   
    struct Node *tail;   

    struct Node* hashmap[HASH_SIZE];
};

struct LRUCache *cache = NULL;

void insertAtHead(struct LRUCache *cache, struct Node *node) {
    node->prev = NULL;
    node->next = cache->head;

    if (cache->head != NULL)
        cache->head->prev = node;

    cache->head = node;

    if (cache->tail == NULL)
        cache->tail = node;
}

void removeNode(struct LRUCache *cache, struct Node *node) {
    if (node->prev != NULL)
        node->prev->next = node->next;
    else
        cache->head = node->next;

    if (node->next != NULL)
        node->next->prev = node->prev;
    else
        cache->tail = node->prev;
}

void createCache(int capacity) {
    cache = (struct LRUCache *)malloc(sizeof(struct LRUCache));
    cache->capacity = capacity;
    cache->count = 0;
    cache->head = NULL;
    cache->tail = NULL;

    for (int i = 0; i < HASH_SIZE; i++)
        cache->hashmap[i] = NULL;
}

char* get(int key) {
    if (cache->hashmap[key] == NULL) {
        printf("NULL\n");
        return NULL;
    }

    struct Node *node = cache->hashmap[key];

    removeNode(cache, node);
    insertAtHead(cache, node);

    printf("%s\n", node->data);
    return node->data;
}

void put(int key, char *value) {

    if (cache->hashmap[key] != NULL) {
        struct Node *node = cache->hashmap[key];
        strcpy(node->data, value);

        removeNode(cache, node);
        insertAtHead(cache, node);
        return;
    }

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->key = key;
    strcpy(newNode->data, value);
    newNode->prev = newNode->next = NULL;


    if (cache->count == cache->capacity) {
        struct Node *lru = cache->tail;

        cache->hashmap[lru->key] = NULL;
        removeNode(cache, lru);
        free(lru);

        cache->count--;
    }

    insertAtHead(cache, newNode);
    cache->hashmap[key] = newNode;
    cache->count++;
}

int main() {
    char command[50];

    while (scanf("%s", command) != EOF) {
        if (strcmp(command, "createCache") == 0) {
            int size;
            scanf("%d", &size);
            createCache(size);
        }
        else if (strcmp(command, "put") == 0) {
            int key;
            char value[MAX_STRING];
            scanf("%d %s", &key, value);
            put(key, value);
        }
        else if (strcmp(command, "get") == 0) {
            int key;
            scanf("%d", &key);
            get(key);
        }
        else if (strcmp(command, "exit") == 0) {
            break;
        }
    }

    return 0;
}