#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

#define TINYMALLOC		10
#define SMALLMALLOC		(TINYMALLOC * 10)

#define TINYMALLOCZONE	(TINYMALLOC * 100)
#define SMALLMALLOCZONE	(SMALLMALLOC * 100)

//	main.c

void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	show_alloc_mem(void);