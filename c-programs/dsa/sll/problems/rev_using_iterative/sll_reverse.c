/*
 * File : sll_reverse.c
 *
 * Description: singly linked list reverse program
 *
 * author : Yupindra Kumar Balaji
 *
 */

#include "sll_reverse.h"

int main(void)
{
	/* Create a linked list first */
	struct Node *head = sll_create_fillup_node(10);
	head->next = sll_create_fillup_node(20);
	head->next->next = sll_create_fillup_node(30);
	head->next->next->next = sll_create_fillup_node(40);

	sll_display(head);

	head = sll_reverse(head);

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

struct Node *sll_reverse(struct Node *head)
{
	if (head == NULL) {
		SLL_ERROR("%s:%d head is null!!!\n", __func__, __LINE__);
		return NULL;
	}

	/* We need 3 pointers to reverse
	 * in iterative approach
	 */
	struct Node *prev = NULL;
	struct Node *curr = head;
	struct Node *next = NULL;
	
	while (curr != NULL) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}

	// When the loop breaks that means the head is pointed by prev

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
