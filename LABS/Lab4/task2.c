//Program: task2.c
//Author: Mitchell Krystofiak
//Description: Read in file and find the discovered digit characters.
//Date: March 10, 2021

#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int int_to_str(char * str, int x)
{
	sprintf(str, "%d", x);
	return(strlen(str));
}

int convertStrToInt(char *str, int count)
{
        int temp = 10;
        int num = 0;
        for (int i = count-1; i >= 0; i--)//converts string to int
        {
                str[i] = str[i] - 48;
                if (i == count-1) //ones digit
                        num = str[i];
                else
                {
                        num = num + temp * str[i];
                        temp = temp*10;
                }
        }
        return num;
}

int is_digit(int c)
{
	if (c >= 48 && c <= 57)
		return 1;
	else 
		return 0;
}

int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		printf("Argument error! Expecting 1 argument!\n");
		exit(1);
	}
	
	int inFile;
	char buffer[80];
	char buf;
	int count = 0;
	int temp;

	if ((inFile = open(argv[1], O_RDONLY)) == -1)
	{
		printf("Error opening input file!\n");
		exit(1);
	}
	
	while(read(inFile, &buf, 1) > 0)
		if (is_digit(buf))
		{
			buffer[count] = buf;
			count++;
		}
	if (count == 0)
	{
		printf("File contains no digits!\n");
                return 1;	
	}	
	temp = convertStrToInt(buffer, count);
	temp = temp + 10;
	
	printf("%d", temp);
	printf("\n");
	return 0;
	
}
