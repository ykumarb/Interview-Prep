/*
 * File : identical_ll.c
 *
 * Description: Check if two given ll's are identical or not.
 *
 * author : Yupindra Kumar Balaji
 *
 */

#include "identical_ll.h"

int main(void)
{
	int result = 0;

	/* Create the first linked list */
	struct Node *head1 = sll_create_fillup_node(10);
	head1->next = sll_create_fillup_node(20);
	head1->next->next = sll_create_fillup_node(30);
	head1->next->next->next = sll_create_fillup_node(40);

	sll_display(head1);

	/* Create the second linked list */
	struct Node *head2 = sll_create_fillup_node(10);
        head2->next = sll_create_fillup_node(20);
	head2->next->next = sll_create_fillup_node(30);
	head2->next->next->next = sll_create_fillup_node(40);	

	sll_display(head2);

	result = sll_is_identical(head1, head2);

	if (result == TRUE) {
		SLL_DEBUG("%s:%d Two given linked lists are identical\n", __func__, __LINE__);
	} else {
		SLL_DEBUG("%s:%d Two given linked lists are not identical\n", __func__, __LINE__);
	}	

	sll_cleanup(head1);
	sll_cleanup(head2);
		
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

bool sll_is_identical(struct Node *head1, struct Node *head2)
{
	if (head1 == NULL || head2 == NULL) {
		SLL_ERROR("%s:%d head1 or head2 is null\n", __func__, __LINE__);
		return FALSE;
	}

	while (head1 != NULL && head2 != NULL) {
		if (head1->data != head2->data)	{
			return FALSE;
		}
		head1 = head1->next;
		head2 = head2->next;
	}

	return (head1 == NULL && head2 == NULL);
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
