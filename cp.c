#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc,char* argv[])
{
	// 检查参数是否正确
	if(3 != argc)
	{
		printf("User：cp src dest\n");
		return 0;
	}

	// 打开源文件
	int src_fd = open(argv[1],O_RDONLY);
	if(0 > src_fd)
	{
		perror("open");
		return -1;
	}

	// 检查目标文件是否存在
	int dest_fd = open(argv[2],O_WRONLY|O_CREAT|O_EXCL,0644);
	if(0 > dest_fd)
	{
		printf("目标文件已经存在，是否覆盖Y/N?");
		char cmd = getchar();
		if('y' == cmd || 'Y' == cmd)
		{
			dest_fd = open(argv[2],O_WRONLY|O_TRUNC);
			if(0 > dest_fd)
			{
				perror("open");
				return -1;
			}
		}
		else
		{
			return 0;
		}
	}
	
	int buf[1024] = {} , ret = 0;
	while(ret = read(src_fd,buf,sizeof(buf)))
	{
		write(dest_fd,buf,ret);
	}

	close(src_fd);
	close(dest_fd);
}
