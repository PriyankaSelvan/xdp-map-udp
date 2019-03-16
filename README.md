# xdp-map-udp
Simple XDP program to use BPF maps from kernel and user space. 

### The programs

The kernel XDP program 
- Drops all UDP packets that arrive at the interface it is loaded to
- Counts the number of packets it drops and writes it to a BPF map with key as the UDP protocol number (17)

The user XDP program 
- Loads the kernel object file to the interface given in the command line argument
- Reads from the BPF map and displays the result

### Running the programs

First compile the kernel program
```
cd kernel
make
```

Next compile the user program
```
cd ../user
make
```

Run the user program with the interface to load the XDP program to
```
sudo ./udp_usr.o <interface-name>
```

Send UDP traffic to the interface from another node
```
iperf -c 10.10.1.1 -u -n 1G -b 100M
```

Enter an integer to go ahead with the program and see the number of packets dropped.

