#include "ft_malloc.h"

static inline void	init(void);

static t_context	ctx;

void	free(void *ptr)
{
	ft_printf("Called free\n");
	init();
	if (!ptr)
		return;
	
	return;
}

void	*malloc(size_t size)
{
	ft_printf("Called malloc\n");
	init();
	if (!size)
		return NULL;
	
	const size_t	realSize = alignedSize(size);
	const t_param 	type = getType(&ctx, size);
	void*			ptr = searchFree(&ctx, realSize, type);
	if (((t_allocHeader*)ptr)->type == TAKENALLOC)
	{
		((t_allocHeader*)ptr)->next = getNewBlock(getSize(&ctx, type, realSize), type);
		ptr = ((t_allocHeader*)ptr)->next;
	}
	if (!ptr)
		return NULL;
	((t_allocHeader*)ptr)->allocSize = size;
	((t_allocHeader*)ptr)->realSize = realSize;
	((t_allocHeader*)ptr)->type = TAKENALLOC;
	((t_allocHeader*)ptr)->next = NULL;
	((t_allocHeader*)ptr)->data = ptr + sizeof(t_allocHeader);
	return ((t_allocHeader*)ptr)->data;

	return NULL;
}

void	*realloc(void *ptr, size_t size)
{
	ft_printf("Called realloc\n");
	init();
	(void)ptr;
	(void)size;
	return NULL;
}

void	show_alloc_mem(void)
{
	ft_printf("Called show\n");
	return;
}

static inline void	init(void)
{
	if (!ctx.init)
		init_malloc(&ctx);
}
