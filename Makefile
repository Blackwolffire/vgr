CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -std=c99 -pedantic $(shell sdl2-config --cflags) -Iinc
LDFLAGS = -L. #-lasan
LDLIBS = -lm $(shell sdl2-config --libs)
VPATH = src

RT_NAME = rt
RT_OBJS = graphical_engine.o main.o

all: $(RT_NAME) $(RT_OBJS)

proper:
	$(RM) $(RT_OBJS)

clean: proper
	$(RM) $(RT_NAME)

.PHONY: all $(RT_NAME) proper clean

