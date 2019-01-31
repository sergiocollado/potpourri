#include<stdio.h>
#include<unistd.h>

int main(int argc, char ** argv)
{
	char pwd[512];

	if(getwd(pwd) != 0)
	{
		printf("current directory is: %s\n", pwd);
		return (0);
	}
	else
	{
		printf("Error in finding the current directory\n");
		return (1);
	}
}
