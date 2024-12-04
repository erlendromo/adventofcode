#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int value;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int value) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

struct Tree {
    struct Node* root;
};

struct Tree* createTree() {
    struct Tree* tree = (struct Tree*)malloc(sizeof(struct Tree));
    tree->root = NULL;
    return tree;
}

void insert(struct Tree* tree, int value) {
    struct Node* newNode = createNode(value);

    if (tree->root == NULL) {
        tree->root = newNode;
        return;
    }

    struct Node* current = tree->root;
    struct Node* parent = NULL;

    while (1) {
        parent = current;

        if (value < current->value) {
            current = current->left;

            if (current == NULL) {
                parent->left = newNode;
                return;
            }
        } else {
            current = current->right;

            if (current == NULL) {
                parent->right = newNode;
                return;
            }
        }
    }
}

struct Tree* readAndPopulate(char filename[]) {
    struct Tree* tree = createTree();

    FILE *fptr;
    fptr = fopen(filename, "r");

    if (fptr == NULL) {
        printf("Error opening file");
        return tree;
    }

    char line[256];
    while (fgets(line, sizeof(line), fptr)) {
        int value = atoi(line);
        insert(tree, value);
    }

    fclose(fptr);

    return tree;
}

void minToMaxInTree(struct Node* current) {
    if (current == NULL) {
        return;
    }

    minToMaxInTree(current->left);
    printf("%d\n", current->value);
    minToMaxInTree(current->right);
}

int calcDistance(int* llist, int* rlist) {
    int distance = 0;
    for (int i = 0; i < 1000; i++) {
        distance += abs(llist[i] - rlist[i]);
    }

    return distance;
}

int calcSimilarityScore(int* llist, int* rlist) {
    int similarity = 0;

    for (int i = 0; i < 1000; i++) {
        int number = llist[i];
        int numberOccurences = 0;
        for (int j = 0; j < 1000; j++) {
            if (number == rlist[j]) {
                numberOccurences++;
            }
        }

        similarity += (number * numberOccurences);
    }

    return similarity;
}


int main() {
    int llist[1000];
    int rlist[1000];

    FILE *lfptr = fopen("leftinputsorted.txt", "r");
    FILE *rfptr = fopen("rightinputsorted.txt", "r");
    char lstr[1000];
    char rstr[1000];

    int i = 0;
    while (fgets(lstr, 1000, lfptr)) {
        llist[i] = atoi(lstr);
        i++;
    }

    i = 0;
    while (fgets(rstr, 1000, rfptr)) {
        rlist[i] = atoi(rstr);
        i++;
    }

    fclose(lfptr);
    fclose(rfptr);

    printf("Distance: %d\n", calcDistance(llist, rlist));
    printf("Similarity score: %d\n", calcSimilarityScore(llist, rlist));

    return 0;
}
