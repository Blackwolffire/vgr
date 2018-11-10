CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -std=c99 -pedantic $(shell sdl2-config --cflags) -Iinc
LDFLAGS = -L. #-lasan
LDLIBS = -lm $(shell sdl2-config --libs) -lSDL2_image
VPATH = src

NAME = test
OBJS = graphical_engine.o main.o engine.o physical_engine.o game_object.o \
		scene.o menu.o input.o

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $@
proper:
	$(RM) $(OBJS)

clean: proper
	$(RM) $(NAME)

.PHONY: all $(NAME) proper clean

