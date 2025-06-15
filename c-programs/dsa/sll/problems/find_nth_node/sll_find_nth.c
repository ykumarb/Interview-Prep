/*
 * File : sll_find_nth.c
 *
 * Description: Find nth node if exists given pos else return -1
 *
 * author : Yupindra Kumar Balaji
 *
 */

#include "sll_find_nth.h"

int main(void)
{

	int index = 0;
	int result = -1;

	/* Create a linked list first */
	struct Node *head = sll_create_fillup_node(10);
	head->next = sll_create_fillup_node(20);
	head->next->next = sll_create_fillup_node(30);
	head->next->next->next = sll_create_fillup_node(40);

	sll_display(head);

	/* Input pos feed any value */
	//index = 2;
	index = 5;

	SLL_DEBUG("Find data at pos: %d\n", index);
	result = sll_find_nth(head, index);

	SLL_DEBUG("Result: %d %s\n", result, result == -1 ? "Fail" : "Pass");

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

int sll_find_nth(struct Node *head, int pos)
{
	// pos needs to be +ve value
	if (head == NULL || pos < 1) {
		SLL_ERROR("%s:%d head is null or pos is invalid!!!\n", __func__, __LINE__);
		return LL_ERROR;
	}

	// If pos is 1 return data at head and fast exit
	if (pos == 1) {
		return head->data;	
	}

	// If pos is other than 1st, lets loop through
	// and find and stop at right pos index and take action
	// if not found till end and curr becomes NULL return -1
	struct Node *curr = head;

	for(int i=1; curr != NULL && i<pos; i++) {
		curr = curr->next;
	}

	/* When loop ends one of the two cases is possible
	 * 1. We found the node at pos - curr will be valid
	 * 2. We dont find the node at pos - curr will be NULL
	 */

	if (curr == NULL) {
		SLL_ERROR("%s:%d pos exceeded\n", __func__, __LINE__);
		return LL_ERROR;
	}
	
	SLL_DEBUG("%s:%d curr is valid at proper pos\n", __func__, __LINE__);
	return curr->data;
		
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
