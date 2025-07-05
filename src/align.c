#include "ft_malloc.h"

size_t	alignedSize(size_t size)
{
	while ((size + sizeof(t_allocHeader) / BYTE) * BYTE != size + sizeof(t_allocHeader))
		size++;
	return size;
}

t_param	getType(t_context* ctx, size_t size)
{
	if (size <= ctx->tinyMax)
		return TINY;
	else if (size <= ctx->smallMax)
		return SMALL;
	else
		return LARGE;
}
