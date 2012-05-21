#include <linux/device.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/string.h>


MODULE_AUTHOR("Chang ShaoRan");
MODULE_LICENSE("GPL");

extern struct device my_bus_dev;
extern struct bus_type my_bus_type;

static void my_dev_release(struct device *dev)
{
	printk("[Call my_dev_release!]\n");
}

struct device my_dev = 
{
	.init_name = "my_dev",
	.bus = &my_bus_type,
	.parent = &my_bus_dev,
	.release = my_dev_release,		/* ������������У�����Ϊ�� */
};

/* �����ļ��Ķ����� */
static ssize_t mydev_show(struct device *dev,struct device_attribute *attr,
				char *buf)
{
	return sprintf(buf,"%s\n","This is my device!");
}

/* �����ṹ�����������ļ� */
static DEVICE_ATTR(dev,S_IRUGO,mydev_show,NULL);

static int __init my_device_init(void)
{
	int ret = 0;
	printk("[Call my_device_init!]\n");	

	/* ע���豸 */
	ret = device_register(&my_dev);
	if(ret)
		return ret;

	/* ���������ļ� */
	ret = device_create_file(&my_dev,&dev_attr_dev);

	return ret;
}

static void __exit my_device_exit(void)
{
	printk("[Call my_device_exit!]\n");	
	device_unregister(&my_dev);
}

module_init(my_device_init);
module_exit(my_device_exit);

