

static int l5_init(struct sock *sk);
static void l5_update(struct sock *sk, struct proto *p,
		void (*write_space)(struct sock *sk));
static int l5_get_info(const struct sock *sk, struct sk_buff *skb);
static void l5_release(struct sock *sk);
static size_t l5_get_info_size(const struct sock *sk);


static struct tcp_ulp_ops l5_ops __read_mostly = {
	.name = "l5",
	.owner = THIS_MODULE,
	.init = l5_init,
	.update = l5_update,
	.get_info = l5_get_info,
	.get_info_size = l5_get_info_size,
	.release = l5_release,
};
