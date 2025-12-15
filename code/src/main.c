#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LEVEL 16
#define P 0.5

typedef struct SkipNode {
    int key;
    int level;
    struct SkipNode **forward;
} SkipNode;

typedef struct SkipList {
    int level;
    SkipNode *header;
} SkipList;

int random_level() {
    int lvl = 1;
    while (((double)rand() / RAND_MAX) < P && lvl < MAX_LEVEL)
        lvl++;
    return lvl;
}

SkipNode *create_node(int level, int key) {
    SkipNode *node = (SkipNode *)malloc(sizeof(SkipNode));
    node->key = key;
    node->level = level;
    node->forward = (SkipNode **)malloc(sizeof(SkipNode *) * level);
    for (int i = 0; i < level; i++)
        node->forward[i] = NULL;
    return node;
}

SkipList *create_skiplist() {
    SkipList *list = (SkipList *)malloc(sizeof(SkipList));
    list->level = 1;
    list->header = create_node(MAX_LEVEL, -1);
    return list;
}

SkipNode *search_node(SkipList *list, int key) {
    SkipNode *x = list->header;
    for (int i = list->level - 1; i >= 0; i--) {
        while (x->forward[i] && x->forward[i]->key < key)
            x = x->forward[i];
    }
    x = x->forward[0];
    if (x && x->key == key)
        return x;
    return NULL;
}

void insert(SkipList *list, int key) {
    SkipNode *update[MAX_LEVEL];
    SkipNode *x = list->header;

    for (int i = list->level - 1; i >= 0; i--) {
        while (x->forward[i] && x->forward[i]->key < key)
            x = x->forward[i];
        update[i] = x;
    }

    if (x->forward[0] && x->forward[0]->key == key) {
        printf("Insert key=%d ignored\n", key);
        return;
    }

    int lvl = random_level();
    if (lvl > list->level) {
        for (int i = list->level; i < lvl; i++)
            update[i] = list->header;
        list->level = lvl;
    }

    x = create_node(lvl, key);
    for (int i = 0; i < lvl; i++) {
        x->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = x;
    }

    printf("Insert key=%d level=%d\n", key, lvl);
}

void delete_key(SkipList *list, int key) {
    SkipNode *update[MAX_LEVEL];
    SkipNode *x = list->header;

    for (int i = list->level - 1; i >= 0; i--) {
        while (x->forward[i] && x->forward[i]->key < key)
            x = x->forward[i];
        update[i] = x;
    }

    x = x->forward[0];
    if (!x || x->key != key) {
        printf("Delete key=%d fail\n", key);
        return;
    }

    for (int i = 0; i < list->level; i++) {
        if (update[i]->forward[i] != x)
            break;
        update[i]->forward[i] = x->forward[i];
    }

    printf("Delete key=%d success\n", key);

    free(x->forward);
    free(x);

    while (list->level > 1 && list->header->forward[list->level - 1] == NULL)
        list->level--;
}

int main() {
    srand((unsigned int)time(NULL));
    SkipList *list = create_skiplist();

    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        char op;
        int key;
        scanf(" %c %d", &op, &key);

        if (op == 'I') {
            insert(list, key);
        } else if (op == 'D') {
            delete_key(list, key);
        } else if (op == 'S') {
            SkipNode *res = search_node(list, key);
            if (res)
                printf("Found key=%d level=%d\n", key, res->level);
            else
                printf("NotFound key=%d\n", key);
        }
    }
    return 0;
}
