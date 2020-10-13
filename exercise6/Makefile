# program executable name
TARGET = output

# compiler flags
CFLAGS = -g -Wall

# linker flags
LDFLAGS = -g -pthread -lcomedi -lm

# list of sources
SOURCES = $(shell find . -name "*.c")

# default rule, to compile everything
all: $(TARGET)

# define object files
OBJECTS = $(SOURCES:.c=.o)

# link programs
$(TARGET): $(OBJECTS)
	clang $(LDFLAGS) -g -o $@ $^

# compile
%.o : %.c
	clang $(CFLAGS) -std=gnu11 -g -c -o $@ $<

# cleaning
clean:
	rm -f $(TARGET) $(OBJECTS)
