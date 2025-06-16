/*
 * File : sll_sum_of_last_n.c
 *
 * Description: sum of last n nodes of the given Linked List
 *
 * author : Yupindra Kumar Balaji
 *
 */

#include "sll_sum_of_last_n.h"

#define RECURSIVE_APPROACH

int main(void)
{

	int n = 3;
	int n1 = n;

	/* Create a linked list first */
	struct Node *head = sll_create_fillup_node(21);
	head->next = sll_create_fillup_node(13);
	head->next->next = sll_create_fillup_node(19);
	head->next->next->next = sll_create_fillup_node(20);
	head->next->next->next->next = sll_create_fillup_node(30);
	head->next->next->next->next->next = sll_create_fillup_node(40);

	sll_display(head);

#ifdef RECURSIVE_APPROACH
	int sum = 0;
	sll_sum_of_last_n_use_recurse(head, &n1, &sum);
	SLL_DEBUG("sum of last %d nodes: %d\n", n, sum);
#else
	head = sll_sum_of_last_n(head, n);
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

struct Node *sll_sum_of_last_n(struct Node *head, int n)
{
	if (head == NULL || n < 1) {
		return NULL;
	}

	/* 1. Find the nth node - one pass using main_ptr and ref_ptr (two pointer approach)
	 * 2. Loop from nth node to end and calculate sum
	 */

	// 1. Find nth node using two pointer approach

	struct Node *main_ptr = head;
	struct Node *ref_ptr = head;
	int sum = 0;
	
	for(int i=1; i<n; i++) {
		ref_ptr = ref_ptr->next;
	}

	// Distance between main_ptr and ref_ptr is n - 1;
	while(ref_ptr->next != NULL) {
		main_ptr = main_ptr->next;
		ref_ptr = ref_ptr->next;
	}

	// main_ptr will point at nth node.
	
	// 2. Calculate sum from main_ptr (i.e at last nth node) till end
	while(main_ptr != NULL) {
		sum = sum + main_ptr->data;
		main_ptr = main_ptr->next;
	}

	SLL_DEBUG("sum of last %d nodes: %d\n", n, sum);
	return head;
	
}

void sll_sum_of_last_n_use_recurse(struct Node *head, int *n, int *sum)
{
	if (head == NULL) {
		return;
	}

	sll_sum_of_last_n_use_recurse(head->next, n, sum);

	if(*n > 0) {
		*sum = *sum + head->data;
		--*n;	
	}
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
