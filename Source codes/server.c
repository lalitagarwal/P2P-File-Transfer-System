#include<sys/shm.h>
#include"unp.h"

int *downloadstatus;
int *cnt;

struct client *clients;

//client structure to store the list of files shared by each client.
struct client
{			
                int id;
		int fileno;
		char ipaddress[20];
                char *name;
                char list[1000][30];
};

//Function to send the list of files shared by all the clients connected to the server.
void sendlist(void *fd)
{
	int confd=*(int *)fd;
	int err;
	char filename[30];
	char handshake[15];
	struct client *list;
	list=clients;
	strcpy(handshake,"CNTSTART");
	err=write(confd,(const void *)handshake,15);
	err=write(confd,(const void *)cnt,sizeof(int));
	if(err==-1) printf("Error in sending cnt.\n");
	err=write(confd,(const void *)list,*cnt*sizeof(struct client));
	if(err==-1) printf("error in sending list.\n");
	printf("List sent.\n");
}

//Function to check if any download request sent to any of the clients.
void idcheck(void *kuchbhi)
{
	int id=((int *)kuchbhi)[1];
	int confd=((int *)kuchbhi)[0];
	char request='d';
	while(*downloadstatus!=id);
	*downloadstatus=0;
	printf("Client %d accepted the download request.\n\n",id);
	write(confd,(const void *)&request,sizeof(request));
}

//Function to set the status of client to upload the file.
void download(int id,int did)
{
	
	*downloadstatus=did;
}

//Function to receive the request given by the client and take appropriate action.
int first(void* fd, int id)
{
        int confd=*(int *)fd;
	char *c;
	int ret=0;
	int did;
	int array[2];
	pthread_t tid;
	array[0]=confd;
	array[1]=id;
	pthread_create(&tid,NULL,idcheck,(void *)array);
	while(1)
	{
	c=(char *)malloc(2*sizeof(char));
	do
	{
		ret=read(confd,(void *)c,2);
	}while(ret==-1);
	if(c[0]=='l')
	{
		printf("\nGot List Request from Client %d\n",id);
		sendlist(fd);
	}
	else if(c[0]=='d')
	{
		sleep(1);
		read(confd,(void *)&did,sizeof(int));
		printf("\nGot Download Request from Client %d\n",did);
		write(confd,(void *)clients[did].ipaddress,20*sizeof(char));
		download(id,did);
	}
	else
	{
		printf("\nClient %d is exiting.\n",id);
		clients[id-1].fileno=0;
		pthread_exit();
		exit(0);
	}
	free(c);
	}
}

int main(void)
{
        int sockfd,j;
	int cntaddress,listaddress,daddress;
	socklen_t len;
	pid_t pid[1000];
        struct sockaddr_in servaddr,cliaddr;
	//Using Shared Memory. 
	cntaddress=shmget(800,sizeof(int),IPC_CREAT | 0755);
	listaddress=shmget(900,15*sizeof(struct client),IPC_CREAT | 0755);
	daddress=shmget(1000,sizeof(int),IPC_CREAT | 0755);
	//cnt variable stores the number of clients connected to the server.
	cnt=(int *)shmat(cntaddress,NULL,0);
        clients=(struct client *)shmat(listaddress,NULL,0);
	downloadstatus=(int *)shmat(daddress,NULL,0);	
	*downloadstatus=0;
	sockfd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP); 
        bzero(&servaddr,sizeof(servaddr));
        servaddr.sin_family=AF_INET;
        servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
        servaddr.sin_port=htons(13000);
        bind(sockfd,(SA *) &servaddr,sizeof(servaddr));
	*cnt=0;
        listen(sockfd,LISTENQ);
                len=sizeof(cliaddr);
                printf("\nServer Ready\n");
                while(1)
                {
			int confd,i;
			int ret=0;
			char ip[17];
			char filename[30];
			printf("Waiting for clients ..\n\n");
	                confd=accept(sockfd,(SA *) &cliaddr,&len);
			printf("Connection Established.\n");
			ret=read(confd,(void *)ip,17);
			if(ret==-1) 
				printf("read error.\n");
			strncpy(clients[*cnt].ipaddress,ip,17);
			printf("IP Address of Client %d connected is %s\n",(*cnt+1),clients[*cnt].ipaddress);
			strcpy(filename,"");
			clients[*cnt].id=*cnt+1;
			clients[*cnt].fileno=0;
			do
			{			
				do
				{	ret=read(confd,(void *)filename,30);
				}while(ret==-1);
				printf("Listing the files of Client %d.\n",(*cnt+1));
			}while(strcmp(filename,"STARTOFFILE")!=0);
			do
			{
				clients[*cnt].fileno++;
				do				
				{	ret=read(confd,(void *)filename,30);
				}while(ret==-1);
				if(strcmp(filename,"ENDOFFILE")==0) break;
				strcpy(clients[*cnt].list[clients[*cnt].fileno],filename);
			}while(1);
			//Creating child server by using fork() command to handle the client connected.
			pid[*cnt]=fork();
			if(pid[*cnt]==0)
			{
				close(sockfd);
				first((void *)&confd, *cnt);
			}
			close(confd);
			(*cnt)++;
			printf("No. of Clients Connected: %d\n\n",*cnt);
                }
        return 0;
}
