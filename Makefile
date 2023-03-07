# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: meltremb <meltremb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/27 12:12:14 by meltremb          #+#    #+#              #
#    Updated: 2023/03/07 15:09:45 by meltremb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#------------------------------------------------------------------------------#
#                                  GENERICS                                    #
#------------------------------------------------------------------------------#

# Special variables
DEFAULT_GOAL: all
.DELETE_ON_ERROR: $(NAME)
.PHONY: all bonus clean fclean re

# Hide calls
export VERBOSE	=	TRUE
ifeq ($(VERBOSE),TRUE)
	HIDE =
else
	HIDE = @
endif


#------------------------------------------------------------------------------#
#                                VARIABLES                                     #
#------------------------------------------------------------------------------#

# Compiler and flags
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra
RM		=	rm -rf

# Libraries
LDIR	=	reworked-libft/
LIBFT	=	libft.a

# Dir and file names
NAME	=	pipex
SRCDIR	=	src/
OBJDIR	=	bin/
SRCS	=	src/pipex.c \
			src/data_utils.c \

OBJS	=	$(patsubst $(SRCDIR)%.c,$(OBJDIR)%.o,$(SRCS))


#------------------------------------------------------------------------------#
#                                 TARGETS                                      #
#------------------------------------------------------------------------------#

all: $(NAME)

# Generates output file
$(NAME): $(OBJS) $(LDIR)/$(LIBFT)
	$(HIDE)$(CC) $(CFLAGS) $(LDIR)/$(LIBFT) -o $@ $^

$(OBJS): $(OBJDIR)%.o : $(SRCDIR)%.c
		$(HIDE)mkdir -p $(OBJDIR)
		$(HIDE)$(CC) $(CFLAGS) -c $< -o $@

# Generates libft
$(LDIR)/$(LIBFT):
				$(HIDE)$(MAKE) -C $(LDIR)

leaks: all
	$(HIDE) valgrind --show-leak-kinds=all --trace-children=yes --leak-check=full --track-fds=yes

# Removes objects
clean:
	$(HIDE)$(RM) $(OBJS)
	$(HIDE)$(MAKE) -C $(LDIR) $(MAKE) clean

# Removes objects and executables
fclean: clean
	$(HIDE)$(RM) $(NAME)
	$(HIDE)$(MAKE) -C $(LDIR) $(MAKE) fclean

# Removes objects and executables and remakes
re: fclean all
