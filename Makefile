NAME = codexion

# Compiler and Flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinc
PTHREAD = -pthread

# Directories
SRC_DIR = src/
INC_DIR = inc/
OBJ_DIR = obj/

# Source files
# List your .c files from the src directory here
SRC_FILES = parse_args.c
MAIN_FILE   = main.c

# Combine paths
SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES)) $(MAIN_FILE)
OBJS = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o)) $(OBJ_DIR)main.o

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(PTHREAD) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile main.c into obj/
$(OBJ_DIR)main.o: main.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create the objects directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)
	@echo "🧹 Objects removed."

fclean: clean
	rm -f $(NAME)
	@echo "🗑️  Executable removed."

re: fclean all

.PHONY: all clean fclean re