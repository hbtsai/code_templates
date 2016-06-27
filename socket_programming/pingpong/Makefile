# Makefile template for shared library

CC = gcc # C compiler
CFLAGS = -fPIC -Wall -Wextra -O2 -g # C flags
LDFLAGS = # linking flags
RM = rm -f  # rm command
SERVER_EXEC = server
CLIENT_EXEC = client

SERVER_SRCS = server.c # source files
CLIENT_SRCS = client.c 
SERVER_OBJS = $(SERVER_SRCS:.c=.o)
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)

.PHONY: all
all: ${SERVER_EXEC} ${CLIENT_EXEC}

$(SERVER_EXEC): $(SERVER_OBJS)
	$(CC) ${LDFLAGS} -o $@ $^

$(CLIENT_EXEC): $(CLIENT_OBJS)
	$(CC) ${LDFLAGS} -o $@ $^

$(SERVER_SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

$(CLIENT_SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

#include $(SRCS:.c=.d)

.PHONY: clean
clean:
	-${RM} ${CLIENT_EXEC} ${SERVER_EXEC} ${SERVER_OBJS} $(CLIENT_OBJS) $(SERVER_SRCS:.c=.d) $(CLIENT_SRCS:.c=.d)
