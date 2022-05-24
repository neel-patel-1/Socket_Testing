#!/bin/bash

serv_client(){
	./sock_test &
	serv=$!
	nc localhost 4433 &
	nc=$!
}

kill_serv_client(){
	kill -KILL $nc $serv
}

full_test(){
	if [ -z "$( lsmod | grep l5 )" ]; then
		make | grep -E "(Error|error)"
		dmesg -C
		insmod l5.ko
		dmesg | tee ins_l5.out
		dmesg -C
		make sock_test
		serv_client
		dmesg | tee sock_test.out
		kill_serv_client
	else
		rmmod l5.ko
	fi
}


full_test
