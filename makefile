CC = gcc
CFLAGS = -g -O2
LDFLAGS = 
SOURCES = main.c task_manager.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = test_task.exe

all : $(SOURCES) $(EXECUTABLE)

force : clean $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -rf *.o
	rm -rf *.exe