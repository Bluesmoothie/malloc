#include "ft_malloc.h"

void	*ft_malloc_internal(t_param param, void *ptr, size_t size)
{
	static	t_context	ctx;

	if ((!ctx.dataMax || !ctx.pageSize) && !init_malloc(&ctx))
		return (NULL);

	switch(param)
	{
		case	FREE:
			break;
		case	MALLOC:
			break;
		case	REALLOC:
			break;
		case	SHOW:
			break;
	}
}

//	Initialize infos needed for malloc
//	Return TRUE on success
t_bool	init_malloc(t_context* ctx)
{
	struct rlimit	rl;

	if (getrlimit(RLIMIT_DATA, &rl) || (ctx->pageSize = sysconf(_SC_PAGESIZE)) == -1
		|| !rl.rlim_cur || !ctx->pageSize)
		return (FALSE);
	ctx->dataMax = rl.rlim_cur;
	return (TRUE);
}