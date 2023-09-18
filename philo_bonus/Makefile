NAME = philo_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g -g3

FILES = \
		act\
		change_state \
		end_philo \
		error \
		exit\
		forks\
		ft_itoa\
		id_getter \
		init \
		launcher\
		main \
		monitor \
		parse \
		print \
		routines\
		time\
		utils_end \
		utils_getter \
		utils\




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