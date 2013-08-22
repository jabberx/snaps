CC=gcc
CFLAGS=-c -O3 -ffast-math -fomit-frame-pointer
LDFLAGS=-lmingw32 -lSDLmain -mwindows -lSDL -static-libgcc
SOURCES=main.c perlin.c project.c snapshot.c fillholes.c colors.c cloud.c \
		lookfly.c SDL_plus.c data.c plyreader.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=a.exe
RM=del

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) $(OBJECTS) $(EXECUTABLE)
