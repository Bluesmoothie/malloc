#include "ft_malloc.h"

//Return free zone large enought for size, or the last element of the chain if no free space left
void*	searchFree(t_context* ctx, size_t size, t_param type)
{
	switch(type)
	{
		case	TINYBLOCK:
			break;
		case	SMALLBLOCK:
			break;
		case	LARGEBLOCK:
			break;
	}
}

size_t	getSize(t_context* ctx, t_param type, size_t size)
{
	switch(type)
	{
		case	TINYBLOCK:
			return ctx->tinyZoneSize;
			break;
		case	SMALLBLOCK:
			return ctx->smallZoneSize;
			break;
		case	LARGEBLOCK:
			return size + sizeof(t_blockHeader);
			break;
	}
}
