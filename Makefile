src = $(wildcard *.c)
obj = $(src:.c=.o)

LDFLAGS = -lpthread -lrt

chat: $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) chat