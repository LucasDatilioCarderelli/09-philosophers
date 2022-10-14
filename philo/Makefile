.PHONY: all clean fclean re

NAME		=	philo

CC			=	gcc
CFLAGS		=	-g -Wall -Wextra -Werror -pthread

SRC_DIR		=	src
OBJ_DIR		=	obj

INCLUDE		=	-I ./

SRC_FILES	=	philo.c \
				utils.c	\
				get_time.c \
				checker.c \
				create_llist.c \
				thread_init.c \
				philo_routines.c

SRC			=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ			=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
				mkdir -p $(OBJ_DIR)
				$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

all:			$(NAME)

$(NAME):		$(OBJ)
				$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
				rm -rf $(OBJ_DIR)

fclean:			clean
				rm -rf $(NAME)

re:				fclean all
