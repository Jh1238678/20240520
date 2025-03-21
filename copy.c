#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/fcntl.h>
#include<sys/stat.h>
#include<stdlib.h>
int main(int argc,char *argv[])
{
	int fds = open(argv[1],O_RDONLY);
	int fdd = open(argv[2],O_WRONLY);
	char buffer[atoi(argv[4])];
	lseek(fds,atoi(argv[3]),SEEK_SET);
	read(fds,buffer,sizeof(buffer));
	lseek(fdd,atoi(argv[3]),SEEK_SET);
	write(fdd,buffer,sizeof(buffer));
	close(fds);
	close(fdd);
	return 0;
}

