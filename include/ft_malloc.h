#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/mman.h>

#include "libft.h"
#include "ft_printf.h"

#include <stdio.h>

#define	ZONE_MIN	100
#define	BYTE		8

typedef	unsigned char 	t_param;

typedef struct s_blockHeader
{
	t_param	type;
	void*	next;
	size_t	size;
}	t_blockHeader;

typedef struct s_allocHeader
{
	t_param	type;
	void*	next;
	size_t	allocSize;
	size_t	realSize;
	void*	data;
}	t_allocHeader;

typedef struct s_context
{
	t_bool		init;
	rlim_t		totalAllocated;
	rlim_t		totalClaimed;
	rlim_t		dataMax;
	long		pageSize;
	size_t		tinyZoneSize;
	size_t		smallZoneSize;
	size_t		tinyMax;
	size_t		smallMax;
	void*		tinyZones;
	void*		smallZones;
	void*		largeZones;
}	t_context;

enum	e_types
{
	SMALLBLOCK = 0,
	TINYBLOCK,
	LARGEBLOCK,
	TAKENALLOC,
	FREE
};

//	main.c

void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	show_alloc_mem(void);

//	init.c
t_bool	init_malloc(t_context* ctx);

//	block.c
void	*getNewBlock(size_t size, t_param blockType);
void	releaseBlock(void* ptr);

//	align.c
size_t	alignedSize(size_t size);
t_param	getType(t_context* ctx, size_t size);

//	utils.c
void*	searchFree(t_context* ctx, size_t size, t_param type);
size_t	getSize(t_context* ctx, t_param type, size_t size);