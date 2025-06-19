/*
 * File : sll_intersection_point_of_lls.c
 *
 * Description:	 Given two singly linked lists that merge into a single Y-shaped list. The two lists initially have distinct paths but eventually converge at a common node, forming a Y-shape, the task is to find and return the node where the two lists merge.
 *
 * author : Yupindra Kumar Balaji
 *
 */

#include "sll_intersection_point_of_lls.h"

int main(void)
{
	/* Create the first linked list */
	struct Node *head1 = sll_create_fillup_node(10);
	head1->next = sll_create_fillup_node(15);
	head1->next->next = sll_create_fillup_node(30);

	sll_display(head1);

	/* Create the second linked list */
	struct Node *head2 = sll_create_fillup_node(3);
	head2->next = sll_create_fillup_node(6);
	head2->next->next = sll_create_fillup_node(9);

	head2->next->next->next = head1->next;

	sll_display(head2);

	struct Node *int_node = sll_intersection_point_of_lls(head1, head2);

	SLL_DEBUG("%s:%d Intersection node: %d\n", __func__, __LINE__, int_node->data);

	/* This cleanup is not proper because of double free due to intersection of nodes */
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

int sll_get_count(struct Node *head) {

	struct Node *curr = head;
	int len = 0;
	while (curr != NULL) {
		len++;
		curr = curr->next;
	}

	return len;
}

struct Node *sll_intersection_check(int diff, struct Node *head1, struct Node *head2)
{
	struct Node *curr1 = head1;
	struct Node *curr2 = head2;

	for(int i=0; i<diff; i++) {
		if(curr1 == NULL) return NULL;
		curr1 = curr1->next;
	}

	while(curr1!=NULL && curr2!=NULL) {
		if(curr1 == curr2) return curr1;
		curr1 = curr1->next;
		curr2 = curr2->next;	
	}

	return NULL;
}

struct Node* sll_intersection_point_of_lls(struct Node *head1, struct Node *head2)
{
	if (head1 == NULL || head2 == NULL) {
		return NULL;
	}

	int l1 = sll_get_count(head1);
	int l2 = sll_get_count(head2);
	int diff = 0;

	if (l2 > l1) {
		diff = l2 - l1;
		return sll_intersection_check(diff, head2, head1);
	} else {
		diff = l1 - l2;
		return sll_intersection_check(diff, head1, head2);
	}

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
