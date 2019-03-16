#include "bpf_util.h"
#include "bpf/bpf.h"
#include "bpf/libbpf.h"
#include <net/if.h>
#include <linux/if_link.h>

int main(int argc, char** argv)
{
	struct bpf_object *obj;
	int prog_fd;

	int map_fd;

	if(argc != 2){
		printf("\nPlease enter interface to load to");
		return 1;
	}

	static __u32 xdp_flags = XDP_FLAGS_DRV_MODE;
	int ifindex = if_nametoindex(argv[1]);

	struct bpf_prog_load_attr prog_load_attr = {
		.prog_type = BPF_PROG_TYPE_XDP,
		.file = "../kernel/udp_kern.o",
	};

	struct bpf_map *map = bpf_object__find_map_by_name(obj, "dpcnt");

	unsigned int nr_cpus = bpf_num_possible_cpus();
	__u64 values[nr_cpus];
	__u32 key = 17;
	__u64 sum = 0;
	int cpu;

	if(!map){
		printf("\nFinding a map obj file failed");
		return 1;
	}

	if(bpf_prog_load_xattr(&prog_load_attr, &obj, &prog_fd)){
		printf("\nLoading kernel program failed");
		return 1;
	}

	if(bpf_set_link_xdp_fd(ifindex, prog_fd, xdp_flags) < 0) {
		printf("\nlink set xdp fd failed");
		return 1;
	}
        
	map_fd = bpf_map__fd(map);

        if(bpf_map_lookup_elem(map_fd, &key, &values)){
		printf("\nLookup failed");
		return 1;
	}
	for(cpu = 0; cpu < nr_cpus; cpu++)
		sum += values[cpu];

	printf("\n Key %u value %llu\n", key, sum);

	return 0;

}
