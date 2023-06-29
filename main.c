#include <stdio.h>
#include <stdlib.h>
typedef struct{
    void *next; // pointer to the next node in the list
    int data; // data stored in the node
} Node;// this represent a single node in the list

Node *head = NULL; // this is the head of the list

//to add a node to the list
Node *addNode(int data)//returns the address of the added node
{
    Node *new = NULL;
    /*if head is null allocate a node and point head to this node
    else
        allocate a node and point the next of the last node to this node
    if you add a node to the end of the list, you need to traverse the list to find the last node
    and this costs O(n) time when n is the number of nodes in the list
    so it is better to add a node to the beginning of the list
    How to do this? 
    just allocate a new node and point the next of this node to the head and point the head to this node
                head
    *head--/-- First node
        |          |
        |-- Second node
    So its just cost O(1) time and does not depend on the number of nodes in the list
    */
   if (head == NULL)
   {
        Node *new = malloc(sizeof(Node));//allocate a new node and return the address of the node
        if (new == NULL)
        {
            printf("Error: Memory allocation failed\n");
            return NULL;
        }
        new->data = data;//set the data of the node
        head = new;//point the head to the new node
        new->next = NULL;//set the next of the new node to NULL(because we don't have a next node)       
   }else
   {
        Node *new = malloc(sizeof(Node));//allocate a new node and return the address of the node
        if (new == NULL)
        {
            printf("Error: Memory allocation failed\n");
            return NULL;
        }
        new->data = data;//set the data of the node
        new->next = head;//point the next of the new node to the head(point the same node that head is pointing to)
        head = new;//point the head to the new node(remove the old head that points to the first node and point the head to the new node)
   }
   return new;
   

}

//to remove a node from the list
/*      head
*head -> 1 -> 2 -> 3 if we want to remove element 2
*head -> 1 /2/ -> 3
         |________|

track the prevuious pointer and make it point to the next of the node to be deleted
than free the node to be deleted
*But if current node is the head node, we need to make the head point to the next of the current node
*/
int removeNode(int data)
{
    Node *current = head;//current is a pointer to the current node
    Node *prev = head;//prev is a pointer to the previous node
    while (current!=NULL){
        //find the first node equal to the data
        if (current->data == data){
            if (current== head){
                //if current node is the list head
                head = current -> next;
                free(current);
                current = NULL;
            }else
            {
                prev->next = current->next;
                free(current);
                current = NULL;
            }
            return 1;//return 1 if the node is found and deleted
            
        }
        prev = current;
        current = current->next;
    }
    return 0;//return 0 if the node is not found
}

//insert a node into a position in the list
/*          head
    *head -> 1 -> 2 -> 3 if we want to insert element 4 after element 2 what shold we do??
    *head -> 1 -> 2 -/> 3  point the next of 4 to 3 and point the next of 2 to 4 
                  |__4__|
*/
Node *insertNode(int data , int position){
    Node *current = head;//current is a pointer to the current node
    while (current !=NULL && position != 0)
    {
        
        position--;
    }
    if (position != 0)
    {
        printf("Error: Invalid position, too far into list \n");
        return NULL;
    }
    Node *new = malloc(sizeof(Node));//allocate a new node and return the address of the node
    if (new == NULL)
    {
        printf("Error: Memory allocation failed\n");
        return NULL;
    }
    new->data = data;//set the data of the node
    new->next = current->next;//point the next of the new node to the next of the current node
    current->next = new;//point the next of the current node to the new node
    return new;
}
//print operation
void printList()
{
    Node *current = head;
    while (current != NULL)
    {
        printf("%d->", current->data);
        current = current->next;
    }
    printf("\n");;
}

void printMenu()
{
    printf("You have the following options:\n");
    printf("\t1. Add a node to the list\n");
    printf("\t2. Remove a node from the list\n");
    printf("\t3. Insert a node into a position in the list\n");
    printf("\t4. Print your list\n");
    printf("\t5. Quit\n");
    return;
}

int main(int argc, char **argv) {
    int option = -1;
    int arg = 0;
    int arg2 = 0;
    while (option != 5)
    {
        printMenu();
        int num_received = scanf("%d", &option);// returns the number of items received
        if (num_received == 1 && option>0 && option <=4)
        {
            switch (option)
            {
            case 1:
                //add operation
                printf("Enter the data you want to add to the list\n");
                scanf("%d", &arg);
                Node *new = addNode(arg);
                break;
            case 2:
                //remove operation
                printf("Enter the data you want to remove from the list\n");
                scanf("%d", &arg);
                int success = removeNode(arg);
                if (!success)
                {
                    printf("Element not found\n");
                }
                
                break;
            case 3:
                //insert operation
                printf("Enter the data you want to insert to the list\n");
                scanf("%d", &arg);
                printf("Enter the positon\n");
                scanf("%d", &arg2);
                new = insertNode(option, arg2);
                if (new == NULL)
                    printf("Failed to insert into list\n");
                break;
            case 4:
                //print operation
                printList();
                break;
                
            case 5:
                break;
            
            default:
                break;
            }
        }
    }
    
    return 0;
}