/*
 * File : sll_move_last_to_front.c
 *
 * Description: Find last node and move it to front.
 *
 * author : Yupindra Kumar Balaji
 *
 */

#include "sll_move_last_to_front.h"

#define TWO_POINTER

int main(void)
{

	/* Create a linked list first */
	struct Node *head = sll_create_fillup_node(10);
	head->next = sll_create_fillup_node(20);
	head->next->next = sll_create_fillup_node(30);
	head->next->next->next = sll_create_fillup_node(40);
	head->next->next->next->next = sll_create_fillup_node(50);
	head->next->next->next->next->next = sll_create_fillup_node(60);

	sll_display(head);

	head = sll_move_last_to_front(head);

	sll_display(head);

	sll_cleanup(head);
		
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

struct Node *sll_move_last_to_front(struct Node *head)
{

	if (head == NULL) {
		return NULL;
	}

	struct Node *curr = head;

	// Go to last but second node
	while (curr->next != NULL && curr->next->next != NULL) {
		curr = curr->next;
	}

	struct Node *last_node = curr->next;
	curr->next = NULL;

	last_node->next = head;
	head = last_node;

	return head;

}

void sll_display(struct Node *head)
{
	struct Node *curr = head;

	while (curr != NULL) {
		SLL_PRINTF("%d->", curr->data);
		curr = curr->next;
	}
	SLL_PRINTF("null\n");
}

struct Node *sll_cleanup(struct Node *head)
{
	struct Node *temp = NULL;

	while (head != NULL) {
		temp = head;
		head = head->next;
		SLL_FREE(temp);
	}

	/* This means head is null and no more nodes */
	if (head == NULL) {
		SLL_DEBUG("%s:%d Cleanup successfull\n", __func__, __LINE__);
	}

	return head;
}
