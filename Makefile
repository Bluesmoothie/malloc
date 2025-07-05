.PHONY				:	clean fclean re all debug leaks check FORCE

ifeq ($(HOSTTYPE),)
HOSTTYPE 			:= $(shell uname -m)_$(shell uname -s)
endif

NAME				=   libft_malloc_$(HOSTTYPE).so
LNNAME				=	libft_malloc.so
MODE 				?= 	release

#			GCC

CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror -MMD -MP -fPIC $(INCLUDE)
LIBSFLAGS			=	-L./ -lft

ifeq ($(MODE), debug)
	CFLAGS			= 	-Wall -Wextra -MMD -MP -fPIC $(INCLUDE) -g3 -DDEBUG
endif

#			CLANG-TIDY

CLANG-TIDY			=	clang-tidy-12
CLANG-TIDY_CHECKS	=	-checks='-*,bugprone-*,cert-*,cppcoreguidelines-*,modernize-*,readability-*'

#			LIBFT

LIBFT				=	libft
LIBFT_SO			=	$(LIBFT)/libft_ex.so

#			COMMON

BUILD_DIR			=	.build/
SRC_DIR				=	./src/
INCLUDE 			=	-Iinclude/ -I$(LIBFT)/include/

#			SRC

VPATH				=

SRC_FILES			=	main			\
						init			\
						block			\
						align			\
						utils			\

SRC 				= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 				= 	$(addprefix $(BUILD_DIR), $(addsuffix .o, $(SRC_FILES)))
DEPS 				= 	$(addprefix $(BUILD_DIR), $(addsuffix .d, $(SRC_FILES)))

#			RULES

all					:	$(NAME)

debug				:
					$(MAKE) MODE=debug all

leaks				:
					$(MAKE) MODE=debug all
					valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./$(NAME)
			
check				:
					$(CLANG-TIDY) $(SRC) $(CLANG-TIDY_CHECKS) -- $(INCLUDE)

$(NAME)				:	$(BUILD_DIR) $(OBJ) $(LIBFT_SO)
					$(CC) $(LIBSFLAGS) -shared -o $(NAME) $(OBJ)
					rm -f $(LNNAME)
					ln -s $(NAME) $(LNNAME)

$(BUILD_DIR)		:
					mkdir -p $(BUILD_DIR)

$(BUILD_DIR)%.o		: 	$(SRC_DIR)%.c
					$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)

$(LIBFT_SO)			:	FORCE
					$(MAKE) -C $(LIBFT)
					cp $(LIBFT_SO) ./libft.so

FORCE				:

clean				:
					rm -rf $(BUILD_DIR)
					$(MAKE) clean -C $(LIBFT)

fclean				:	clean
					rm -f $(NAME)
					rm -f $(LNNAME)
					rm -f libft.so
					$(MAKE) fclean -C $(LIBFT)

re					:	fclean all