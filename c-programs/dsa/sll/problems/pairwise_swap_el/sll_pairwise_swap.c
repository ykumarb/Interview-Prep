/*
 * File : sll_pairwise_swap.c
 *
 * Description: Given a singly linked list, the task is to swap linked list elements pairwise.
 *
 * author : Yupindra Kumar Balaji
 *
 */

#include "sll_pairwise_swap.h"

int main(void)
{

	/* Create the first linked list */
	struct Node *head1 = sll_create_fillup_node(21);
	head1->next = sll_create_fillup_node(13);
	head1->next->next = sll_create_fillup_node(19);
	head1->next->next->next = sll_create_fillup_node(20);
	head1->next->next->next->next = sll_create_fillup_node(30);
	head1->next->next->next->next->next = sll_create_fillup_node(40);

	sll_display(head1);

	head1 = sll_pairwise_swap_el(head1);

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

struct Node *sll_pairwise_swap_el(struct Node *head)
{
	if (head == NULL) {
		SLL_DEBUG("%s:%d head is null returning\n", __func__, __LINE__);
		return NULL;
	}
	struct Node *curr = head;
	// Swap - also xor will work!
#ifdef WITH_TEMP
	int temp = 0;

	while (curr != NULL && curr->next != NULL) {
		temp = curr->data;
		curr->data = curr->next->data;	
		curr->next->data = temp;
		curr = curr->next->next;
	}
#else
	while (curr != NULL && curr->next != NULL) {
#if 0
		curr->data = curr->data + curr->next->data;
		curr->next->data = curr->data - curr->next->data;
		curr->data = curr->data - curr->next->data;
#endif
		curr->data = curr->data ^ curr->next->data;
		curr->next->data = curr->data ^ curr->next->data;
		curr->data = curr->data ^ curr->next->data;
		
		// move the hare now
		curr = curr->next->next;
	}
	
#endif /* WITH_TEMP */

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
