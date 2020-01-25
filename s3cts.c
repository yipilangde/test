#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/input.h>
#include <linux/init.h>
#include <linux/serio.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/clk.h>
#include <asm/io.h>
#include <asm/irq.h>
#include <asm/plat-s3c24xx/ts.h>
#include <asm/arch/regs-adc.h>
#include <asm/arch/regs-gpio.h>

static struct input_dev *s3c_ts_dev;

static int s3c_ts_init(void)
{
	struct clk* clk; = clk_get(NULL,"adc");
	
	
	//1、分配一个input_dev结构体
	s3c_ts_dev = input_allocate_device();
	//2、设置
	//2.1能产生哪类事件
	set_bit(EV_KEY,s3c_ts_dev->evbit);
	set_bit(EV_ABS,s3c_ts_dev->evbit);
	//2.2能产生这类事件里的哪些事件
	set_bit(BTN_TOUCH,buttons_dev->keybit);
	
	input_set_abs_params(s3c_ts_dev,ABS_X,0,0x3FF,0,0);
	input_set_abs_params(s3c_ts_dev,ABS_Y,0,0x3FF,0,0);
	input_set_abs_params(s3c_ts_dev,ABS_PRESSURE,0,1,0,0);
	 
	//3、注册
	input_register_device(s3c_ts_dev);
	
	//4、硬件相关的操作
	//4.1使能时钟(CLKCON[15])
	clk = clk_get(NULL,"adc");
	clk_enable(clk);
	//4.2
	
	
	
	
	return 0;
}

static void s3c_ts_exit(void)
{
	
}

module_init(s3c_ts_init);
module_exit(s3c_ts_exit);
MODULE_LICENSE("GPL");