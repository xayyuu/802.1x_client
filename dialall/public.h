#ifndef __PUBLIC_H_
#define __PUBLIC_H_

#include <stdint.h>
#include <stdio.h>

#define MAGIC 0x31e2d3
#define LISTEN_PORT 23456
#define LOCALHOST   "127.0.0.1"

struct ctrl_msg
{
	uint32_t msg_magic;	
	char msg[16];
};

#define PASSWDFILE "/etc/house_802x_conf"
char user_id[32];
char passwd[32];
char interface_name[32];


void enc_pass(char *, char *);
void print_mac(char *src);

#endif
