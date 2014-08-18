#ifndef __HOUSE_DIAL_H
#define __HOUSE_DIAL_H

#include "public.h"
#include "house_network.h"
#include <stdio.h> 
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <net/if.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <linux/if_ether.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/types.h>
#include <fcntl.h>
#include <pthread.h>


void sig_action(int signo);
void *thread_msg_receiver(void *args);
void get_from_file(char *, char *, char *, char *);

#endif
