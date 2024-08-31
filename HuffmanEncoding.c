#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    char letter;
    int freq;
    struct Node *left;
    struct Node *right;
} Node;

Node *convert_to_Node(char letter, int freq) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->letter = letter;
    newNode->freq = freq;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void bubble_sort(Node **arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j]->freq > arr[j + 1]->freq) {
                Node *temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

Node *join_Node(Node *node1, Node *node2) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->letter = '\0';
    newNode->freq = node1->freq + node2->freq;
    newNode->left = node1;
    newNode->right = node2;
    return newNode;
}

int main() {
    printf("Enter the number of alphabets: ");
    int num = 0;
    scanf("%d", &num);

    char *alphabets = (char *)malloc(sizeof(char) * num);
    int *frequencies = (int *)malloc(sizeof(int) * num);

    getchar();

    printf("Enter the alphabets: ");
    for (int i = 0; i < num; i++) {
        scanf("%c", &alphabets[i]);
        getchar();
    }

    printf("Enter the frequencies: ");
    for (int i = 0; i < num; i++) {
        scanf("%d", &frequencies[i]);
    }

    Node **nodes = (Node **)malloc(sizeof(Node *) * num);
    for (int i = 0; i < num; i++) {
        nodes[i] = convert_to_Node(alphabets[i], frequencies[i]);
    }

    bubble_sort(nodes, num);

    printf("Sorted frequencies: ");
    for (int i = 0; i < num; i++) {
        printf("%d, ", nodes[i]->freq);
    }
    printf("\n");

    //----------------------------------------------
    free(alphabets);
    free(frequencies);
    for (int i = 0; i < num; i++) {
        free(nodes[i]);
    }
    free(nodes);

    return 0;
}
