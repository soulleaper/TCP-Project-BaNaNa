#include "inet.h"
#define BUFSIZE 1024

main(int argc, char *argv[]){
int sockfd;
char buffer[BUFSIZE+1];
int bytereceive = 0;
struct sockaddr_in serv_addr;
char createname[20];
char deletename[20];
static struct sigaction act;

void catchin(int);

act.sa_handler = catchin;
sigfillset(&(act.sa_mask));

sigaction(SIGINT, &act, (void *) 0);


if(argc <= 1){
printf("How to use : %s remoteIPaddress [example: ./client 127.0.0.1]\n", argv[0]); exit(1); }

bzero( (char*) &serv_addr, sizeof(serv_addr) );
serv_addr.sin_family = AF_INET ;
serv_addr.sin_port = htons (SERV_TCP_PORT);
inet_pton (AF_INET, argv[1], &serv_addr.sin_addr);

if( (sockfd = socket(AF_INET, SOCK_STREAM, 0) ) < 0) {
perror("Client: socket() error \n");
exit(1); }

if(connect (sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) <0 ) {
perror("Client: connect() error\n");
exit(1);}

/* Get the user name */
	char *buf;
	buf=(char *)malloc(10*sizeof(char));
	buf=getlogin();

	/* set the 'client_file' path */
	char str[30];
	strcpy(str, "/home/");
	strcat(str, buf);
	strcat(str, "/client_file/");

	/* Check the path exist or not, if not, create one */
	struct stat s;
	if(stat(str, &s) == -1){
	mkdir(str, 0700); }

do{
bzero( buffer, sizeof(buffer));
recv(sockfd, buffer, BUFSIZE, 0);
printf("\n%s\n", buffer);
gets(buffer);
send(sockfd,buffer, BUFSIZE, 0);


if(!strcmp(buffer, "1"))
{
	bzero( buffer, sizeof(buffer));
	recv(sockfd, buffer, BUFSIZE, 0);
	printf("\n%s\n", buffer);
	gets(buffer);
	send(sockfd,buffer, BUFSIZE, 0);

   	char filename[30];
    	strcpy(filename, "/home/");
    	strcat(filename, buf);
    	strcat(filename, "/client_file/");
    	strcat(filename, buffer);

    	FILE *fp;
    	fp = fopen(filename, "ab");

		if(NULL == fp)
    	{
        	printf("Error opening file");

    	}

    	bzero( buffer, sizeof(buffer));

    	bytereceive = recv(sockfd, buffer, BUFSIZE, 0);
    	fwrite(buffer,1,bytereceive,fp);

}


else if(!strcmp(buffer, "2"))
{


	DIR *dir;
	struct dirent *ent;

	char directoryName[30];
   	strcpy(directoryName, "/home/");
    	strcat(directoryName, buf);
    	strcat(directoryName, "/client_file/");

	if ((dir = opendir (directoryName)) != NULL) {

		printf("\n[List of files in Client Directory]\n");
  		// print all the files and directories within directory
  		while ((ent = readdir (dir)) != NULL) {

		printf("%s\n", ent->d_name);    }

 		closedir (dir);
	}

	printf("\nPlease enter one of the filename from above including extension\n");

	bzero( buffer, sizeof(buffer));
	gets(buffer);
	send(sockfd,buffer, BUFSIZE, 0);

	char filename[30];
	strcpy(filename, "/home/");
	strcat(filename, buf);
	strcat(filename, "/client_file/");

	strcat(filename, buffer);

	FILE *fp;
    	fp = fopen(filename, "r");

	bzero( buffer, sizeof(buffer));
	int nread = fread(buffer,1,256,fp);
	send(sockfd, buffer, nread, 0);
}


else if(!strcmp(buffer, "3"))
{
	printf("Enter directory name that you want to create: ");
	scanf("%s", createname);

	/* set the path/name of the directory that want to create */
	char createDirectory[30];
	strcpy(createDirectory, "/home/");
	strcat(createDirectory, buf);
	strcat(createDirectory, "/");
	strcat(createDirectory, createname);

	/* Check the path exist or not, if not, create one */
	struct stat s;
	if(stat(createDirectory, &s) == -1){
	mkdir(createDirectory, 0700); }
}


else if(!strcmp(buffer, "4"))
{
	printf("Enter directory name that you want to delete: ");
	scanf("%s", deletename);

	/* set the path of the directory that want to delete */
	char deleteDirectory[30];
	strcpy(deleteDirectory, "/home/");
	strcat(deleteDirectory, buf);
	strcat(deleteDirectory, "/");
	strcat(deleteDirectory, deletename);

	/* select all the files inside the directory that want to delete */
	char selectSubDirectory[50];
	strcpy(selectSubDirectory, "exec rm -r ");
	strcat(selectSubDirectory, "/home/");
	strcat(selectSubDirectory, buf);
	strcat(selectSubDirectory, "/");
	strcat(selectSubDirectory, deletename);
	strcat(selectSubDirectory, "/*");

	/* Check the path exist or not, if exist, delete it */
	struct stat s;
	if(stat(deleteDirectory, &s) != -1){
	system(selectSubDirectory);
	rmdir(deleteDirectory); }
}

}while (strcmp(buffer, "/q"));
close(sockfd);
}

void catchin(int signo){
	printf("\n[ Interrupt signal has been ignored.]\n");
}
