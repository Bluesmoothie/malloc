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

	ctx->tinyZoneSize = ctx->pageSize;
	while (ctx->tinyZoneSize < ZONE_MIN * BYTE)
		ctx->tinyZoneSize += ctx->pageSize;
	ctx->smallZoneSize = ctx->tinyZoneSize * BYTE;
	ft_printf("Tinyzone = %zu tinySize = %zu\n smallzonesize = %zu smallsize = %zu\n", ctx->tinyZoneSize, ctx->tinyMax, ctx->smallZoneSize, ctx->smallMax);
	return (TRUE);
}
