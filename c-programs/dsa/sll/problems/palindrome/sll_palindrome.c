/*
 * File : sll_palindrome.c
 *
 * Description:	Given a singly linked list. The task is to check if the given linked list is palindrome or not. 
 *
 * author : Yupindra Kumar Balaji
 *
 */

#include "sll_palindrome.h"

int main(void)
{
	struct Node *original = NULL;

	/* Create the first linked list */
	struct Node *head1 = sll_create_fillup_node(1);
	head1->next = sll_create_fillup_node(2);
	head1->next->next = sll_create_fillup_node(1);
	head1->next->next->next = sll_create_fillup_node(1);
	head1->next->next->next->next = sll_create_fillup_node(2);
	head1->next->next->next->next->next = sll_create_fillup_node(1);

	original = sll_deep_clone(head1);
	
	SLL_DEBUG("%s:%d Valid palindrome: %s\n", __func__, __LINE__, sll_palindrome(original, head1) ? "Yes" : "No");

	sll_cleanup(original);

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


struct Node *sll_deep_clone(struct Node *head)
{
	if (head == NULL) {
		return NULL;
	}
	struct Node *new_head = sll_create_fillup_node(head->data);
	struct Node *curr_new = new_head;
	struct Node *curr_old = head->next;

	while(curr_old) {
		curr_new->next = sll_create_fillup_node(curr_old->data);
		curr_old = curr_old->next;
		curr_new = curr_new->next;
	}

	return new_head;
}

bool sll_palindrome(struct Node *orig_head, struct Node *new_head)
{
	if (!orig_head || !new_head) {
		return NULL;	
	}

	SLL_DEBUG("%s:%d orig ll\n", __func__, __LINE__);
	sll_display(orig_head);
	new_head = sll_reverse(new_head);
	SLL_DEBUG("%s:%d rev ll\n", __func__, __LINE__);
	sll_display(new_head);
	
	struct Node *orig = orig_head;
	struct Node *rev = new_head;

	/* Check both the ll */
	while (orig != NULL && rev != NULL) {
		
		if (orig->data != rev->data) {
			sll_cleanup(new_head);
			return false;
		}
		orig = orig->next;
		rev = rev->next;
	}
	
	sll_cleanup(new_head);

	return true;
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
