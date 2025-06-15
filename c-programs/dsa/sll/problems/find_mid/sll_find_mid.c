/*
 * File : sll_find_mid.c
 *
 * Description: Find middle node of the linked list. If even, return second mid
 *
 * author : Yupindra Kumar Balaji
 *
 */

#include "sll_find_mid.h"

int main(void)
{

	int no_of_nodes = 0;
	int mid_val = 0;

	/* Create a linked list first */
	struct Node *head = sll_create_fillup_node(10);
	head->next = sll_create_fillup_node(20);
	head->next->next = sll_create_fillup_node(30);
	head->next->next->next = sll_create_fillup_node(40);
	head->next->next->next->next = sll_create_fillup_node(50);
	head->next->next->next->next->next = sll_create_fillup_node(60);

	sll_display(head);

	// Find middle of the linked list

	/* By counting nodes.
	 * Find the number of nodes
	 * Get mid pos. Go till there and return answer
	 */

	no_of_nodes = sll_find_length(head);

	if (no_of_nodes == -1) {
		SLL_ERROR("%s:%d head is null\n", __func__, __LINE__);
		return LL_ERROR;
	}

	mid_val = sll_find_mid(head, no_of_nodes);

	SLL_DEBUG("%s:%d curr->data: %d\n", __func__, __LINE__, mid_val);

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

int sll_find_length(struct Node *head)
{
	int  result = 0;

	if (head == NULL) {
		SLL_ERROR("%s:%d head is null\n", __func__, __LINE__);
		return LL_ERROR;
	}

	struct Node *curr = head;

	while(curr != NULL) {
		result++;
		curr = curr->next;
	}

	return result;
}

int sll_find_mid(struct Node *head, int no_of_nodes)
{
	int mid = 0;

	/* Find middle node pos */

	mid = (no_of_nodes/2 ) + 1; // This gives one less than expected. So add 1

	struct Node *curr = head;

	for(int i=1; i<mid && curr != NULL; i++) {
		curr = curr->next;
	}

	if (curr == NULL) {
		SLL_ERROR("%s:%d mid is invalid or exceeded\n", __func__, __LINE__);
		return LL_ERROR;
	}

	/* Now this should point us at exact mid node the problem expects */

	SLL_DEBUG("%s:%d curr->data: %d at mid: %d\n", __func__, __LINE__, curr->data, mid);

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
