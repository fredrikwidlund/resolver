PROG=resolve
OBJS=main.o graph.o
LDADD=-ldynamic
CFLAGS	= -g -Wall -O2

$(PROG): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDADD)

clean:
	rm -f $(PROG) $(OBJS)
