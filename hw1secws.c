#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO and for the 						Macros */

#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
//#include <linux/ip.h>
//#include <linux/config.h>

struct nf_hook_ops my_nf_hook_ops;

unsigned int my_nf_hookfn(void *priv, struct sk_buff *skb, const struct nf_hook_state *state){
	printk(KERN_INFO "Dropping a packet\n");
	return NF_DROP;
}

static int __init my_module_init_function(void) {
	my_nf_hook_ops.hook = &my_nf_hookfn;
	my_nf_hook_ops.pf = PF_INET;
	my_nf_hook_ops.hooknum = NF_INET_FORWARD; //NF_IP_FORWARD
	my_nf_hook_ops.priority = NF_IP_PRI_FIRST;
	nf_register_hook(&init_net, &my_nf_hook_ops);
	
	printk(KERN_INFO "Module loaded\n");

	return 0; /* if non-0 return means init_module failed */
}
static void __exit my_module_exit_function(void) {
	nf_register_net_hook(&init_net, &my_nf_hook_ops);
	printk(KERN_INFO "Module removed\n");
}
module_init(my_module_init_function);
module_exit(my_module_exit_function);
