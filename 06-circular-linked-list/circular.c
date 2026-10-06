// circular linked list insert delete search display

#include <stdio.h>
#include <stdlib.h>
#include "circular.h"

struct ListNode *createNode(int data) {
    struct ListNode *n = (struct ListNode *)malloc(sizeof(struct ListNode));
    n->data = data;
    n->next = n;
    return n;
}

void display(struct ListNode *head){
	if(head == NULL){
		printf("List is empty");
		return;
	}
	struct ListNode *temp = head;
	do {
		printf("%d -> ", temp->data);
		temp = temp->next;
	}
	while(temp != head);
	printf("(back to %d)\n", head->data);
}

void search(struct ListNode *head, int value) {
	if(head == NULL){
		printf("List is empty\n");
		return;
	}
	struct ListNode *temp = head;
	do {
		if(temp->data == value){
			printf("Value %d found in the list\n", value);
			return;
		}
		temp = temp->next;
	} while(temp != head);
	printf("Value %d not found in the list\n", value);
}

struct ListNode *insertAnywhere(struct ListNode *head, int value, int position) {
	struct ListNode *newNode = createNode(value);
	if(position == 0){
		if(head == NULL){
			return newNode;
		}
		struct ListNode *last = head;
		while(last->next != head){
			last = last->next;
		}
		last->next = newNode;
		newNode->next = head;
		return newNode; // new head
	}
	struct ListNode *temp = head;
	for(int i=0; i<position-1 && temp->next != head; i++){
		temp = temp->next;
	}
	newNode->next = temp->next;
	temp->next = newNode;
	return head;
}


struct ListNode *deleteNode(struct ListNode *head, int value) {
	if(head == NULL){
		printf("List is empty\n");
		return NULL;
	}
	struct ListNode *temp = head;
	struct ListNode *prev = NULL;
	do {
		if(temp->data == value){
			if(prev == NULL){ // deleting head
				struct ListNode *last = head;
				while(last->next != head){
					last = last->next;
				}
				if(last == head){ // only one node
					free(head);
					return NULL;
				}
				last->next = head->next;
				struct ListNode *newHead = head->next;
				free(head);
				return newHead;
			} else {
				prev->next = temp->next;
				free(temp);
				return head;
			}
		}
		prev = temp;
		temp = temp->next;
	} while(temp != head);
	printf("Value %d not found in the list\n", value);
	return head;
}

int main() {
	struct ListNode *head = NULL;
	head = createNode(10);
	head->next = createNode(20);
	head->next->next = createNode(30);
	head->next->next->next = head;

	int c;
	while(1) {
		printf("1. Display\n2. Search\n3. Insert\n4. Delete\n");
		printf("Enter your choice: ");
		scanf("%d", &c);
		switch(c){
			case 1:
				display(head);
				break;
			case 2:
				search(head, 20);
				break;
			case 3:
				head = insertAnywhere(head, 15, 1);
				display(head);
				break;
			case 4:
				head = deleteNode(head, 20);
				display(head);
				break;
			default:
				printf("Invalid choice\n");
		}
	}
	return 0;
}