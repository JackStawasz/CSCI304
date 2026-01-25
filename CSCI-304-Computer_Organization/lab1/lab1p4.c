#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Node Struct
*  Purpose: Contains data and a reference to the next Node to be used in a Linked List.
*  Members: char* data: The string of data to be stored.
*           Node* next: The reference to the next node in the Linked list. 
*/
typedef struct Node {
    char* data;
    struct Node* next;
} Node;

/* Linkedlist Struct
*  Purpose: Serves as the base and reference of the head to the Linked List.
*  Members: Node* head: The reference to the Node that is the start of the Linked List. 
*/
typedef struct {
    Node* head;
} Linkedlist;

/* insertAtBeginning Function
*  Purpose: Given a Linked List and a string, it creates a Node with the string and inserts it to the front of the Linked List.
*  Input: The data to be added to the Linked List and the Linked List we want to add the data to.
*  Output: None
*/
void insertAtBeginning(Linkedlist* LL, char ele[]) {
    // Create a new node containing element "ele"
    Node* node = (Node*) malloc(sizeof(Node));
    node->data = malloc((strlen(ele) + 1) * sizeof(char));
    strcpy(node->data, ele);
    
    // Append node to start of Linkedlist
    node->next = LL->head;
    LL->head = node;
    
    return;
}

/* insertAtTheEnd Function
*  Purpose: Given a Linked List and a string, it creates a Node with the string and inserts it to the back of the Linked List.
*  Input: The data to be added to the Linked List and the Linked List we want to add the data to.
*  Output: None
*/
void insertAtTheEnd(Linkedlist* LL, char ele[]) {
    // Create a new node containing element "ele"
    Node* node = (Node*) malloc(sizeof(Node));
    node->data = malloc((strlen(ele) + 1) * sizeof(char));
    strcpy(node->data, ele);
    node->next = NULL;

    // If the Linked List is empty, we can immediately set the node to the head.
    if (LL->head == NULL) {
        LL->head = node;
        return;
    }
    
    // Traverse the Linked List until we find the end, and then insert the desired node.
    Node *traversalNode = LL->head;
    while (traversalNode->next != NULL) {
        traversalNode = traversalNode->next;
    }
    traversalNode->next = node;
}

/* deleteNode Function
*  Purpose: Given a Linked List and a string, delete the Node in the Linked List with value of the string if it exists.
*  Input: The data to be removed to the Linked List and the Linked List we want remove the data from.
*  Output: None
*/
void deleteNode(Linkedlist* LL, char ele[]) {
    Node* curNode = LL->head;
    Node* prevNode = NULL;

    // Find deletion Node
    while (curNode != NULL) {
        if (strcmp(curNode->data, ele) == 0) {
            break;
        }
        prevNode = curNode;
        curNode = curNode->next;
    }

    // Exit if LL is empty or "ele" not found
    if (curNode == NULL) {
        return;
    }
    
    // Delete node
    if (prevNode == NULL) { // Head Node deletion
        LL->head = curNode->next;
    } else { // Non-head Node deletion
        prevNode->next = curNode->next;
    }

    // Free the memory of the deleted Node.
    free(curNode->data);
    free(curNode);
    return;
}

/* findNode Function
*  Purpose: Given a Linked List and a string, finds if a string exists within the Linked List.
*  Input: The data to be searched for and the Linked List to search.
*  Output: 1 if the element can be found, 0 otherwise.
*/
int findNode(Linkedlist LL, char ele[]) {
    Node *traversalNode = LL.head;
    // Travel the Linked List, stopping only when the desired Node is found or the end of the Linked List is reached.
    while (traversalNode != NULL) {
        if (strcmp(traversalNode->data, ele) == 0) {
            return 1;
        }
        traversalNode = traversalNode->next;
    }
    return 0;
}

/* displayLinkedList Function
*  Purpose: Given a Linked List , print a comma seperated list of all of its elements.
*  Input: The Linked List whose data to print.
*  Output: None
*/
void displayLinkedList(Linkedlist LL) {
    Node* curNode = LL.head;
    if (curNode == NULL) {
        return;
    }
    // Seperate case for the first element in case commas aren't needed.
    printf("%s", curNode->data);
    curNode = curNode->next;
    // For every following item, print its data preceded by a comma an space.
    while (curNode != NULL) {
        printf(", %s", curNode->data);
        curNode = curNode->next;
    }
    printf("\n");
}

/* main Function
*  Purpose: Controls program, reads a list of command line arguments, apply the necessary rules to add or delete elements from a Linked List, and print the result.
*  Input: The strings to be placed in a Linked List.
*  Output: None
*/
int main (int argc, char *argv[]) {
    // Check to make sure the correct amount of arguments were typed in.
    if (argc < 2) {
        printf("ERROR: The program must read at least an argument.\n");
        return EXIT_FAILURE;
    }
    Linkedlist *LL = malloc(sizeof(Linkedlist));
    LL->head = NULL;

    // For each argument, check if we need to delete, prepend, or append a Node.
    for (int i = 1; i < argc; i++) {
        if (findNode(*LL, argv[i]) == 1) {
            deleteNode(LL, argv[i]);
        }
        else if (isupper(argv[i][0])){
            insertAtBeginning(LL, argv[i]);
        }
        else {
            insertAtTheEnd(LL, argv[i]);
        }
    }
    // Print the resulting Linked List.
    printf("The list:- ");
    displayLinkedList(*LL);
    printf("\n");
    return EXIT_SUCCESS;
}