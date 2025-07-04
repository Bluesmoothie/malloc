#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>

#include "libft.h"
#include "ft_printf.h"

#define ZONESIZE		100

#define TINYMALLOC		8
#define SMALLMALLOC		(TINYMALLOC * 8)

#define TINYMALLOCZONE	(TINYMALLOC * ZONESIZE)
#define SMALLMALLOCZONE	(SMALLMALLOC * ZONESIZE)

typedef	unsigned char 		t_param;

typedef struct s_tinyZone 	t_tinyZone;
typedef struct s_smallZone 	t_smallZone;
typedef struct s_largeZone 	t_largeZone;

typedef struct s_tinyZone
{
	void*			ptrs[ZONESIZE];
	t_tinyZone*		next;
}	t_tinyZone;

typedef struct s_smallZone
{
	void*			ptrs[ZONESIZE];
	t_smallZone*	next;
}	t_smallZone;

typedef struct s_largeZone
{
	void*			ptr;
	t_largeZone*	next;
}	t_largeZone;

typedef struct s_context
{
	rlim_t			dataMax;
	long			pageSize;
	t_tinyZone		tinyZones;
	t_smallZone		smallZones;
	t_largeZone*	largeZones;
}	t_context;

enum	e_params
{
	FREE,
	MALLOC,
	REALLOC,
	SHOW
};

//	main.c

void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	show_alloc_mem(void);

//	internal.c
void	*ft_malloc_internal(t_param param, void *ptr, size_t size);