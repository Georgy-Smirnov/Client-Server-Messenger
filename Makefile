## START_MAKEFILE ##

#==================================>COLORS<====================================#

_RED		=	\e[31m
_YELLOW		=	\e[33m
_GREEN		=	\e[32m
_END		=	\e[0m

#==================================>FILES<=====================================#

SRC			=	./libft.c

SRC1		=	./server.c

SRC2		=	./client.c

#===============================>COMPILATIONS<=================================#

GCC			=	gcc

CFLAGS		=	-Wall -Werror -Wextra

#===================================>DELETE<===================================#

RM			=	rm -rf

#=================================>DIRECTORIES<================================#

DIR_HEAD	=	./

#===============================>COMPILED_SOURCES<=============================#

OBJ1		=	${SRC1:%.c=%.o}

OBJ2		=	${SRC2:%.c=%.o}

OBJ			=	${SRC:%.c=%.o}

NAME1		=	server

NAME2		=	client

#================================>COMPILED_RULES<==============================#


all:			${NAME1} ${NAME2}

${NAME1}:		${OBJ1} ${OBJ}
				@${GCC} ${CFLAGS} -o ${NAME1} ${OBJ1} ${OBJ}
				@printf "\033[2K\r${_GREEN} FILE create: '${NAME1}'. ${_END}✅\n"

${NAME2}:		${OBJ2} ${OBJ}
				@${GCC} ${CFLAGS} -o ${NAME2} ${OBJ2} ${OBJ}
				@printf "\033[2K\r${_GREEN} FILE create: '${NAME2}'. ${_END}✅\n"

#===========================>COMPILED_SOURCES_RULES<===========================#

%.o: 			%.c
				@$(GCC) $(CFLAGS) -I $(DIR_HEAD) -c $< -o $@
				@printf "\033[2K\r$(_YELLOW) Compiling $< $(_END)⌛"

#===================================>NORM_RULES<===============================#

norm:
				@norminette *.c
				@norminette *.h				

#====================================>CLEAN_RULES<=============================#

clean:
				@${RM} ${OBJ1} ${OBJ2} ${OBJ}
				@printf "\033[2K\r${_RED} '".o"' has been deleted. ${_END}🗑️\n"

fclean:			clean	
				@${RM} ${NAME1} ${NAME2}
				@printf "\033[2K\r${_RED} '"${NAME1}"' and '"${NAME2}"' has been deleted. ${_END}🗑️\n"

re:				fclean all

.PHONY: all clean fclean norm re