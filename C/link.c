#include<stdio.h>

//linked list structure
struct node{
  int data;
  struct node *next;
};

//insert a new node to link list
struct node *insertANewNodeInFront(struct node *head, struct node *newNode){
  newNode -> next = head;
  head = newNode;
  printf("New list printing\n");
  printLinkList(head);
  printf("New list printing finished");
  return head;
}

//reverse the link list
struct node* reverseLinkList(struct node *head){
  struct node* temp = NULL;
  struct node* previous = NULL;

  while(head -> next != NULL){
    temp = head -> next;
    head -> next = previous;
    previous = head;
    head = temp;
  }

  head -> next = previous;

  return head;
}

//main method .:)
void main(void){
  struct node *head   = (struct node*)malloc(sizeof(struct node));
  struct node *second = (struct node*)malloc(sizeof(struct node));
  struct node *third  = (struct node*)malloc(sizeof(struct node));
  struct node *zero   = (struct node*)malloc(sizeof(struct node));

  head -> data = 1;
  head -> next = second;

  second -> data = 2;
  second -> next = third;

  third -> data = 3;
  zero -> data  = 0;

  printLinkList(head);
  head = insertANewNodeInFront(head, zero);
  printLinkList(head);

  printf("reversed list? \n");
  head = reverseLinkList(head);

  printLinkList(head);
}

//print the list
void printLinkList(struct node *head){
  struct node *temp = head;
  while(temp!=NULL){
    printf("hello from list number %d\n", temp->data);
    temp = temp -> next;
  }
}
