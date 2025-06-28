/*
 * File: main.h
 * 
 * Description: Bit manipulation - Generate xor from 1 to n
 *
 * Author: Yupindra Kumar Balaji
 *
 */

#ifndef __BIT_MANIP_H__
#define __BIT_MANIP_H__

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>

#define BMP_SCANF(fmt, ...)							\
	do {									\
		scanf(fmt, __VA_ARGS__);					\
	} while(0)

#define BMP_INFO(fmt, ...) 							\
	do {									\
		printf("[INFO] " fmt, ##__VA_ARGS__);				\
	} while(0)					

#define BMP_DEBUG(fmt, ...) 							\
	do {									\
		printf("[DEBUG] " fmt, ##__VA_ARGS__);				\
	} while(0)					

#define BMP_ERROR(fmt, ...) 							\
	do {									\
		printf("[ERROR] " fmt, ##__VA_ARGS__);				\
	} while(0)					

#define SIZE_HEADER	sizeof(size_t)

#define BMP_MALLOC(size) ({							\
	void *raw = malloc(size + SIZE_HEADER);					\
	if (!raw) {								\
		BMP_ERROR("%s:%d malloc failed\n", __func__, __LINE__);		\
		return NULL;							\
	}									\
	*((size_t *)raw) = size;						\
	void *user_ptr = raw + SIZE_HEADER;					\
	BMP_DEBUG("%s:%d BMP_MALLOC: %zu bytes at raw: %p user_ptr: %p\n",	\
			__func__, __LINE__, (size_t)size, raw, user_ptr);	\
	user_ptr;								\
	})

#define BMP_FREE(user_ptr) 							\
	do {									\
		void *raw = (char *)user_ptr - SIZE_HEADER;			\
		size_t size = *((size_t *)raw);					\
		BMP_DEBUG("%s:%d BMP_FREE: %zu bytes at raw: %p user_ptr: %p\n",\
			__func__, __LINE__, size, raw, user_ptr);		\
		free(raw);							\
		raw = NULL;							\
	} while(0)

/* Function Prototypes */
int bmp_generate_xor_1ton(int n);

#endif /* __BIT_MANIP_H__ */
