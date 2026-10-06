#pragma once

struct ListNode {
	int data;
	struct ListNode *next;
};

struct ListNode *createNode(int data);
void display(struct ListNode *head);
void search(struct ListNode *head, int value);
struct ListNode *insertAnywhere(struct ListNode *head, int value, int position);
struct ListNode *deleteNode(struct ListNode *head, int value);
