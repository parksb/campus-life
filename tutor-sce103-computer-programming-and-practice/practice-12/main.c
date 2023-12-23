#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  char data;
  struct node *next;
} Node;

void push(Node** top, const char item);
char pop(Node** top);
void printStack(Node* top);

int main() {
  char data[] = "Ajou University";
  char val;
  Node *top;

  top = NULL;

  for (int i = 0; i < 15; i++) {
    push(&top, data[14-i]);
    printStack(top);
  }

  for (int i = 0; i < 15; i++) {
    val = pop(&top);
    printStack(top);
  }

  return 0;
}

void push(Node** top, const char item) {
  Node* temp = (Node*)malloc(sizeof(Node));

  temp->data = item;
  temp->next = *top;
  *top = temp;
}

char pop(Node** top) {
  Node* temp;
  char item;

  if (top == NULL) {
    exit(1);
  }

  temp = *top;
  item = temp->data;
  *top = temp->next;
  free(temp);

  return item;
}

void printStack(Node* top) {
  Node* temp = top;

  printf("Stack: ");
  while (temp != NULL) {
    printf("%c", temp->data);
    temp = temp->next;
  }
  printf("\n");
}
