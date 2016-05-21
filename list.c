// A general Program in C programming language to demonstrate insertions and deletions in Linked List.

#include <stdio.h>
#include <stdlib.h>

// A linked list containing integer values.
struct node {
    int data;
    struct node* next;
};


void insert_at_beginning(struct node** head, int element) {

    // Insert an element at the beginning of the linked list.
    struct node* temp = (struct node*) malloc(sizeof(struct node*));
    temp -> data = element;
    temp -> next = *head;
    *head = temp;
}


void insert_at(struct node** head, int element, int position) {

    /* Insert an element in the list at the given index.
       Indexing is assumed to start with 1, i.e., the first element is at index 1. */

    struct node* temp = *head;
    struct node* new_temp = (struct node*) malloc(sizeof(struct node*));

    new_temp -> data = element;
    new_temp -> next = NULL;

    // Indexing starts with 1.
    if(position < 1) {
        printf("Index starts with 1. Please try again.\n");
        return;
    }

    // Special case for the insertion at the first position.
    if(position == 1) {
        new_temp -> next = temp;
        *head = new_temp;
        return;
    }

    for(int i = 1; i <= position - 2; i++) {
        if(temp == NULL) {
            printf("Invalid Index. Please try again\n");
            return;
        }
        temp = temp -> next;
    }

    if(temp == NULL) {
        printf("Invalid Index. Please try again\n");
        return;
    }

    new_temp -> next = temp -> next;
    temp -> next = new_temp;

}

void insert(struct node** head, int element) {

    // Insert an element at the end of the linked list.

    struct node* traverse = *head;
    struct node* temp = (struct node*) malloc(sizeof(struct node*));
    temp -> data = element;
    temp -> next = NULL;

    // If the linked list is empty, make it the first element by pointing head to it.
    if(*head == NULL) {
        *head = temp;
        return;
    }

    // Else, traverse to the last element of the linked list and change its pointer from NULL to temp.
    while(traverse -> next != NULL)
        traverse = traverse -> next;
    traverse -> next = temp;
}

void delete_at(struct node** head, int position) {

    /* Delete an element at the given position from the linked list.
       Indexing is assumed to start with 1, i.e., the first element of the linked list is at index 1. */

    struct node* temp = *head;

    // Indexing starts with 1.
    if(position < 1) {
        printf("Index starts with 1. Please try again.\n");
        return;
    }

    // Special Case for deletion of first node.
    if(position == 1) {
        if(*head == NULL) {
            printf("List is empty.\n");
            return;
        }
        *head = temp -> next;
        free(temp);
        return;
    }

    struct node* traverse = *head;
    for(int i = 1; i <= position - 2; i++) {
        if(traverse == NULL) {
            printf("Invalid Index. Please try again.\n");
            return;
        }
        traverse = traverse -> next;
    }
    if(traverse == NULL || traverse -> next == NULL) {
        printf("Invalid Index. Please try again.\n");
        return;
    }

    temp = traverse -> next;
    traverse -> next = temp -> next;
    free(temp);
}

void print(struct node** head) {

    // Prints all the elements present in the linked list starting from head.

    if(*head == NULL) {
        printf("List is empty.\n\n");
        return;
    }

    printf("Elements of List are: ");
    struct node* temp = *head;
    while(temp != NULL) {
        printf("%d ", temp -> data);
        temp = temp -> next;
    }
    printf("\n\n");
}

void menu(struct node** head) {

    // Prints the menu infinite times until the user chooses to exit.

    int n, element, i, position, choice;
    int run = 1;
    while(run) {

        printf("----MENU----\n");
        printf("1. Insert at end.\n");
        printf("2. Insert at beginning.\n");
        printf("3. Insert at an index.\n");
        printf("4. Delete at an index.\n");
        printf("5. Print the contents.\n");
        printf("6. Exit.\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: printf("Enter an element: ");
                    scanf("%d", &element);
                    insert(head, element);
                    print(head);
                    break;

            case 2: printf("Enter an element: ");
                    scanf("%d", &element);
                    insert_at_beginning(head, element);
                    print(head);
                    break;

            case 3: printf("Enter an element and index: ");
                    scanf("%d %d", &element, &position);
                    insert_at(head, element, position);
                    print(head);
                    break;

            case 4: printf("Enter an index: ");
                    scanf("%d", &position);
                    delete_at(head, position);
                    print(head);
                    break;

            case 5: print(head);
                    break;

            case 6: run = 0;
                    break;

            default: printf("Wrong Choice. Please try again.\n");
        }
    }
}

int main() {

    // initialize head to NULL to signify empty list
    struct node* head = NULL;

    // Menu driven program.
    menu(&head);
    return 0;
}
