/*
 * File : sll_swap_nodes_without_swap_data.c
 *
 * Description:	Given a singly linked list with two values x and y, the task is to swap two nodes having values x and y without swapping data.
 *
 * author : Yupindra Kumar Balaji
 *
 */

#include "sll_swap_nodes_without_swap_data.h"

int main(void)
{
	/* Create the first linked list */
	struct Node *head1 = sll_create_fillup_node(23);
	head1->next = sll_create_fillup_node(28);
	head1->next->next = sll_create_fillup_node(28);
	head1->next->next->next = sll_create_fillup_node(35);
	head1->next->next->next->next = sll_create_fillup_node(49);
	head1->next->next->next->next->next = sll_create_fillup_node(49);
	head1->next->next->next->next->next->next = sll_create_fillup_node(53);
	head1->next->next->next->next->next->next->next = sll_create_fillup_node(53);

	sll_display(head1);

	head1 = sll_swap_nodes_wo_swap_data(head1, 28, 35);

	sll_display(head1);

	sll_cleanup(head1);

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

struct Node *sll_swap_nodes_wo_swap_data(struct Node *head, int x, int y)
{
	if (head == NULL) {
		return NULL;
	}

	if (x == y) return head;

	struct Node *prevX = NULL, *prevY = NULL;
	struct Node *currX = NULL, *currY = NULL;
	struct Node *prev = NULL, *curr = head;

	while (curr != NULL) {

		if (curr->data == x) {
			prevX = prev;
			currX = curr;
		}
		else if (curr->data == y) {
			prevY = prev;
			currY = curr;	
		}
			
		prev = curr;
		curr = curr->next;
	}

	if (!currX || !currY) return head;

	if (prevX != NULL) {
		prevX->next = currY;
	} else {
		head = currY;
	}


	if (prevY != NULL) {
		prevY->next = currX;
	} else {
		head = currX;
	}

	struct Node *temp = currY->next;
	currY->next = currX->next;
	currX->next = temp;

	return head;
}

struct Node *sll_reverse(struct Node *head)
{
	if (head == NULL) {
		return NULL;
	}
	
	struct Node *prev = NULL;
	struct Node *curr = head;
	struct Node *next = NULL;

	while (curr != NULL) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}

	return prev;
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
