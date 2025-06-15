/*
 * File : sll_find_nth_node_from_end.c
 *
 * Description: Find nth node from end of linked list.
 *
 * author : Yupindra Kumar Balaji
 *
 */

#include "sll_find_nth_node_from_end.h"

#define TWO_POINTER

int main(void)
{

	int N = 4;

	/* Create a linked list first */
	struct Node *head = sll_create_fillup_node(10);
	head->next = sll_create_fillup_node(20);
	head->next->next = sll_create_fillup_node(30);
	head->next->next->next = sll_create_fillup_node(40);
	head->next->next->next->next = sll_create_fillup_node(50);
	head->next->next->next->next->next = sll_create_fillup_node(60);

	sll_display(head);
#ifndef TWO_POINTER
	int len = 0;

	// Find length of linked list - 1 pass
	len = sll_find_length(head);

	// Calculate nth node from start instead of end
	// nth_node_from_start = total_len - given_nth_index + 1 
	
	int nth_node_from_start = len - N + 1;
	SLL_DEBUG("%s:%d nth node from end given %d: %d\n", __func__, __LINE__, N, sll_get_nth_node(head, nth_node_from_start, len));
#else
	struct Node *main_ptr = head;
	struct Node *ref_ptr = head;

	// Make ref_ptr stand at N
	for(int i=1; i<N; i++) {
		ref_ptr = ref_ptr->next;

		if(ref_ptr == NULL) {
			return LL_ERROR;
		}
	}

	// Distance b/w main_ptr and ref_ptr is N - 1
	// Now simultaneously move main_ptr and ref_ptr
	// one step ahead till ref_ptr points at last node.

	while(ref_ptr->next != NULL) {
		main_ptr = main_ptr->next;
		ref_ptr = ref_ptr->next;
	}

	 SLL_DEBUG("%s:%d main_ptr->data: %d at N : %d\n", __func__, __LINE__, main_ptr->data, N);

#endif /* !TWO_POINTER */

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

int sll_get_nth_node(struct Node *head, int nth_node, int len)
{

	if (nth_node < 1 || nth_node > len) {
		return LL_ERROR;
	}
	struct Node *curr = head;
	for(int i=1; i<nth_node && curr != NULL; i++) {
		curr = curr->next;
	}

	if (curr == NULL) {
		return LL_ERROR;
	}
	// Now curr should already point at valid pointer

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
