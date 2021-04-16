#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <time.h>

int main(){
	uint32_t rip = 0;
	uint32_t lip = 0;
	uint16_t rprt = 0;
	uint16_t lprt = 0;
	char* user[80];
	char* command[200];
	char q = 10;
	uint8_t *p;
	p = (uint8_t*) &rip;

	printf("SSH REVERSE TUNNEL CREATOR\n\n");

	printf("Remote IP: ");
	scanf("%" SCNu8 ".%" SCNu8 ".%" SCNu8 ".%" SCNu8,p,(p+1),(p+2),(p+3));
	//SCNu8 -> for input of 8bit unsigned integers
	//SCNd8 -> for input of 8bit signed integers

	printf("Remote Port: ");
	scanf("%" SCNu16,&rprt);
	//SCNu16 -> for input of 16bit unsigned integers
	//SCNd16 -> for input of 16bit signed integers

	printf("Local Port: ");
	scanf("%" SCNu16,&lprt);

	printf("Remote User: ");
	scanf("%s",&user);

	printf("RIP: %d.%d.%d.%d RPRT: %d\n", *p,*(p+1),*(p+2),*(p+3),rprt);
	printf("USER: %s LPRT: %d\n", user ,lprt);

	sprintf(command,"ssh -N -R %d.%d.%d.%d:%d:localhost:%d %s@%d.%d.%d.%d",
			*p,*(p+1),*(p+2),*(p+3),rprt,lprt,user,*p,*(p+1),*(p+2),*(p+3));
	printf("SSH Command: '%s'\n", command);

	printf("Execute command now? (y/n)\n");
	while(q == 10){
		q = getchar();
	}

	printf("======= SSH SESSION STARTED ======\n\n",q,q);
	if(q == 'y'){
		system(command);
		printf("SSH Session terminated!\n");
	}

	return 0;
}
