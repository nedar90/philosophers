# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nrajabia <nrajabia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/31 11:35:01 by nrajabia          #+#    #+#              #
#    Updated: 2023/08/17 18:51:17 by nrajabia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		:= philo
CC			:= gcc
CFLAGS		:= -Wextra -Wall -Werror
PFLAG		:= -lpthread

HEADERS		:= -I ./include
SRCS		:= $(shell find ./src -iname "*.c")
OBJS		:= ${SRCS:.c=.o}

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\ "

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(HEADERS) $(PFLAG) -o $(NAME)

all: $(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: clean all

.PHONY: all, clean, fclean, re
