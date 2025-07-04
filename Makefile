.PHONY				:	clean fclean re all debug leaks check

ifeq ($(HOSTTYPE),)
HOSTTYPE 			:= $(shell uname -m)_$(shell uname -s)
endif

NAME				=   libft_malloc_$(HOSTTYPE).so
LNNAME				=	libft_malloc.so
MODE 				?= 	release

#			GCC

CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror -MMD -MP -fPIC $(INCLUDE)

ifeq ($(MODE), debug)
	CFLAGS			= 	-Wall -Wextra -MMD -MP -fPIC $(INCLUDE) -g3 -DDEBUG
endif

#			CLANG-TIDY

CLANG-TIDY			=	clang-tidy-12
CLANG-TIDY_CHECKS	=	-checks='-*,bugprone-*,cert-*,cppcoreguidelines-*,modernize-*,readability-*'

#			COMMON

BUILD_DIR			=	.build/
SRC_DIR				=	./src/
INCLUDE 			=	-Iinclude/

#			SRC

VPATH				=

SRC_FILES			=	main			\

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

$(NAME)				:	$(BUILD_DIR) $(OBJ)
					$(CC) -shared -o $(NAME) $(OBJ)
					ln -s $(NAME) $(LNNAME)

$(BUILD_DIR)		:
					mkdir -p $(BUILD_DIR)

$(BUILD_DIR)%.o		: 	$(SRC_DIR)%.cpp
					$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)

clean				:
					rm -rf $(BUILD_DIR)

fclean				:	clean
					rm -f $(NAME)

re					:	fclean all