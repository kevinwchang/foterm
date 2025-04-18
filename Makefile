OBJS = main.o print.o intro.o pass.o wordParse.o getline.o getdelim.o shim.o

foterm: ${OBJS}
	cc -i -o $@ ${OBJS} -lcurses -ltermcap

%.o: %.c

clean:
	rm -f *.o foterm
