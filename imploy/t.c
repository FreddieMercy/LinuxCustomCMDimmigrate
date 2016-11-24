#define codeLength 100

#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int readByLine(int fd, char *buff, int count)
{
	//make sure that the file had been opened and have fd with you
	//"count" indicates the number of bytes that buff can take. Don't get the number wrong otherwise sure it will fuck up

	int byteRead = 0;
	int byte = 0;
	char tmp[1];
	int num = count;

	if(num <= 0)
	{
		return byteRead;
	}

	byte = read(fd, tmp, 1);

	if(byte<=0)
	{
		if(byte<0)
		{
			printf("reading error!!\n");
		}

		return byteRead;
	}

	byteRead += byte;
	num--;
	
	while(tmp[0] != '\n')
	{
		buff[byteRead - 1] = tmp[0];

		if(num <= 0)
		{
			return byteRead;
		}

		byte = read(fd, tmp, 1);

		if(byte<0)
		{
			printf("reading error!!\n");
			return byteRead;
		}

		byteRead += byte;
		num--;

		//printf("%c\n", tmp[0]);
	}

	buff[byteRead - 1] = tmp[0];
	buff[byteRead] = '\0';

	return byteRead;
}


int main(int argc, char* argv[])
{
	int fd;
	int byteRead=0;
	int iscode = 1;
	int found = 0;
	char code[codeLength] = "#@#^NdWsFred123456789abcdefg";
	char buf[100];
	char *s;
	int end = 0;
	int counter;
	char cmd[100];
	int i = 0;
	int j = 0;
	int z = 0;
	char *cp = "cp /usr/bin/";
	char *ending = " cmd";
	char *result;
	int writer;
	
	for (i=0; i<argc; i++){
	    printf("argv[%d]=%s\n", i, argv[i]);
	  }

	if(argc > 1)
	{
		printf("parsing %s...\n", argv[1]);
		
		fd = open(argv[1], O_RDONLY);
		writer = open("cmd/list.txt", O_WRONLY);
		
		lseek(fd, SEEK_SET, 0);

	    if(fd < 0)
	    {
	    	printf("cannot open %s!\n", argv[1]);
	        return 1;
	    }

	    byteRead = readByLine(fd, &buf, 100);

	    do
	    {
	    	if(byteRead > 0)
	    	{
	    		for(i = 0; i < strlen(code); i++)
				{
					
					if(code[i] != buf[i])
					{
						iscode = 0;
						break;
					}
					
					//printf("%c", buf[i]);
					//printf("%d", i);
				}
				//printf("\n");

				if(iscode != 0)
				{
					printf("\n\nfound the following: \n");
					found = 1;
				}
				
				if(found != 0)
				{
					//do the shell

					end = 0;
					counter = 0;
					j = 0;
					s = &buf;

					while(buf[counter] != '\n')
					{

						if(buf[counter]!='=')
						{
							counter++;
						}
						else
						{
							counter++;

							while(isspace(buf[counter]))
							{
								counter++;
							}

							if(buf[counter] == '\'')
							{
								//skip '
								counter++;

								while(isspace(buf[counter]))
								{
									counter++;
								}

								//skip .

								counter++;

								while(isspace(buf[counter]))
								{
									counter++;
								}

								while(buf[counter]!='\'')
								{
									cmd[j] = buf[counter];
									counter++;
									j++;
								}

								cmd[j] = '\0';

								result = malloc(strlen(cp)+strlen(cmd)+strlen(ending)+1);//+1 for the zero-terminator
							    //in real code you would check for errors in malloc here
							    strcpy(result, cp);
							    strcat(result, cmd);
							    strcat(result, ending);

								system(result);

								if(writer < 0)
								{
									printf("!!! cannot open the file to WRITE !!!\n");
								}

								printf("%s", s);

								z = write(writer, s, strlen(s));

								if(z < 0)
								{
									printf("### error writing: %s", s);
								}

								if(z == 0)
								{
									printf("### zero byte written: %s", s);
								}

							}

							break;
						}
					}

		    		//reset
		    		buf[0]='\0';
		    		
			    }

			    iscode = 1;

			    //printf("%c\n", buf[0]);
			}

		    byteRead = readByLine(fd, buf, 100);

		}while(byteRead > 0);

	    close(fd);
	    close(writer);
	}
	else
	{
		printf("No enought arguments. (usage: './a.out file1')\n");
		return 0;
	}

	return 0;
}
