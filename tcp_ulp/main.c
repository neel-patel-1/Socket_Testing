#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdlib.h> //malloc
#include <string.h> //strerror
#include <stdio.h>
#include <errno.h> //errno
#include <unistd.h> // close

int main(){

	int tcp_socket;
	struct sockaddr_in  addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(4433);

	tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
	int optval = 1;
	if ( setsockopt(tcp_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) != 0 )
	{
		printf("sockopt: %s", strerror(errno));
		return 1;
	}
	if ( bind(tcp_socket, (struct sockaddr*)&addr, sizeof(addr)) < 0 )
		printf("bind failed: %s\n", strerror(errno));
	listen(tcp_socket, 4096);
	accept(tcp_socket, NULL, NULL );

	setsockopt(tcp_socket, SOL_TCP, TCP_ULP, "l5", sizeof("l5"));
	close(tcp_socket);
}
