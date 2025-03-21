#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/fcntl.h>
#include<stdlib.h>
#include<sys/wait.h>

void pram_check(char *sfile,int argc,int pronum)
{
	if(access(sfile,F_OK) != 0)
	{
		printf("源文件不存在\n");
		return;
	}
	if(pronum <= 3||pronum >=80)
	{
		printf("进程数量不合理\n");
		return;
	}
	if(argc < 3)
	{
		printf("参数数量少于3\n");
		return;
	}
}

int block_cur(char *sfile,int pronum)
{
	int fd = open(sfile,O_RDONLY);
	int size = lseek(fd,0,SEEK_END);
	int block_cur;
	if((size%pronum) == 0)
	{
		block_cur = size % pronum;
	}else
	{
		block_cur = size % pronum + 1;
	}
	return block_cur;
}

void process_create(char *sfile,char *dfile,int blocksize,int pronum)
{
	pid_t pid;
	int i = 0;
	for(i;i<pronum;i++)
	{
		pid = fork();
		if(pid == 0)
		{
			break;
		}
	}
	if(pid == 0)
	{
		printf("child process %d\n",getpid());
		execl("/home/colin/20240520/process/copy.c","./copy",sfile,dfile,i*blocksize,blocksize,NULL);
		printf("child %d excel success\n",i);
		exit(i);
	}else if(pid > 0)
	{
		printf("parent process %d\n",getpid());
	}
	else{
		perror("for fork call error\n");
		exit(0);
    }

}

void waiting(void)
{
	pid_t zpid;
	while((zpid = wait(NULL)) != -1)
	{
		if(zpid > 0)
		{
			printf("parent wait success. zpid %d\n",zpid);
		}else
		{
			printf("parent wait failed\n");
		}
	}
}

int main(int argc, char* argv[])
{
	int pronum;
	if(argv[3] == 0)
	{
		pronum = 3;
	}else
	{
		pronum = atoi(argv[3]);
	}
	pram_check(argv[1],argc,atoi(argv[3]));
	int blocksize = block_cur(argv[1],atoi(argv[3]));
	process_create(argv[1],argv[2],blocksize,atoi(argv[3]));
	waiting();
	return 0;
}
