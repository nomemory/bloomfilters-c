CC = gcc
CFLAGS = -Wall -Wextra -Werror

.o: @.c @.h
  $(CC) $(CFLAGS) $@.c -o $@

OBJECTS = bitutil.o bloom.o hashf.o

bloom: $(OBJECTS)
  $(CC) $(CFLAGS) $(OBJECTS) $@.c -o $@

clean:
  -rm *.o
