/*
 *  chardev.c: Creates a read-only char device that says how many times
 *  you've read from the dev file
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/list.h>
#include <asm/uaccess.h>    /* for put_user */
#include <charDeviceDriver.h>
#include <linux/string.h>
#include <linux/vmalloc.h>

 
static char mymsg[BUF_LEN]= {0};
struct Message {
    struct list_head list;
    char* s;

};




MODULE_LICENSE("GPL");

/*
 * This function is called whenever a process tries to do an ioctl on our
 * device file. We get two extra parameters (additional to the inode and file
 * structures, which all device functions get): the number of the ioctl called
 * and the parameter given to the ioctl function.
 *
 * If the ioctl is write or read/write (meaning output is returned to the
 * calling process), the ioctl call returns the output of this function.
 *
 */
static struct Message * node;
static struct Message hello;
DEFINE_MUTEX(devLock);

struct list_head head;

struct list_head* tail;
int temp;
static int lencount = 0;
/*
 * This function is called when the module is loaded
 * You will not need to modify it for this assignment
 */

int init_module(void)
{
	struct Message * two;
	struct Message *three;
	struct Message* one ;
	struct Message * last;
	struct Message * semi;

    Major = register_chrdev(0, DEVICE_NAME, &fops);

    if (Major < 0) {
        printk(KERN_ALERT "Registering char device failed with %d\n", Major);
        return Major;
    }

    printk(KERN_INFO "I was assigned major number %d. To talk to\n", Major);
    printk(KERN_INFO "the driver, create a dev file with\n");
    printk(KERN_INFO "'mknod /dev/%s c %d 0'.\n", DEVICE_NAME, Major);
    printk(KERN_INFO "Try various minor numbers. Try to cat and echo to\n");
    printk(KERN_INFO "the device file.\n");
    printk(KERN_INFO "Remove the device file and module when done.\n");


		INIT_LIST_HEAD(&head);
    printk(KERN_INFO "init\n");
	
/*
one =(struct Message *) vmalloc(sizeof(struct Message*));
one->s = "dadas";
list_add_tail(&one->list, &head);
//	node = list_last_entry(&head, struct Message, list);
printk(KERN_INFO "all added \n");
one =(struct Message *) vmalloc(sizeof(struct Message*));
one->s = "ddaddasdadsad";
list_add_tail(&one->list, &head);
printk(KERN_INFO "all added 2 \n");
one=NULL;
one = list_last_entry(&head, struct Message, list);

printk(KERN_INFO "got entry %s \n", one->s);
list_del(&one->list);
printk(KERN_INFO "deleted \n");
	
one = list_last_entry(&head, struct Message, list);
*/
/*
one =kmalloc(sizeof(struct Message), GFP_KERNEL);

one->s = "dadas";

list_add_tail(&one->list, &head);

//	node = list_last_entry(&head, struct Message, list);

printk(KERN_INFO "all added \n");

one =kmalloc(sizeof(struct Message), GFP_KERNEL);
one->s = "ddaddasdadsad";

list_add_tail(&one->list, &head);

printk(KERN_INFO "all added 2 \n");

one=NULL;

one = list_last_entry(&head, struct Message, list);



printk(KERN_INFO "got entry %s \n", one->s);

list_del(&one->list);

printk(KERN_INFO "deleted \n");

	

one = list_last_entry(&head, struct Message, list);
printk(KERN_INFO "got entry %s \n", one->s);
*/
    return SUCCESS;
}

/*
 * This function is called when the module is unloaded
 */
void cleanup_module(void)
{
    /*  Unregister the device */
    unregister_chrdev(Major, DEVICE_NAME);
}

/*
 * Methods
 */

 /*
  * Called when a process tries to open the device file, like
  * "cat /dev/mycharfile"
  */
static int device_open(struct inode* inode, struct file* file)
{



    // struct Message * last;
    mutex_lock(&devLock);
    if (Device_Open) {
        mutex_unlock(&devLock);
        return -EBUSY;
    }
    Device_Open++;
    mutex_unlock(&devLock);

    //last = list_last_entry(&head, struct Message, list);
    /* result of function calls */

  //  msg_Ptr = last->s ;
    try_module_get(THIS_MODULE);

    return SUCCESS;
}

/* Called when a process closes the device file. */
static int device_release(struct inode* inode, struct file* file)
{
    mutex_lock(&devLock);
    Device_Open--;      /* We're now ready for our next caller */
    mutex_unlock(&devLock);
    /*
     * Decrement the usage count, or else once you opened the file, you'll
     * never get get rid of the module.
     */
    module_put(THIS_MODULE);

    return 0;
}

/*
 * Called when a process, which already opened the dev file, attempts to
 * read from it.
 * This is just an example about how to copy a message in the user space
 * You will need to modify this function
 */
static ssize_t device_read(struct file* filp,   /* see include/linux/fs.h   */
    char* buffer,    /* buffer to fill with data */
    size_t length,   /* length of the buffer     */
    loff_t* offset)
{

    return 0;
}

/* Called when a process writes to dev file: echo "hi" > /dev/hello  */
static ssize_t
device_write(struct file* filp, const char* buff, size_t len, loff_t* off)
{
	
	
	
	if (list_empty(&head)){
    		//INIT_LIST_HEAD(&head);
    		printk(KERN_INFO "already created \n");
	}
	memset(mymsg, 0, 80);
	struct Message *new;

	struct Message * prevv;
	struct Message * last ;
	
        int i;
        char *mes;
	mutex_lock(&devLock);
        for(i = 0 ; i < len ; i++){
		 get_user(mymsg[i],buff +i);

	}
	
	

	
        
        new = kmalloc(sizeof(struct Message), GFP_KERNEL);
        new->s = mymsg;
        
        
        if (new->s != "hello"){
        	 last = list_last_entry(&head,struct Message, list);
       	 printk(KERN_INFO "old last %s\n %p", last->s, last);
       	 printk(KERN_INFO "%p address\n",&head);
        }
       
        list_add_tail(&new->list, &head);
	
	printk(KERN_INFO "writte next %s %p \n", new->s, new);
		 
	last = list_last_entry(&head,struct Message, list);
	printk(KERN_INFO "new last %s", last->s);
	mutex_unlock(&devLock);
        return len;

}
//module_init(listinit);
//module_exit(listexit);
