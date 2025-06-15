/*
 * File : sll_move_mid_to_front.c
 *
 * Description: Find mid node and move it to front.
 *
 * author : Yupindra Kumar Balaji
 *
 */

#include "sll_move_mid_to_front.h"

int main(void)
{

	/* Create a linked list first */
	struct Node *head = sll_create_fillup_node(10);
	head->next = sll_create_fillup_node(20);
	head->next->next = sll_create_fillup_node(30);
	head->next->next->next = sll_create_fillup_node(40);
	head->next->next->next->next = sll_create_fillup_node(50);
	head->next->next->next->next->next = sll_create_fillup_node(60);

	sll_display(head);

	struct Node *mid = sll_move_mid_to_front(head);

	mid->next = head;
	head = mid;

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

struct Node *sll_move_mid_to_front(struct Node *head)
{

	if (head == NULL) {
		return NULL;
	}

	struct Node *slow = head;
	struct Node *fast = head;
	struct Node *prev = NULL;

	// fast moves two nodes forward and slow moves one node forward
	// when even/odd slow points to mid

	while(fast && fast->next) {
		prev = slow;
		slow = slow->next;
		fast = fast->next->next;
	}

	// prev points one step behind slow (i.e mid)
	prev->next = slow->next;
	return slow;

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
