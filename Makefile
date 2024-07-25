NAME = philo
DIR_SRC = src/
DIR_OBJ = obj/
CC = cc 
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -f

SRCS =  src/checker.c \
src/error.c \
src/init.c \
src/launch.c \
src/main.c \
src/routine_state.c \
src/utils.c

OBJS = $(SRCS:$(DIR_SRC)%.c=$(DIR_OBJ)%.o)

all: $(NAME)

$(DIR_OBJ)%.o: $(DIR_SRC)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -rf $(DIR_OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
