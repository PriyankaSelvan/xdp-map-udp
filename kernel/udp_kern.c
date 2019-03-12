#define KBUILD_MODNAME "foo"
#define asm_volatile_goto(x...)
#include <uapi/linux/bpf.h>
#include <linux/in.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <linux/if_vlan.h>
#include <linux/ip.h>
#include <linux/ipv6.h>
#include "bpf_helpers.h"

static __always_inline
int parse_ipv4(void *data, u64 nh_off, void *data_end)
{
	struct iphdr *iph = data + nh_off;

	if(iph+1 > data_end)
		return 0;
	return iph->protocol;
}

SEC("xdp_drop_UDP")
int xdp_prog_drop_all_UDP(struct xdp_md *ctx)
{
	void *data_end = (void *)(long)ctx->data_end;
	void *data = (void *)(long)ctx->data;
	struct ethhdr *eth = data;
	u64 nh_off;
	u32 ipproto = 0;

	nh_off = sizeof(*eth);
	if(data + nh_off > data_end)
		return XDP_ABORTED;

	if(eth->h_proto == htons(ETH_P_IP))
		ipproto = parse_ipv4(data, nh_off, data_end);

	if(ipproto == IPPROTO_UDP)
		return XDP_DROP;

	return XDP_PASS;
}
