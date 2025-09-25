#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char* data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} Linkedlist;

void insertAtBeginning(Linkedlist* LL, char ele[]) {
    // Create a new node containing element "ele"
    Node* node = (Node*) malloc(sizeof(Node));
    node->data = ele;

    // Append node to start of Linkedlist
    if (LL->head == NULL) { // Empty LL
        LL->head = node;
    } else { // Existing LL
        node->next = LL->head;
        LL->head = node;
    }
}

void insertAtTheEnd(Linkedlist* LL, char ele[]) {
    // Create a new node containing element "ele"
    Node* node = (Node*) malloc(sizeof(Node));
    node->data = ele;

    // Append node to end of Linkedlist
    // TODO
}

void deleteNode(Linkedlist* LL, char ele[]) {

}

// Return 1 if node is found and 0 if not
int findNode(Linkedlist* LL, char ele[]) {

}

void displayLinkedList(Linkedlist* LL) {
    Node* curNode = LL->head;
    while (curNode != NULL) {
        printf("%s, ", curNode->data);
        curNode = curNode->next;
    }
    printf("\n");
}

int main (int argc, char *argv[]) {
    Linkedlist* LL = (Linkedlist*) malloc(sizeof(Linkedlist));
    LL->head = NULL;

    insertAtBeginning(LL, "Hello");
    insertAtTheEnd(LL, "World");
    insertAtTheEnd(LL, "from");
    insertAtTheEnd(LL, "Linked");
    insertAtTheEnd(LL, "List");

    displayLinkedList(LL);

    deleteNode(LL, "from");
    displayLinkedList(LL);

    if (findNode(LL, "World")) {
        printf("Node found\n");
    } else {
        printf("Node not found\n");
    }

    return 0;
}