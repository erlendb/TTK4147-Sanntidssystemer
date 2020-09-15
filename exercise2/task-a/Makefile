# program executable name
TARGET = output

# compiler flags
CFLAGS = -g -Wall

# linker flags
LDFLAGS = -g

# list of sources
SOURCES = $(shell find . -name "*.c")

# default rule, to compile everything
all: $(TARGET)

# define object files
OBJECTS = $(SOURCES:.c=.o)

# link programs
$(TARGET): $(OBJECTS)
	gcc $(LDFLAGS) -g -o $@ $^

# compile
%.o : %.c
	gcc $(CFLAGS) -std=gnu11 -g -c -o $@ $<

# cleaning
clean:
	rm -f $(TARGET) $(OBJECTS)
