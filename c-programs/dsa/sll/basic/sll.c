/*
 * File : sll.c
 *
 * Description: singly linked list c file
 *
 * author : Yupindra Kumar Balaji
 *
 */

#include "sll.h"

int main(void)
{
	SLL_DEBUG("%s:%d Entered\n", __func__, __LINE__);

	struct Node *head = sll_create_fillup_node(10);
	head->next = sll_create_fillup_node(20);
	head->next->next = sll_create_fillup_node(30);
	head->next->next->next = sll_create_fillup_node(40);

	sll_display(head);

	head = sll_insertion(head);

	head = sll_deletion(head);

	head = sll_cleanup(head);

	return 0;
}

struct Node *sll_create_fillup_node(int data)
{
	struct Node *node = (struct Node *)SLL_MALLOC(sizeof(struct Node));
	
	if (!node) {
		SLL_ERROR("%s:%d node alloc failed\n", __func__, __LINE__);
		return NULL;
	}

	node->data = data;
	node->next = NULL;

	return node;
}

void sll_display(struct Node *head)
{
	struct Node *curr = head;

	while (curr) {
		printf("%d->", curr->data);
		curr = curr->next;
	}
	printf("NULL\n");
}

struct Node *sll_insertion(struct Node *head)
{
	head = sll_insert_at_front(head, 100);
	SLL_DEBUG("Insertion at front display\n");
	sll_display(head);

	head = sll_insert_at_pos(head, 200, 2);
	SLL_DEBUG("Insertion at pos 2 display\n");
	sll_display(head);

	head = sll_insert_at_end(head, 300);
	SLL_DEBUG("Insertion at end display\n");
	sll_display(head);

	return head;
}

struct Node *sll_insert_at_front(struct Node *head, int data)
{
	if (head == NULL) {
		return NULL;
	}

	struct Node *new_node = sll_create_fillup_node(data);

	SLL_ASSERT(new_node != NULL);

	new_node->next = head;
	head = new_node;

	return head;
}

struct Node *sll_insert_at_pos(struct Node *head, int data, int pos)
{

	if (pos < 1 || head == NULL) {
		return NULL;
	}

	if (pos == 1) {
		struct Node *new_node = sll_create_fillup_node(data);
		SLL_ASSERT(new_node);
		new_node->next = head;
		head = new_node;
		return head;
	}

	struct Node *new_node = sll_create_fillup_node(data);
	SLL_ASSERT(new_node);
	struct Node *curr = head;


	for (int i=1; curr != NULL && i<pos-1; i++) {
		curr = curr->next;
	}

	if (curr == NULL) {
		SLL_DEBUG("pos exceeds\n");
		return NULL;
	}
		
	new_node->next = curr->next;
	curr->next = new_node;

	return head;
}

struct Node *sll_insert_at_end(struct Node *head, int data)
{
	if (head == NULL) {
		return NULL;
	}

	struct Node *new_node = sll_create_fillup_node(data);

	SLL_ASSERT(new_node != NULL);

	struct Node *last_node = head;

	while(last_node->next != NULL) {
		last_node = last_node->next;	
	}

	last_node->next = new_node;

	return head;
}

struct Node *sll_deletion(struct Node *head)
{
	head = sll_delete_at_front(head);
	SLL_DEBUG("Deletion at front display\n");
	sll_display(head);

	head = sll_delete_at_pos(head, 2);
	SLL_DEBUG("Deletion at pos 2 display\n");
	sll_display(head);

	head = sll_delete_at_end(head);
	SLL_DEBUG("Deletion at end display\n");
	sll_display(head);

	return head;
}

struct Node *sll_delete_at_front(struct Node *head)
{
	if (head == NULL) {
		return NULL;
	}

	struct Node *temp = head;
	head = head->next;

	SLL_FREE(temp);

	return head;
}


struct Node *sll_delete_at_pos(struct Node *head, int pos)
{
	if (head == NULL) {
		return NULL;
	}

	if (pos == 1) {
		struct Node *temp = head;
		head = head->next;
		SLL_FREE(temp);
	}

	struct Node *curr = head;
	struct Node *prev = NULL;

	for(int i=1; i<pos && curr; i++) {
		prev = curr;
		curr = curr->next;
	}

	prev->next = curr->next;
	SLL_FREE(curr);

	return head;

}

struct Node *sll_delete_at_end(struct Node *head)
{
	if (head == NULL) {
		return NULL;
	}

	if (head->next == NULL) {
		SLL_FREE(head);
		return NULL;
	}
	struct Node *second_last = head;

	while(second_last->next->next != NULL) {
		second_last = second_last->next;
	}

	SLL_FREE(second_last->next);
	second_last->next = NULL;

	return head;
	
}

struct Node *sll_cleanup(struct Node *head)
{

	struct Node *temp;

	while (head != NULL) {
		temp = head;
		head = head->next;
		SLL_FREE(temp);
	}

	if (head == NULL) { SLL_DEBUG("Cleanup successfull\n"); }

	return head;
}
