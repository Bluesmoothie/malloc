#include "ft_malloc.h"

//	Initialize infos needed for malloc
//	Return TRUE on success
t_bool	init_malloc(t_context* ctx)
{
	struct rlimit	rl;

	if (getrlimit(RLIMIT_DATA, &rl) || (ctx->pageSize = sysconf(_SC_PAGESIZE)) == -1
		|| !rl.rlim_cur || !ctx->pageSize)
		return FALSE;
	ctx->dataMax = rl.rlim_cur;

	ctx->tinyZoneSize = ctx->pageSize;
	while (ctx->tinyZoneSize < (ZONE_MIN * sizeof(t_allocHeader) * 2) + sizeof(t_blockHeader))
		ctx->tinyZoneSize += ctx->pageSize;
	ctx->tinyMax = (ctx->tinyZoneSize - sizeof(t_blockHeader)) / ZONE_MIN - sizeof(t_allocHeader);
	ctx->smallZoneSize = ctx->tinyZoneSize * BYTE * 2;
	ctx->smallMax = (ctx->smallZoneSize - sizeof(t_blockHeader)) / ZONE_MIN - sizeof(t_allocHeader);

	ctx->tinyZones = getNewBlock(ctx->tinyZoneSize, TINYBLOCK);
	ctx->smallZones = getNewBlock(ctx->smallZoneSize, SMALLBLOCK);
	if (!ctx->tinyZones || !ctx->smallZones)
		return FALSE;
	ctx->init = TRUE;
	return TRUE;
}
