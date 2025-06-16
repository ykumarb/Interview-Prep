/*
 * File : sll_add_one_to_num.c
 *
 * Description: Add 1 to number represented in ll
 *
 * author : Yupindra Kumar Balaji
 *
 */

#include "sll_add_one_to_num.h"

#define ITERATIVE_APPROACH

int main(void)
{

	/* Create a linked list first */
	struct Node *head = sll_create_fillup_node(1);
	head->next = sll_create_fillup_node(9);
	head->next->next = sll_create_fillup_node(9);
	head->next->next->next = sll_create_fillup_node(9);
	head->next->next->next->next = sll_create_fillup_node(9);
	head->next->next->next->next->next = sll_create_fillup_node(9);

	sll_display(head);

#ifndef ITERATIVE_APPROACH
	head = sll_add_carry_recurse(head); // recursion
#else	
	// reverse the ll
	head = sll_reverse(head);

	// compute addition on individual digits in nodes
	head = sll_add_carry_iter(head);
	
	// reverse to get orig ll back
	head = sll_reverse(head);
#endif
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

int sll_add_one_to_num(struct Node *head)
{

	if (head == NULL) {
		return 1;
	}

	int res = head->data + sll_add_one_to_num(head->next);
	
	head->data = res % 10;

	return (res / 10);

}

struct Node *sll_add_carry_recurse(struct Node *head)
{
	if (head == NULL) {
		return NULL;
	}

	int carry = sll_add_one_to_num(head);
	
	if (carry > 0) {
		struct Node *carryn = sll_create_fillup_node(carry);
		SLL_ASSERT(carryn);
		carryn->next = head;
		head = carryn;
	}
	
	return head;
}

struct Node *sll_add_carry_iter(struct Node *head)
{
	if (head == NULL) {
		return NULL;
	}

	struct Node *curr = head;
	struct Node *last = NULL;
	int carry = 1;
	int sum;

	while (curr != NULL) {
		sum = carry + curr->data;	
		carry = (sum == 10) ? 1 : 0;
		
		curr->data = sum % 10;
		
		last = curr;
		curr = curr->next;
	}

	if (carry > 0) {
		last->next = sll_create_fillup_node(carry);
	}

	return head;
}

struct Node *sll_reverse(struct Node *head)
{

	struct Node *curr = head;
	struct Node *prev = NULL;
	struct Node *next = NULL;

	while(curr != NULL) {
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
