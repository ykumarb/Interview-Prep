/*
 * File : sll_find_mid_slow_fast.c
 *
 * Description: Find middle node of the linked list. If even, return second mid
 *
 * author : Yupindra Kumar Balaji
 *
 */

#include "sll_find_mid_slow_fast.h"

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

	// Find mid using hare and tortoise algorithm
	SLL_DEBUG("%s:%d mid: %d\n", __func__, __LINE__, sll_find_mid(head));

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

int sll_find_mid(struct Node *head)
{
	// Slow pointer keeps track of next node (moves 1 node forward)
	// Fast pointer keeps track of next nodes next (moves 2 nodes forward)
	// When length is odd, fast ptr points to last node and slow ptr points to mid
	// When length is even, fast ptr points to null and slow ptr points to mid
	
	struct Node *slow = head;
	struct Node *fast = head;

	while(fast != NULL && fast->next != NULL) {
		slow = slow->next;
		fast = fast->next->next;
	}

	// When loop ends either one is true
	/* 1. fast next is null, means odd length and slow is already at mid
	 * 2. fast is null, means event length and slow is already at mid
	 */

	return slow->data; // Guaranteed
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
