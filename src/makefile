CC = g++
CFLAGS = -std=c++11 -Wall -Wextra -Wvla -c -g
LFLAGS = -std=c++11


OBJS = Cache.o Endpoint.o Organizer.o Network.o Video.o
PROGRAM = Organizer

.PHONY: clean


$(PROGRAM): $(OBJS)
	$(CC) $(LFLAGS) $^ -o $@


%.o: %.cpp
	$(CC) $(CFLAGS) $< -MMD -o $@
	

clean:
	rm $(PROGRAM) *.o *.d




-include $(OBJS:.o=.d)
