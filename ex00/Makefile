CC = c++
CFLAGS = -Werror -Wextra -Wall -std=c++98 -g3 -MMD

NAME = bitcoin
OBJ_DIR = objs

SRCS = $(shell find . -name '*.cpp')
OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRCS))
DEPENDS = $(OBJS:.o=.d)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

-include $(DEPENDS)