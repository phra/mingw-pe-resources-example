EXECUTABLE=hello.exe

# CC=x86_64-w64-mingw32-gcc
CC=x86_64-w64-mingw32-clang
CCFLAGS=-municode -Wall -pedantic
LDFLAGS=-lgdi32
WINDRES=x86_64-w64-mingw32-windres

src = $(wildcard *.c)
obj = $(src:.c=.o)

all: hello.res myprog

hello.res: hello.rc
	$(WINDRES) hello.rc -O coff -o hello.res

myprog: $(obj) 
	$(CC) $(CCFLAGS) -o $(EXECUTABLE) $^ $(LDFLAGS) hello.res

.PHONY: clean
clean:
	rm -rf $(obj) $(EXECUTABLE) hello.res
