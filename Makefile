CC =	/usr/bin/clang
RM =	/bin/rm
MAKE =	/usr/bin/make
MKDIR =	/bin/mkdir

NAME = minishell 

ROOT =		$(shell /bin/pwd)
OPATH =		$(ROOT)/objs
CPATH =		$(ROOT)/srcs
HPATH =		$(ROOT)/includes
LIBPATH =	$(ROOT)/libft
LFTHPATH =	$(LIBPATH)/includes

CFLAGS = -g -Wall -Werror -Wextra -I $(HPATH) -I $(LFTHPATH)
LIBS = -L $(LIBPATH) -lft

SRC = 	minishell.c \

OFILES = $(patsubst %.c, $(OPATH)/%.o, $(SRC))

.PHONY: all clean fclean re

all: $(OPATH) $(NAME)

$(NAME): $(OFILES)
	@$(MAKE) -C $(LIBPATH)
	@echo "Creating OBJ files"
	@echo "Building $@"
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	@echo "\033[36mAll is done!\033[0m"

$(OPATH)/%.o: $(CPATH)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(OPATH):
	@echo "Creating OBJ directory"
	@$(MKDIR) $@

clean:
	@echo "Deleting OBJ files"
	@$(RM) -rf $(OPATH)

fclean: clean lib.fclean
	@echo "Deleting $(NAME)"
	@$(RM) -f $(NAME)
	@echo "\033[36mAll clear!\033[0m"

lib.fclean:
	@$(MAKE) fclean -C $(LIBPATH)

re: fclean all

# lil memo
# $@ = rule's name
# $^ = all the rule dependecies
# $< = only the first dependence

# Color for c
#   reset	"\033[0m"
#   RED  	"\033[31m"
#   GRN  	"\033[32m"
#   YEL  	"\033[33m"
#   BLU  	"\033[34m"
#   MAG  	"\033[35m"
#   CYN  	"\033[36m"
#   WHT  	"\033[37m"
