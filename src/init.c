#include "ft_malloc.h"

//	Initialize infos needed for malloc
//	Return TRUE on success
t_bool	init_malloc(t_context* ctx)
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
