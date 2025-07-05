#include "ft_malloc.h"

void	*getNewBlock(size_t size, t_param blockType)
{
	void*	ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS, -1, 0);
	if (ptr == MAP_FAILED)
		return NULL;
	((t_blockHeader*)ptr)->type = blockType;
	((t_blockHeader*)ptr)->size = size;
	((t_blockHeader*)ptr)->next = ptr + sizeof(t_blockHeader);
	return ptr;
}

void	releaseBlock(void* ptr)
{
	munmap(ptr, ((t_blockHeader*)ptr)->size);
}
