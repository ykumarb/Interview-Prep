/*
 * File : sll_find_loop.h
 *
 * Description:	Given a singly linked list, check if the linked list has a loop (cycle) or not.
 * A loop means that the last node of the linked list is connected back to a node in the same list. 
 *
 * author : Yupindra Kumar Balaji
 *
 */
#ifndef SLL_DEBUG_H
#define SLL_DEBUG_H
#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Macros */

#define TRUE	true
#define FALSE	false


/* Codes */
#define LL_ERROR	-1
#define LL_SUCCESS	0
#define LL_NOMEM	-2

#define SLL_TRACE(args)		printf args
#define SLL_PRINTF(fmt, ...) 				\
	do {						\
	   printf(fmt, ##__VA_ARGS__);			\
	} while (0)	

#define SLL_INFO(fmt, ...) 				\
	do {						\
	   printf("[INFO]: " fmt, ##__VA_ARGS__);	\
	} while (0)					

#define SLL_DEBUG(fmt, ...) 				\
	do {						\
	   printf("[DEBUG]: " fmt, ##__VA_ARGS__);	\
	} while (0)					

#define SLL_ERROR(fmt, ...)				\
	do {						\
	   printf("[ERROR]: " fmt, ##__VA_ARGS__); 	\
	} while (0)					

#ifdef MALLOC_STORE_SIZE_IN_RAW
#define SIZE_HEADER	sizeof(size_t)
#define SLL_MALLOC(size) ({									           \
	   void *raw = malloc(SIZE_HEADER + size);							   \
	   if (!raw) {											   \
		SLL_ERROR(" %s:%d malloc failed\n", __func__, __LINE__); 				   \
		return NULL;										   \
	   }												   \
	   *((size_t *)raw) = size;									   \
	   void *user_ptr = (char *)raw + SIZE_HEADER;							   \
	   SLL_DEBUG("%s:%d SLL_MALLOC: %zu bytes bytes at raw: %p user_ptr: %p\n",			   \
			   __func__, __LINE__, (size_t)size, raw, user_ptr); 				   \
	   user_ptr;											   \
	})
#define	SLL_FREE(user_ptr) 										\
	do {												\
	  if (user_ptr) {										\
	  	void *raw = (char *)user_ptr - SIZE_HEADER;						\
	  	size_t size = *((size_t *)raw);								\
	  	SLL_DEBUG("%s:%d SLL_FREE: %zu bytes at raw: %p user_ptr: %p\n",			\
			__func__, __LINE__, size, raw, user_ptr);					\
	  	free(raw);										\
	  	raw = NULL;										\
	 }												\
	} while (0)
#else
#define SLL_MALLOC(l) ({				\
	void *p = malloc(l);				\
	SLL_DEBUG("Allocated %zu bytes at %p\n", l, p)	\
	p; })

#define	SLL_FREE(ptr) 	free(ptr);
#endif /* MALLOC_STORE_SIZE_IN_RAW */

#define SLL_ASSERT(expr)				\
	do {						\
	   if ((expr) == FALSE) {			\
	      printf("[ASSERT]: Assert triggered\n");	\
	      return NULL;				\
	   }						\
	} while (0)

/* Structs */
struct Node {
    int data;
    struct Node *next;
};

/* Function prototypes */
struct Node *sll_create_fillup_node(int);
void sll_display(struct Node *);
struct Node *sll_cleanup(struct Node *head);
bool sll_find_loop(struct Node *head, int *n);
#endif /* SLL_DEBUG_H */
