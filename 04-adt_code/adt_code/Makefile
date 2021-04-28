#CFLAGS+=-Wall -Wextra -ansi -pedantic
CFLAGS+=-Wall -Wextra -std=c11 -pedantic
CFLAGS+=-g
LDLIBS+=-lm
objects = incomplete_types \
		  typedef_vs_define \
		  use_timer1 \
		  use_timer2 \
		  use_timer3

.PHONY: all clean

all: $(objects)

use_timer3: use_timer3.o timer3.o

clean:
	rm -f $(objects) *.o
