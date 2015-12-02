CC		= g++
CFLAGS		= -g -c -Wall -std=c++11 -stdlib=libc++
LDFLAGS		=
SOURCES		= market_server.cc
INCLUDES	= -I.
OBJECTS		= $(SOURCES:.cc=.o)
TARGET		= market_server

.all: $(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cc.o:
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

.PHONY: clean
clean:
	rm -rf $(OBJECTS) $(TARGET)
