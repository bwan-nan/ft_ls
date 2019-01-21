# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/26 23:18:40 by cempassi          #+#    #+#              #
#    Updated: 2019/01/21 19:03:44 by bwan-nan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
LIB = libftprintf.a

CC = Clang
COMPILE = $(CC) -c
DEBUG = $(CC) -g

MKDIR = mkdir -p
CLEANUP = rm -rf

WFLAGS += -Wall
WFLAGS += -Werror
WFLAGS += -Wextra
DFLAGS = -fsanitize=address
IFLAGS = -I $(IPATH) -I $(LIPATH)
CFLAGS = $(WFLAGS) $(IFLAGS)

OPATH = obj/
SPATH = srcs/
IPATH = includes/
LPATH = libft/
LIPATH = libft/includes/

INCS += 
SRCS += main.c
SRCS += ft_ls.c
SRCS += display.c
SRCS += formatting.c
DSYM = $(NAME).dSYM

OBJS = $(patsubst %.c, $(OPATH)%.o, $(SRCS))

vpath  %.c srcs/
vpath  %.h includes/

all : $(LIB) $(NAME)

debug : $(LIB) $(SRCS)
	$(DEBUG) $(DFLAGS) $(CFLAGS) -o $(NAME) $^

$(NAME): $(LIB) $(OPATH) $(OBJS) $(INCS)
	$(CC) -o $@ $(LIB) $(OBJS)

$(OBJS) : $(OPATH)%.o : %.c $(INCS)
	$(COMPILE) $(CFLAGS) $(IFLAGS) $< -o $@

$(LIBDB) :
	$(MAKE) -C $(LPATH) debug

$(OPATH):
	$(MKDIR) $@

clean :
	$(CLEANUP) $(OBJS)
	$(CLEANUP) $(OPATH)
	$(CLEANUP) $(DSYM)

fclean : clean
	$(CLEANUP) $(OPATH)
	$(CLEANUP) $(NAME)

re: fclean all

.PHONY: all clean fclean debug
