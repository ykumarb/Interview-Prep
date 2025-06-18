/*
 * File : sll_remove_dup_unsorted.c
 *
 * Description:	Given an unsorted linked list containing n nodes, the task is to remove duplicate nodes while preserving the original order.
 *
 * author : Yupindra Kumar Balaji
 *
 */

#include "sll_remove_dup_unsorted.h"

int main(void)
{
	/* Create the first linked list */
	struct Node *head1 = sll_create_fillup_node(12);
	head1->next = sll_create_fillup_node(11);
	head1->next->next = sll_create_fillup_node(12);
	head1->next->next->next = sll_create_fillup_node(21);
	head1->next->next->next->next = sll_create_fillup_node(41);
	head1->next->next->next->next->next = sll_create_fillup_node(43);
	head1->next->next->next->next->next->next = sll_create_fillup_node(21);

	sll_display(head1);

	head1 = sll_remove_dup_unsorted(head1);

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

struct Node *sll_remove_dup_unsorted(struct Node *head)
{
	if (head == NULL) {
		return NULL;
	}

	struct Node *first_ptr = head;
	struct Node *second_ptr = NULL;
	struct Node *prev = NULL;

	while (first_ptr != NULL) {
		prev = first_ptr;
		second_ptr = first_ptr->next;
		while (second_ptr != NULL) {
			if (first_ptr->data == second_ptr->data) {
				struct Node *temp = second_ptr;
				prev->next = second_ptr->next;	
				SLL_FREE(temp);
				second_ptr = prev->next;
				continue;
			}
			prev = second_ptr;
			second_ptr = second_ptr->next;

		}
		first_ptr = first_ptr->next;
	}

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
