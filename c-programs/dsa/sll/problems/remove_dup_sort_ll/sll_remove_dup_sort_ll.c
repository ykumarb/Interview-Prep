/*
 * File : sll_remove_dup_sort_ll.c
 *
 * Description: Given a linked list sorted in non-decreasing order. Return the list by deleting the duplicate nodes from the list. The returned list should also be in non-decreasing order.
 *
 * author : Yupindra Kumar Balaji
 *
 */

#include "sll_remove_dup_sort_ll.h"

int main(void)
{

	/* Create the first linked list */
	struct Node *head1 = sll_create_fillup_node(11);
	head1->next = sll_create_fillup_node(11);
	head1->next->next = sll_create_fillup_node(11);
	head1->next->next->next = sll_create_fillup_node(21);
	head1->next->next->next->next = sll_create_fillup_node(43);
	head1->next->next->next->next->next = sll_create_fillup_node(43);
	head1->next->next->next->next->next->next = sll_create_fillup_node(60);
	head1->next->next->next->next->next->next->next = sll_create_fillup_node(8);
	head1->next->next->next->next->next->next->next->next = sll_create_fillup_node(9);
	head1->next->next->next->next->next->next->next->next->next = sll_create_fillup_node(10);

	sll_display(head1);

	head1 = sll_remove_dup_sort_ll(head1);

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

struct Node *sll_remove_dup_sort_ll(struct Node *head)
{
	if (head == NULL) {
		SLL_DEBUG("%s:%d head is null returning\n", __func__, __LINE__);
		return NULL;
	}
	
	struct Node *curr = head;
	struct Node *prev = NULL;

	while(curr != NULL) {

		if(prev && curr->data == prev->data) {
			struct Node *temp = curr;
			prev->next = curr->next;	
			SLL_FREE(temp);
			curr = prev->next;
			continue;
		}

		prev = curr;
		curr = curr->next;
	}

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
