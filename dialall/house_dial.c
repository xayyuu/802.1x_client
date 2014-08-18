/* **********************************************************
*  Used to dial packet to the switcher
*  author: house
*  kidult1107@126.com
*  2014.4 rewrite
* ********************************************************** */

#include "house_dial.h"

int main()
{
	/* global value, in "house_network.h" */
	log_flag = OFF;  
	status = OFFLINE; 

	pthread_t tid;

	/* user_id, passwd, interface_name: global var, defines in "public.h", char [32] */
        get_from_file(PASSWDFILE, user_id, passwd, interface_name);
	init_dial_env();


	signal(SIGINT, sig_action);

	// thread_msg_receiver contains "logon()" and "logoff()"  operation
	int ret;
	ret = pthread_create(&tid, NULL, thread_msg_receiver, NULL);
	if( 0 != ret)
	{
		perror("Create thread failed");
		return ret;
	}

	// recv eap pkt which comes from cisco server
	recv_eap_pkt(sock, &sa_ll, &eth_header);

	pthread_join(tid, NULL);

	close(sock);

	return 0;

}



/* *************************************** 
*  recv msg from local host
*  use the msg to control dial routine
* ****************************************/
void *thread_msg_receiver(void *args)
{
	int listenfd, nrecv;
	uint8_t *recv_buf;

	struct sockaddr_in servaddr;
	struct sockaddr_in clntaddr;
	struct ctrl_msg *pmsg;
	socklen_t addrlen = sizeof(clntaddr);


	recv_buf = malloc(ETH_DATA_LEN);
	if( recv_buf == NULL)
	{
		printf("Malloc for the recv_buf failed, in thread_msg_receiver function\n");
		exit(-1);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(LISTEN_PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	listenfd = socket(AF_INET, SOCK_DGRAM, 0);
	if( -1 == listenfd)
	{
		perror("Create listen socket failed");
		exit(-1);
	}

	if( 0 != bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)))
	{
		perror("Bind listenfd failed");
		exit(-1);
	}
	

	while(1)
	{
		memset(recv_buf, 0, ETH_DATA_LEN);
		nrecv = recvfrom(listenfd, recv_buf, ETH_DATA_LEN, 0,
				(struct sockaddr*) &clntaddr, &addrlen);
		if( -1 == nrecv && errno == EINTR)
			continue;
		if( ((struct ctrl_msg *) recv_buf)->msg_magic == MAGIC)
		{
			pmsg = (struct ctrl_msg *) recv_buf;
		       	if( 0 == strncmp(pmsg->msg, "off", strlen(pmsg->msg) ) )
		       	{
			       printf("Logoff!\n");
			       logoff();
			       status = OFFLINE;
		       }
		       if(0 == strncmp(pmsg->msg, "on", strlen(pmsg->msg) ))
		       {
			       printf("Logon!\n");
			       logon();
		       }
		       if(0 == strncmp(pmsg->msg, "over", strlen(pmsg->msg) ))
		       {
			      printf("Exiting!\n");
			      if( status == ONLINE )
			      	      logoff();
			      exit(0);
		       }
		}
	}
}

/* ************************************************************************ 
	  get the user information from the file
	  itface_name which will be used in crt_sock()
* ************************************************************************/
void get_from_file(char *filename, char *uid, char * pswd, char * itface_name)
{
	
	FILE *fp;
	static char temp[32]  = {0};

	fp = fopen(filename, "r");
	if( NULL == fp)
	{
		printf("Please check the %s does exist!\n", filename);
		exit(-1);
	}


	fgets(uid, 31, fp);

	// diminsh the '\n' in user_id buffer
	char *puser ;
	puser = uid;
	while(*puser != '\n' && *puser != '\0')
		puser++;
	*puser = '\0';

	fgets(temp, 31, fp);

	// diminsh the '\n' in temp buffer
	puser = temp;
	while(*puser != '\n' && *puser != '\0')
		puser++;
	*puser = '\0';

	enc_pass(temp, pswd);

	fgets(itface_name, 31, fp);
	
	fclose(fp);

}



void sig_action(int signo)
{
	if( SIGINT == signo)
	{
		logoff();
		printf("Logging off, please waitting 5sec\n");
		sleep(5);
		exit(0);
	}
}
