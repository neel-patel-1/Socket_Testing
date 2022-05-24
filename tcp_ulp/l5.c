
#include <linux/module.h>
#include <linux/uio.h> //iov_for_each
#include <net/tcp.h> //struct tcp_ulp_ops
#include <net/sock.h> // struct sock
#include <net/inet_common.h>

#include "l5.h"

MODULE_LICENSE("GPL");

static struct proto l5_prot;

static int l5_init(struct sock *sk){
	if ( sk->sk_state != TCP_ESTABLISHED )
		return -ENOTCONN;
	#ifdef L5DEBUG
	printk( KERN_INFO "Init L5 Prot\n" );
	#endif
	sk->sk_prot = &l5_prot;

	return 0;
}

static void l5_update(struct sock *sk, struct proto *p,
		void (*write_space)(struct sock *sk))
{
	#ifdef L5DEBUG
	printk( KERN_INFO "Update l5 prot\n" );
	#endif
}

static int l5_get_info(const struct sock *sk, struct sk_buff *skb)
{
	#ifdef L5DEBUG
	printk ( KERN_INFO "l5 getinfo\n" );
	#endif
	return 0;
}

static void l5_release(struct sock *sk){
	#ifdef L5DEBUG
	printk (KERN_INFO "l5_release\n" );
	#endif
}	

static size_t l5_get_info_size(const struct sock *sk){
	#ifdef L5DEBUG
	printk (KERN_INFO "l5 getinfo size\n" );
	#endif
	size_t size = 0;
	return size;
}

int l5p_sendmsg(struct sock *sk, struct msghdr *msg, size_t size)
{
	struct iov_iter data = msg->msg_iter;

	#ifdef L5DEBUG
	printk( KERN_INFO "l5 sendmsg\n" );
	printk( KERN_INFO "tcp msg: \n" );
	#endif


	#ifdef L5DEBUG
	printk( KERN_INFO "%s\n", (char *) &data );
	#endif
	return 0;
}

static void __exit l5_unregister(void){
	#ifdef L5DEBUG
	printk (KERN_INFO "l5 unregister \n" );
	#endif
	tcp_unregister_ulp(&l5_ops);
}
static int __init l5_register(void)
{
	#ifdef L5DEBUG
	printk (KERN_INFO "l5 register \n" );
	#endif
	l5_prot		= tcp_prot;
	//l5_prot.setsockopt	= l5p_setsockopt;
	//l5_prot.getsockopt	= l5p_getsockopt;
	l5_prot.sendmsg	= l5p_sendmsg;
	//l5_prot.recvmsg	= l5p_recvmsg;
	tcp_register_ulp(&l5_ops);
	return 0;
}

module_init(l5_register);
module_exit(l5_unregister);
