NAME = libft.a
CFLAGS = -Wall -Wextra -Werror
CC = cc

SRC = ft_isalnum.c \
ft_strchr.c \
ft_strncmp.c \
ft_toupper.c \
ft_isalpha.c \
ft_memchr.c \
ft_strdup.c \
ft_strnstr.c \
ft_isascii.c \
ft_memcmp.c \
ft_strrchr.c \
ft_atoi.c \
ft_isdigit.c \
ft_memcpy.c \
ft_strlcat.c \
ft_bzero.c \
ft_memmove.c \
ft_strlcpy.c \
ft_calloc.c \
ft_isprint.c \
ft_memset.c \
ft_strlen.c \
ft_tolower.c \
ft_substr.c \
ft_strjoin.c \
ft_strtrim.c \
ft_split.c \
ft_itoa.c \
ft_strmapi.c \
ft_striteri.c \
ft_putchar_fd.c \
ft_putstr_fd.c \
ft_putendl_fd.c \
ft_putnbr_fd.c \
ft_lstnew.c \
ft_lstadd_front.c \
ft_lstsize.c \
ft_lstlast.c \
ft_lstadd_back.c \
ft_lstdelone.c \
ft_lstclear.c \
ft_lstiter.c \
ft_lstmap.c \
ft_printf.c \
ft_utils_1.c \
ft_utils_2.c

OBJ         = $(SRC:.c=.o)

AR          = ar rcs
RM          = rm -f

# Default target: builds ft_printf library
all: $(NAME)

# Create static library from object files
$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

# Compile object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	$(RM) $(OBJ)

# Clean all generated files
fclean: clean
	$(RM) $(NAME)

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re
