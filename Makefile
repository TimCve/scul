CC = gcc
MKLIB = ar -cvq
LIBOBJ := $(subst Lib/,,$(patsubst %.c,%.o,$(wildcard Lib/*.c)))
TESTS := $(patsubst %.c,%,$(wildcard Tests/*.c))

all: libscul.a
clean:
	-rm *.a *.o
	-rm $(TESTS)

tests: libscul.a $(TESTS)

$(TESTS): %: %.c
	$(CC) $^ -o $@ -L. -lscul -lpthread

libscul.a: $(LIBOBJ)
	$(MKLIB) $@ $^

$(LIBOBJ): %.o: Lib/%.c
	$(CC) -o $@ -c $^
