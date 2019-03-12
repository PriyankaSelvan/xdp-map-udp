#include "bpf_util.h"
#include "bpf/bpf.h"
#include "bpf/libbpf.h"

int main()
{
	struct bpf_object *obj;
	int prog_fd;

	struct bpf_prog_load_attr prog_load_attr = {
		.prog_type = BPF_PROG_TYPE_XDP,
		.file = "../kernel/udp_kern.o",
	};

	if(bpf_prog_load_xattr(&prog_load_attr, &obj, &prog_fd))
		return 1;

	return 0;

}
