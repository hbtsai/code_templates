#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
	int sock=0;
	char send_buf[1024]={0};
	char recv_buf[1024]={0};
	struct sockaddr_in sa_svr;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock==-1)
	{
		perror("socket");
		exit(-1);
	}

	sa_svr.sin_family = AF_INET;
	sa_svr.sin_addr.s_addr = inet_addr("127.0.0.1");
	sa_svr.sin_port = htons(5000);
	
	if(connect(sock, (struct sockaddr*)&sa_svr, sizeof(sa_svr))<0)
	{
		perror("connect");
		exit(-1);
	}

	while(1)
	{
		fprintf(stderr, "please enter messge: ");
		scanf("%s", send_buf);

		if(send(sock, send_buf, strlen(send_buf),0)<0)
		{
			perror("send");
			exit(-1);
		}
		
		if(recv(sock, recv_buf, 1024, 0)<0)
		{
			perror("recv");
			exit(-1);
		}

		fprintf(stderr, "server reply: %s\n", recv_buf);
		memset(recv_buf,0, strlen(recv_buf));
	}

	close(sock);

	return 0;
}
