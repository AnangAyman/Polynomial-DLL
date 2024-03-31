#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node {
    int exponent;
    int coefficient;
    struct Node *next;
    struct Node *prev;
} Node;

Node *head, *tail;

Node *createNode(int coefficient, int exponent){
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->exponent = exponent;
    newNode->coefficient = coefficient;
    newNode->next = NULL;
    newNode->prev = NULL;

    return newNode;
}

// ------------------------------ Printing / Inputing Functions --------------------------------------
//* Print equation
void printEquation(){
    Node *temp = head;
    if (temp == NULL){
        printf("No Equation!\n");
    } else {
        // Print the first element since it wont have a "+" or a "-" sign
        printf("%dx%d", temp -> coefficient, temp -> exponent);
        temp = temp -> next;
        
        // Print the rest
        while(temp != NULL){
            if ((temp -> coefficient) > 0){
                printf("+");
            }
            printf("%dx%d", temp -> coefficient, temp -> exponent);
            
            temp = temp -> next;
        }
        printf("\n");
    }


}

//* Print Menu
void printMenu(){
    printf("1. Insert New Term\n");
    printf("2. Delete Existing Term Based On Exponent\n");
    printf("3. Quit\n");
}

int userOption(){
    int option;
    printf(">> ");
    scanf("%d", &option);
    return option;
}

void clearTerminal(){
    
    char enter;
    getchar();
    printf("Please press Enter to continue...");
    scanf("%c", &enter);
    // Somehow windows's and mac OS's version of clearing is different so I include both
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
        system("clear");
}



// ------------------------------- Insertion And Deletion --------------------------------
//* Insert

void insert(int coefficient, int exponent){
    Node *newNode = createNode(coefficient, exponent);

    if (head == NULL){
        head = tail = newNode;
        head->prev = NULL;
        head->next = NULL;
        tail->prev = NULL;
        tail->next = NULL;

    } else {
        
        if (exponent >= (head->exponent)){
            head -> prev = newNode;
            newNode -> next = head;
            newNode -> prev = NULL;
            head = newNode;
        } else if (exponent < (tail->exponent)){
            tail->next = newNode;
            newNode -> prev = tail;
            newNode -> next = NULL;
            tail = newNode;
        } else {
            Node *temp = head;
            // Iterate through the list
            while (temp->next != NULL && exponent < (temp -> next -> exponent)){
                temp = temp->next;
            }

            newNode -> next = temp-> next;
            newNode -> prev = temp;
            temp -> next -> prev = newNode;
            temp -> next = newNode;   
        }
    }
}

void remove(int exponent){
    Node *temp;
    temp = head;

    if (head == NULL){
        printf("No Data!!!\n");
        return;
    } else if (head -> exponent == exponent){
        if (head -> next == NULL){ // Deleting the last element
            head = tail = NULL;
            free(temp);
        } else { // Deleting the head but not the last element of the equation
            head = head -> next;
            head-> prev = NULL;
            free(temp);
        }

    } else if (tail -> exponent == exponent){
        temp = tail;
        tail = tail -> prev;
        tail-> next = NULL;
        free(temp);
    } else {
        while (temp->next != NULL && temp->next->exponent != exponent) {
            temp = temp->next;
        }

        if (temp->next == NULL) {
            printf("Not Found!!!\n");
            return;
        }

        Node *target = temp -> next;

        temp -> next = target -> next;
        target -> next -> prev = target -> prev;
        free(target);
    }
}

// ---------------------------------------- Main ---------------------------------------------
int main(){
    int option = 0;
    do {
        printEquation();
        printMenu();
        option = userOption();
        int coefficient,exponent =0;

        switch(option) {
            case 1:
                printf("Insert coefficient >> ");
                scanf("%d", &coefficient);
                printf("Insert exponent >> ");
                scanf("%d", &exponent);

                insert(coefficient, exponent);
                break;
            case 2:
                printf("Insert exponent >> ");
                scanf("%d", &exponent);
                remove(exponent);  
                break;
            
            case 3:
                printf("Thank you for using the program\n");
                return 0;

            default:
                printf("Please choose a valid option!\n");
                break;
        }

        clearTerminal();
    } while (option != 3);
}