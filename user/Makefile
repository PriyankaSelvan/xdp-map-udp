KDIR ?= /lib/modules/$(shell uname -r)/source

BIN :=udp_usr.o 
TOOLS:= $(KDIR)/tools
INC = -I$(KDIR)/tools/testing/selftests/bpf \
      -I$(KDIR)/tools/lib \
      -I$(KDIR)/tools/include/uapi

all: $(BIN)

udp_usr.o: udp_usr.c
	gcc $< -o $@ $(INC) $(TOOLS)/lib/bpf/libbpf.a -lelf

clean:
	rm -f udp_usr.o 
