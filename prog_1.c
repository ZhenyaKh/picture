#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/time.h>
#include<unistd.h>
#include<string.h>
#define TRUE 1
#define BUFFER 50

int main()
{
	int shift_lever = 61;
	int shift_lamp = 69;
	int i;
	int lever;
	int lamp;
	char lever_name[BUFFER];
	char lamp_name[BUFFER];
	char symb = 0;
	int number;
	char number_in_char[3];

	while(TRUE)
	{
		for(i = 0; i < 8; i++)
		{
			strcpy(lever_name,"/sys/class/gpio/gpio");
			number = shift_lever + i;	
			snprintf(number_in_char, sizeof(number_in_char), "%d", number);
			strcat(lever_name, number_in_char);
			strcat(lever_name, "/value");
			printf("Lever name = %s\n", lever_name);

			strcpy(lamp_name,"/sys/class/gpio/gpio");
			number = shift_lamp + i;
			snprintf(number_in_char, sizeof(number_in_char), "%d", number);
			strcat(lamp_name, number_in_char);
			strcat(lamp_name, "/value");
			printf("Lamp name = %s\n", lamp_name);

			lever = open(lever_name, O_RDONLY);
       			lamp = open(lamp_name, O_WRONLY);		
       			if(-1 == lamp || -1 == lever)
			{
            			printf("File opening fail\n");
        			return 1;
       			}

			lseek(lever, 0, SEEK_SET);
	      		read(lever, &symb, 1);
 			//printf("Lever value = %c\n\n", number, symb);

			lseek(lamp, 0, SEEK_SET);
			write(lamp, &symb, 1);

			close(lever);
			close(lamp);
		}
			
		sleep(2);
		printf("\n\n");
	}
	
	return 0;
}
