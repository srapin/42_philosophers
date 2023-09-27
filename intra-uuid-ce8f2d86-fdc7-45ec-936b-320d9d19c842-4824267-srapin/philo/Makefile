NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g -g3

FILES = \
		act\
		change_state \
		error_handler \
		exit\
		get_mutex\
		id_getter \
		init \
		init_mutexes \
		launcher\
		main \
		parse \
		print \
		routines\
		set_mutex\
		time\




SRCS_DIR = src
SRCS = $(addprefix $(SRCS_DIR)/, $(addsuffix .c, $(FILES)))

OBJS_DIR = obj
OBJS = ${patsubst ${SRCS_DIR}/%.c, ${OBJS_DIR}/%.o, ${SRCS}}

INCLUDES_DIR = inc
INCLUDES_FILES = philo.h
INCLUDES = $(addprefix $(INCLUDES_DIR)/, $(INCLUDES_FILES))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $@

${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c $(INCLUDES)
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<


clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: clean all


.PHONY: all clean fclean re 