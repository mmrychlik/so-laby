#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/timer.h>
#include <linux/jiffies.h>
#include <linux/sched/loadavg.h>

static struct timer_list my_timer;
static unsigned int interval = 10; // domyślnie 10 sekund

module_param(interval, uint, 0644);
MODULE_PARM_DESC(interval, "Czas w sekundach między zapisami obciążenia CPU");

void monitor_cpu_usage(struct timer_list *t) {
    printk(KERN_INFO "Obciążenie CPU: %lu%%\n", (unsigned long)(avenrun[0] * 100 / FIXED_1));
    mod_timer(&my_timer, jiffies + msecs_to_jiffies(interval * 1000));
}

static int __init monitor_init(void) {
    timer_setup(&my_timer, monitor_cpu_usage, 0);
    mod_timer(&my_timer, jiffies + msecs_to_jiffies(interval * 1000));
    printk(KERN_INFO "Moduł monitorowania CPU został załadowany\n");
    return 0;
}

static void __exit monitor_exit(void) {
    del_timer(&my_timer);
    printk(KERN_INFO "Moduł monitorowania CPU został wyładowany\n");
}

module_init(monitor_init);
module_exit(monitor_exit);

MODULE_LICENSE("GPL");