/*
 * File : sll_remove_dup_sorted.c
 *
 * Description:	Given a sorted linked list, delete all nodes that have duplicate numbers (all occurrences), leaving only numbers that appear once in the original list.
 *
 * author : Yupindra Kumar Balaji
 *
 */

#include "sll_remove_dup_sorted.h"

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

	head1 = sll_remove_dup_sorted(head1);

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

struct Node *sll_remove_dup_sorted(struct Node *head)
{
	if (head == NULL) {
		return NULL;
	}

	struct Node dummy = {0, head};

	struct Node *prev = &dummy;
	struct Node *curr = head;

	while(curr != NULL) {
		if (curr->next && curr->data == curr->next->data) {
			int dup_val = curr->data;
			while(curr && curr->data == dup_val) {
				struct Node *temp = curr;
				curr = curr->next;
				SLL_FREE(temp);
			}
			prev->next = curr;
		} else {
			prev = curr;
			curr = curr->next;
		}
	}

	return dummy.next;

#if 0
	struct Node *dummy = (struct Node *)SLL_MALLOC(sizeof(struct Node));

	SLL_ASSERT(dummy);

	dummy->next = head;

	struct Node *prev = dummy;
	
	struct Node *curr = head;

	while (curr != NULL) {

		while(curr->next && prev->next->data == curr->next->data) {
			curr = curr->next;	
		}

		if (prev->next == curr) {
			prev = prev->next;
		} else {
			prev->next = curr->next;
		}


		curr = curr->next;
	}

	head = dummy->next;

	return head;
#endif
	
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
