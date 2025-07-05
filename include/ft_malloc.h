#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>

#include "libft.h"
#include "ft_printf.h"

#include <stdio.h>

#define	ZONE_MIN	100
#define	BYTE		8

typedef	unsigned char 	t_param;

typedef struct s_block
{
	t_bool	taken;
	size_t	size;
	void*	next;
}	t_block;

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

//	main.c

void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	show_alloc_mem(void);

//	init.c
t_bool	init_malloc(t_context* ctx);