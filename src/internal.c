#include "ft_malloc.h"

static t_bool	init_malloc(t_context* ctx);

void	*ft_malloc_internal(t_param param, void *ptr, size_t size)
{
	static	t_context	ctx;

	if ((!ctx.dataMax || !ctx.pageSize) && !init_malloc(&ctx))
		return (NULL);

	switch(param)
	{
		case	FREE:
			free_internal(ptr);
			return NULL;
			break;
		case	MALLOC:
			return malloc_internal(size);
			break;
		case	REALLOC:
			return realloc_internal(ptr, size);
			break;
		case	SHOW:
			show_internal();
			return NULL;
			break;
	}
	return NULL;
}

//	Initialize infos needed for malloc
//	Return TRUE on success
static t_bool	init_malloc(t_context* ctx)
{
	struct rlimit	rl;

	if (getrlimit(RLIMIT_DATA, &rl) || (ctx->pageSize = sysconf(_SC_PAGESIZE)) == -1
		|| !rl.rlim_cur || !ctx->pageSize)
		return (FALSE);
	ctx->dataMax = rl.rlim_cur;

	ctx->tinySize = ctx->pageSize;
	while (ctx->tinySize < ZONE_MIN * BYTE)
		ctx->tinySize += ctx->pageSize;
	ctx->smallSize = ctx->tinySize * BYTE;
	return (TRUE);
}

void	free_internal(void* ptr)
{
	if (!ptr)
		return;
	return;
}

void	*malloc_internal(size_t size)
{
	(void) size;
	return NULL;
}

void	*realloc_internal(void* ptr, size_t size)
{
	(void) ptr;
	(void) size;
	return NULL;
}

void	show_internal(void)
{
	return;
}
