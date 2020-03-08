#include <sys/wait.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>




int main()
{

	int pfd1[2];
	pid_t cpid1; pid_t cpid2; 
	char buffer[100];

	//get the message
	printf("Enter a string: ");
	fgets(buffer,100,stdin);
	printf("You entered: %s",buffer);



	if(pipe(pfd1)==-1)
	{
		perror("pipe 1 failed");
		exit(EXIT_FAILURE);

	}


	cpid1= fork();
//CHILD 1
	if(cpid1==-1)
	{
		perror("fork failure for CHILD 1");
		exit(EXIT_FAILURE);


	}

	if(cpid1==0)
	{
	//sleep(2);
		int k=0;
		close(pfd1[1]); //write end close
		char temp[100];
		while(read(pfd1[0],&buffer,1)>0) //till message gets complete
		{
			temp[k]=buffer[k];
			k++;
		}

		temp[k]='\0';


		//strcpy(buffer,temp);

		if(strlen(temp)>0)
		{
			printf("%s","\nCHILD 1 HAS GOTTEN THE MESSAGE!");
			printf("%s",temp);

			close(pfd1[0]);
			exit(EXIT_SUCCESS);
			wait(NULL);
		}

		printf("%s","\nCHILD 1 HAS not GOTTEN THE MESSAGE!");
		printf("%s",temp);

		close(pfd1[0]);
		exit(EXIT_SUCCESS);

		wait(NULL);


	}

	if(cpid1>0)
	{
		//wait(NULL);
		printf("%s","\nParent is writing message");
		close(pfd1[0]);
		write(pfd1[1],buffer,strlen(buffer));

		//CHILD 2
		cpid2=fork();

		if(cpid2==-1)
		{
			perror("fork failure for CHILD 2");
			exit(EXIT_FAILURE);


		}
		if(cpid2==0)
		{
		//sleep(2);
			int k=0;
			close(pfd1[1]); //write end close
			char temp[100];
			while(read(pfd1[0],&buffer,1)>0) //till message gets complete
			{

				temp[k]=buffer[k];
				k++;


			}
			temp[k]='\0';


			if(strlen(temp)>0)
			{
				printf("\nCHILD 2 HAS GOTTEN THE MESSAGE!");
				printf("%s",temp);

				close(pfd1[0]);
				exit(EXIT_SUCCESS);
			}
			//strcpy(buffer,temp);
			printf("\nCHILD 2 HASnot GOTTEN THE MESSAGE!");
			printf("%s",temp);

			close(pfd1[0]);
			exit(EXIT_SUCCESS);

		}

				//wait(NULL);

				//sleep(2);




	}
	wait(NULL);
//printf("%s","\nEND of Parent2");

return 0;
}