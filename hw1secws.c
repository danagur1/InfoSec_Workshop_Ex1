#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO and for the 						Macros */

#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
//#include <linux/ip.h>
//#include <linux/config.h>

unsigned int my_nf_hookfn(void *priv, struct sk_buff *skb, const struct nf_hook_state *state){
	return NF_DROP;
}

static int __init my_module_init_function(void) {
	struct nf_hook_ops my_nf_hook_ops;
	my_nf_hook_ops.hook = &my_nf_hookfn;
	my_nf_hook_ops.pf = PF_INET;
	my_nf_hook_ops.hooknum = 2; //NF_IP_FORWARD
	nf_register_net_hook(NULL, &my_nf_hook_ops);
	
	printk(KERN_INFO "Hello World!\n");

	return 0; /* if non-0 return means init_module failed */
}
static void __exit my_module_exit_function(void) {
	nf_register_net_hook(NULL, &my_nf_hook_ops);
	printk(KERN_INFO "Goodbye World!\n");
}
module_init(my_module_init_function);
module_exit(my_module_exit_function);
