NAME = philo
NAME_UNFLAG = philo
NAME_BONUS = philo_bonus

CC = cc
CFLAGS =-pthread -g -g3
# CFLAGS = -Wall -Wextra -Werror -pthread -g -g3

FILES = \
		change_state \
		error_handler \
		id_getter \
		init \
		main \
		parse \
		philo \
		print \
		routines\
		utils\




SRCS_DIR = src
SRCS = $(addprefix $(SRCS_DIR)/, $(addsuffix .c, $(FILES)))

OBJS_DIR = obj
OBJS = ${patsubst ${SRCS_DIR}/%.c, ${OBJS_DIR}/%.o, ${SRCS}}

# SRCS_DIR_BONUS = src_bonus
# SRCS_BONUS = $(addprefix $(SRCS_DIR_BONUS)/, $(addsuffix .c, $(FILES)))

# OBJS_DIR_BONUS = obj_bonus
# OBJS_BONUS = ${patsubst ${SRCS_DIR_BONUS}/%.c, ${OBJS_DIR_BONUS}/%.o, ${SRCS_BONUS}}

# SRCS_DIR_UNFLAG = src
# SRCS_UNFLAG = $(addprefix $(SRCS_DIR_UNFLAG)/, $(addsuffix .c, $(FILES)))

# OBJS_DIR_UNFLAG = obj_UNFLAG
# OBJS_UNFLAG = ${patsubst ${SRCS_DIR_UNFLAG}/%.c, ${OBJS_DIR_UNFLAG}/%.o, ${SRCS_UNFLAG}}

INCLUDES_DIR = inc
INCLUDES_FILES = philo.h
INCLUDES = $(addprefix $(INCLUDES_DIR)/, $(INCLUDES_FILES))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $@

${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c $(INCLUDES)
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<



# $(NAME_UNFLAG) : $(OBJS_UNFLAG)
# 	$(CC) $(OBJS_UNFLAG) $(CFLAGS) -o $@

# ${OBJS_DIR_UNFLAG}/%.o: ${SRCS_DIR_UNFLAG}/%.c $(INCLUDES)
# 	@mkdir -p $(OBJS_DIR_UNFLAG)
# 	$(CC)  -o $@ -c $<


# bonus : $(NAME_BONUS)

# $(NAME_BONUS) : $(OBJS_BONUS)
# 	$(CC) $(OBJS_BONUS) $(CFLAGS) -o $@

# ${OBJS_DIR_BONUS}/%.o: ${SRCS_DIR_BONUS}/%.c $(INCLUDES)
# 	@mkdir -p $(OBJS_DIR_BONUS)
# 	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJS_DIR_UNFLAG)
	rm -rf $(OBJS_DIR)
	rm -rf $(OBJS_DIR_BONUS)

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_UNFLAG)
	rm -f $(NAME_BONUS)

re: clean all


.PHONY: all clean fclean re 