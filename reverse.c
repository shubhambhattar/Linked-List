// A program to reverse the linked list.

#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
};

void insert(struct node **head, int element) {

    // Insert the elements at the end of the linked list.

    struct node* temp = (struct node*) malloc(sizeof(struct node*));
    temp -> data = element;
    temp -> next = NULL;

    if(*head == NULL) {
        *head = temp;
        return;
    }

    struct node* traverse = *head;
    while(traverse -> next != NULL)
        traverse = traverse -> next;
    traverse -> next = temp;
}

void reverse(struct node** head) {

    // Reverse the linked list.

    struct node* prev = NULL;
    struct node* current = *head;
    struct node* link;

    while(current != NULL) {

        link = current -> next;
        current -> next = prev;
        prev = current;
        current = link;
    }

    *head = prev;
}

void print(struct node *head) {

    // Print the contents of the linked list.

    while(head != NULL) {
        printf("%d ", head -> data);
        head = head -> next;
    }
    printf("\n\n");
}

int main() {

    struct node* head = NULL;

    int n, element;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    printf("Enter the elements:\n");
    for(int i = 0; i < n; i++) {
        scanf("%d", &element);
        insert(&head, element);
        print(head);
    }

    reverse(&head);
    print(head);
}