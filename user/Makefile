KDIR ?= /lib/modules/$(shell uname -r)/source

BIN :=udp_usr.o 
INC = -I$(KDIR)/tools/testing/selftests/bpf \
      -I$(KDIR)/tools/lib \

all: $(BIN)

udp_usr.o: udp_usr.c
	gcc -c $< -o $@ $(INC)

clean:
	rm -f udp_usr.o 
