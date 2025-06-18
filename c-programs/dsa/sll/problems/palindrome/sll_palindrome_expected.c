/*
 * File : sll_palindrome_expected.c
 *
 * Description:	Given a singly linked list. The task is to check if the given linked list is palindrome or not. 
 *
 * author : Yupindra Kumar Balaji
 *
 */

#include "sll_palindrome_expected.h"

int main(void)
{
	/* Create the first linked list */
	struct Node *head1 = sll_create_fillup_node(1);
	head1->next = sll_create_fillup_node(2);
	head1->next->next = sll_create_fillup_node(1);
	head1->next->next->next = sll_create_fillup_node(1);
	head1->next->next->next->next = sll_create_fillup_node(2);
	head1->next->next->next->next->next = sll_create_fillup_node(1);
	
	SLL_DEBUG("%s:%d Valid palindrome : %s\n", __func__, __LINE__, sll_is_palindrome(head1) ? "Yes" : "No");

	/* Note: One more approach is to get mid and start from node after mid and reverse all and compare head of start and
	 * reversed head to decide palindrome or not
	 */

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


bool sll_is_palindrome(struct Node *head)
{
	if (head == NULL) {
		return NULL;
	}

	struct Node *start = head;

	return sll_check_palindrome(head, &start);
}

bool sll_check_palindrome(struct Node *end, struct Node **start)
{
	if (end == NULL) {
		return true;
	}

	bool right = sll_check_palindrome(end->next, start);

	bool ans = right && (*start)->data == end->data;

	*start = (*start)->next;

	return ans;
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
