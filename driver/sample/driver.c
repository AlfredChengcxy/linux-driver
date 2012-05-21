#include <linux/device.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/string.h>

MODULE_AUTHOR("Chang ShaoRan");
MODULE_LICENSE("GPL");

extern struct bus_type my_bus_type;

/* �����ṹ�� probe �� remove ��Ա�������ֱ��������
 * ƥ���������ϵĶ�Ӧ�豸��һ������ʱ���� */
static int my_probe(struct device *dev)
{
	printk("[Driver found device which my driver can handle!]\n");
	return 0;
}
static int my_remove(struct device *dev)
{
	printk("[Driver found device unpluged!]\n");
	return 0;
}

struct device_driver my_driver =
{
	.name = "my_dev",
	.bus = &my_bus_type,
	.probe = my_probe,
	.remove = my_remove,
};

/* �����ļ��Ķ����� */
static ssize_t my_drv_show(struct device_driver *driver,char *buf)
{
	return sprintf(buf,"%s\n","This is a driver!");
}
/* ���������ļ��ṹ */
static DRIVER_ATTR(drv,S_IRUGO,my_drv_show,NULL);

static int __init my_driver_init(void)
{
	int ret = 0;
	
	printk("[Call my_driver_init!]\n");
	
 	/* ע������ */
	if(ret = driver_register(&my_driver))
		return ret;
	/* ���������ļ� */
	ret = driver_create_file(&my_driver,&driver_attr_drv);

	return ret;
}

static void __exit my_driver_exit(void)
{
	printk("[Call my_driver_exit!]\n");
	
	driver_unregister(&my_driver);
}

module_init(my_driver_init);
module_exit(my_driver_exit);

