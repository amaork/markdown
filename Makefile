CC			=	g++
CPPFLAGS	=	-Wall -g	
LDSHFLAGS	=	-rdynamic -shared 
ARFLAGS		=	rcv
TARGETS		=	libmarkdown.a libmarkdown.so test	

.PHONY:all clean

all:$(TARGETS)

clean:
	$(RM) *.o *~ depend $(TARGETS)

test:test.o markdown.o

libmarkdown.a:markdown.o
	$(AR) $(ARFLAGS) $@ $^

libmarkdown.so:markdown.o
	$(CC) $(LDSHFLAGS) -o $@ $^

depend:$(wildcard *.cpp *.h)
	$(CC) $(CPPFLAGS) -M $^ > $@

-include depend
