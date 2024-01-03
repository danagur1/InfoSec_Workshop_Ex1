#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */

int init_module(void) {
	printk(KERN_INFO "Hello World!\n");
	return 0; /* if non-0 return means init_module failed */
}
void cleanup_module(void) {
	printk(KERN_INFO "Goodbye World!\n");
}
