/*
 * File : sll_remove_kth_node.c
 *
 * Description: Given a singly linked list, the task is to remove every kth node of the linked list. Assume that k is always less than or equal to the length of the Linked List.
 *
 * author : Yupindra Kumar Balaji
 *
 */

#include "sll_remove_kth_node.h"

int main(void)
{

	int k = 3;
	/* Create the first linked list */
	struct Node *head1 = sll_create_fillup_node(1);
	head1->next = sll_create_fillup_node(2);
	head1->next->next = sll_create_fillup_node(3);
	head1->next->next->next = sll_create_fillup_node(4);
	head1->next->next->next->next = sll_create_fillup_node(5);
	head1->next->next->next->next->next = sll_create_fillup_node(6);
	head1->next->next->next->next->next->next = sll_create_fillup_node(7);
	head1->next->next->next->next->next->next->next = sll_create_fillup_node(8);
	head1->next->next->next->next->next->next->next->next = sll_create_fillup_node(9);
	//head1->next->next->next->next->next->next->next->next->next = sll_create_fillup_node(10);

	sll_display(head1);

	head1 = sll_remove_kth_node(head1, k);

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

struct Node *sll_remove_kth_node(struct Node *head, int k)
{
	if (head == NULL) {
		SLL_DEBUG("%s:%d head is null returning\n", __func__, __LINE__);
		return NULL;
	}
	struct Node *curr = head;
	struct Node *prev = NULL;
	int n = 1;

	while (curr != NULL) {
		if (n % k == 0) {
			SLL_DEBUG("Removing node %d with value %d\n", n, curr->data);
			struct Node *temp = curr;
			if (prev == NULL) {
				head = curr->next;
				curr = head;
			} else {
				prev->next = curr->next;
				curr = prev->next;
			}

			SLL_FREE(temp);
			n++;
			continue;
		}

		prev = curr;
		curr = curr->next;
		n++;
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
