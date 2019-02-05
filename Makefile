# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/26 23:18:40 by cempassi          #+#    #+#              #
#    Updated: 2019/02/04 23:50:12 by cempassi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
LIB = $(LPATH)libft.a
LIBDB = $(LPATH)libftdb.a

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

INCS += ft_ls.h 

SRCS += main.c
SRCS += args.c
SRCS += list.c
SRCS += listing.c
SRCS += display.c
SRCS += basic_printing.c
SRCS += long_printing.c
SRCS += formatting.c
SRCS += sorting.c
SRCS += colors.c
SRCS += xattr.c

DSYM = $(NAME).dSYM

OBJS = $(patsubst %.c, $(OPATH)%.o, $(SRCS))

vpath  %.c srcs/
vpath  %.h includes/

all : $(LIB) $(NAME)

run : all
	./ft_ls

debug : $(LIBDB) $(SRCS)
	$(MAKE) -C $(LPATH) debug
	$(DEBUG) $(DFLAGS) $(CFLAGS) -o $(NAME) $^ 

$(NAME): $(LIB) $(OPATH) $(OBJS) $(INCS)
	$(CC) -o $@ $< $(OBJS)

$(OBJS) : $(OPATH)%.o : %.c $(INCS)
	$(COMPILE) $(CFLAGS) $< -o $@

$(LIB) :
	$(MAKE) -C $(LPATH)

$(LIBDB) :
	$(MAKE) -C $(LPATH) debug

$(OPATH):
	$(MKDIR) $@

clean :
	$(MAKE) -C $(LPATH) clean
	$(CLEANUP) $(OBJS)
	$(CLEANUP) $(OPATH)
	$(CLEANUP) $(DSYM)

fclean : clean
	$(MAKE) -C $(LPATH) fclean
	$(CLEANUP) $(OPATH)
	$(CLEANUP) $(NAME)

re: fclean all

.PHONY: all clean fclean debug
