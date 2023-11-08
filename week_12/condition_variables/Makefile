CC     := gcc
CFLAGS := -Wall -Werror -I../include 

SRCS   := join.c \
	join_modular.c \
	join_no_lock.c \
	join_no_state_var.c \
	join_spin.c \
	pc.c \
	pc_single_cv.c \

OBJS   := ${SRCS:c=o}
PROGS  := ${SRCS:.c=}

.PHONY: all
all: ${PROGS}

${PROGS} : % : %.o Makefile
	${CC} $< -o $@ -pthread

clean:
	rm -f ${PROGS} ${OBJS}

%.o: %.c Makefile
	${CC} ${CFLAGS} -c $<
