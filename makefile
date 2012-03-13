CC = gcc
CFLAGS = -g -O2
LDFLAGS = 
SOURCES = main.c task_manager.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = test_task

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o main.exe

%.o : %.c
	$(CC) $(CFLAGS) -c $<
