#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

void *connection_handler(void *sock)
{

	int conn = *(int*)sock;
	int recv_len = 0;
	char send_buf[1024]="\0";
	char recv_buf[1024]="\0";

	fprintf(stderr, "%s:%d conn=%d\n", __FILE__, __LINE__, conn);

	while( (recv_len = recv(conn, recv_buf, 1024, 0)) >0 )
	{
	fprintf(stderr, "%s:%d received %d words\n", __FILE__, __LINE__, recv_len);
		send(conn, recv_buf, strlen(recv_buf), 0 );
		memset(recv_buf,0,strlen(recv_buf));
	}

	fprintf(stderr, "%s:%d recv_len=%d\n", __FILE__, __LINE__, recv_len);

	if(recv_len==0)
	{
		fprintf(stderr, "client disconnected\n");
		fflush(stdout);
	fprintf(stderr, "%s:%d\n", __FILE__, __LINE__);
	}
	else if(recv_len==-1)
	{
		perror("recv");
		exit(-1);
	}

	fprintf(stderr, "%s:%d\n", __FILE__, __LINE__);


	close(sock);
	free(sock);
	return 0;
}

int main(int argc, char* argv[])
{
	int socket_fd=0, client_fd=0;
	int* new_sock=NULL;
	int recv_len=0;
	char recv_buf[1024] = {0};
	char client_name[128]={0};
	struct sockaddr_in sa_svr, sa_clt; 
	pthread_t thread_id;

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_fd == -1)
	{
		perror("socket");
		exit(-1);
	}

	fprintf(stderr, "%s:%d\n", __FILE__, __LINE__);

	sa_svr.sin_family = AF_INET;
	sa_svr.sin_addr.s_addr = htonl(INADDR_ANY);
	sa_svr.sin_port = htons(5000);

	if(bind(socket_fd, (struct  sockaddr*)&sa_svr, sizeof(sa_svr))  <0)
	{
		perror("bind");
		exit(-1);
	}

	fprintf(stderr, "%s:%d\n", __FILE__, __LINE__);

	listen(socket_fd, 10);
	int c = sizeof(struct sockaddr_in);


	while(1)
	{
		client_fd = accept(socket_fd, (struct sockaddr*)&sa_clt, (socklen_t*)&c);
		if(client_fd<0)
		{
			perror("accept");
			continue;
		}
		inet_ntop(AF_INET, &sa_clt.sin_addr, client_name, sizeof(client_name));
		fprintf(stderr, "%s:%d client from %s \n", __FILE__, __LINE__, client_name);

		new_sock = malloc(sizeof(int));
		*new_sock = client_fd;

		if(pthread_create(&thread_id, NULL, connection_handler, (void*)new_sock)<0)
		{
			perror("pthread_create");
			exit(-1);
		}


	}




	close(socket_fd);
	close(client_fd);
	return 0;
}


