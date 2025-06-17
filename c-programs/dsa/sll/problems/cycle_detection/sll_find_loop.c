/*
 * File : sll_find_loop.c
 *
 * Description: Given a singly linked list, check if the linked list has a loop (cycle) or not.
 * A loop means that the last node of the linked list is connected back to a node in the same list.
 *
 * author : Yupindra Kumar Balaji
 *
 */

#include "sll_find_loop.h"

int main(void)
{

	/* Create the first linked list */
	struct Node *head1 = sll_create_fillup_node(1);
	head1->next = sll_create_fillup_node(2);
	head1->next->next = sll_create_fillup_node(3);
	head1->next->next->next = sll_create_fillup_node(4);
	head1->next->next->next->next = head1->next->next;
	//head1->next->next->next->next = sll_create_fillup_node(5);

	/* This display will loop if it has cycle */
	// sll_display(head1);

	SLL_DEBUG("%s:%d Loop %s\n",
		__func__, __LINE__, sll_find_loop(head1) ? "Detected" : "No Detected");

	/* This display will loop if it has cycle */
	// sll_display(head1);

	/* This cleanup will loop if it has cycle */
	// sll_cleanup(head1);

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

bool sll_find_loop(struct Node *head)
{
	/* Floyd's cycle finding algorithm */
	struct Node *slow = head;
	struct Node *fast = head;

	while (slow && fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;	

		if(slow == fast) {
			return true;
		}
	}
	return false;
	
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
