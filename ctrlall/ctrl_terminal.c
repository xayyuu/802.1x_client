/* ********************************************************************************************
*  Used to send control the dial route
*  writer: house
*  kidult1107@126.com
*  2014.4 rewrite
* ******************************************************************************************** */

#include "ctrl_terminal.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h> 
/*
 * int socket(int domain, int type, int protocol);
 */


 
int main(int argc, char *argv[])
{
	struct ctrl_msg cmsg;
	static char user_id[32];
	static char passwd[32];
	char passwd_encp[32];
	static char interface_name[32];
	static char house_conf[32] = "/etc/house_802x_conf";

	
	memset(&cmsg, 0, sizeof(cmsg));
	cmsg.msg_magic =  MAGIC; 
	char *p2argv = 	NULL;

	if( 2 != argc )
	{
		help();
		return -1;
	}
	else
	{
		p2argv = argv[1];
		if( p2argv[0] != '-' )
		{
			help();
			return -1;
		}
		else
		{
			++p2argv;
			
			if (0 == strncmp(p2argv, "cfg", 3)  && 3 == strlen(p2argv))  
			{
				// config, enter your account and password  and save in /etc/house_8021.conf
				printf("Now enter your account and password, that will use in the dial route.\n");
				printf("Enter your account:");
				scanf("%s", user_id); 
				printf("\n");
		
				printf("Enter your passwd:");
				system("stty -echo");
				scanf("%s", passwd); 
				encpass(passwd, passwd_encp);    
				system("stty echo");
				printf("\n\n");
				
				printf("If you don't know the interface name, enter \"ifconfig -all\" in the shell, \
					and then you will see the interface name, and choose one from there.\n"); 
				printf("Enter your interface name:");
				scanf("%s", interface_name);
				printf("\n");
	
				// write to the file 
				write_to_file( house_conf, user_id, passwd_encp, interface_name);
				printf("End config.........\n");
			

			}
			else if(  (0 == strncmp(p2argv, "on", 2) &&  2 == strlen(p2argv))
				|| (0 == strncmp(p2argv, "off", 3) && 3 == strlen(p2argv))
				|| (0 == strncmp(p2argv, "over", 4)  && 4 == strlen(p2argv))  )
			{
			   
				strncpy( (cmsg.msg), p2argv, strlen(p2argv) );
				send_msg(&cmsg, sizeof(cmsg));
			}
			else 
			{
				help();
				return -1;
			}
		}
	}

		
	return 0;
		
}

static void send_msg(const struct ctrl_msg *pmsg, int msg_len)
{
	int ctrl_sock;
	ctrl_sock = socket(AF_INET, SOCK_DGRAM, 0);
	
	socklen_t len = sizeof(struct sockaddr_in);
	struct  sockaddr_in destaddr;

	if( -1 == ctrl_sock )
	{
		perror("Create sock failed");
		exit(-1);
	}
	destaddr.sin_family = AF_INET;
	destaddr.sin_port = htons(LISTEN_PORT);
	inet_pton(AF_INET, LOCALHOST, &destaddr.sin_addr);

	int nwrite;
	nwrite = sendto(ctrl_sock, pmsg, msg_len, 0, (struct sockaddr *) &destaddr, len);
	close(ctrl_sock);
	printf("%d bytes were sent from house_ctrl route.\n", nwrite);
}





static void help(void)
{
	printf("Usage: ./house_ctrl  [options] \n\n"); 
	printf("OPTIONS: \n"); 
	printf("			-on, logon\n"); 
	printf("			-off, logoff\n"); 
	printf("			-over, terminal\n"); 
	printf("			-cfg, config_file\n"); 
	printf("			-h, help\n"); 
	printf("EXAMPLE:\n"); 
	printf("			./house_ctrl -on\n\n");

}



static void encpass(char *original, char *out)
{
	memset(out, 0, 32);

	int i, len = strlen(original);
	for(i = 0; i < len; i++)
	{
	        out[i] = (char)((signed char)original[i] ^ (signed char)(MAGIC + i));
   	 }
    	out[i] = '\0';
}

		


    
static void write_to_file(const char *filename,const char *user_acnt,const char *pawd, const char * itfc_name)
{
        FILE *fp;
        fp = fopen(filename, "w");
	if( NULL == fp)
	{
		printf(" create file failed,  maybe need to change to the root account.\n");
		exit(-1);
	}

        fprintf(fp, user_acnt);
        fprintf(fp, "\n");
        fprintf(fp, pawd);
        fprintf(fp, "\n");
        fprintf(fp, itfc_name);


        fclose(fp);

}

