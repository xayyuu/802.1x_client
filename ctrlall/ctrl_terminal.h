#ifndef __CTRL_TERMINAL_H
#define __CTRL_TERMINAL_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include  <netinet/in.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>



#define MAGIC 0x31e2d3

#define LISTEN_PORT     23456
#define LOCALHOST	"127.0.0.1"




struct ctrl_msg
{
	uint32_t msg_magic;
	char msg[16];
};


static void send_msg(const struct ctrl_msg *, int );
static void help(void);
static void encpass(char *, char *);    
static void write_to_file(const char *,const char *,const char *, const char *);

#endif
