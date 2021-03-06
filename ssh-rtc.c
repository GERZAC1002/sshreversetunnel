#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include <time.h>

#define ARG_CHECK(arg,chk) (!strncmp(arg,chk,sizeof(chk)))

int main(int argc,char **argv){
	uint32_t rip = 0;
	//uint32_t lip = 0; //not needed yet
	volatile uint16_t rprt = 0;
	volatile uint16_t lprt = 0;
	char user[80];
	char command[200];
	char q = 10;
	char modified[5] = {0,0,0,0,0}; // [0] lp, [1] rp, [2] rip, [3] user
	uint8_t *p;
	p = (uint8_t*) &rip;
	
	/* defaults */
	sprintf(user, "root");
	rprt = 80;
	lprt = 80;
	rip = 16777343;


	for(volatile int i = 1; i < argc; i++){
		if(ARG_CHECK(argv[i],"--help")){
			printf("SSH revese tunnel help\n");
			printf("usage: -lp <port> -rp <port> -rip <ip address> -u <user>\n");
			printf("-lp\t--local-port\t\tLocal port to forward\n");
			printf("-rp\t--remote-port\t\tRemote port, port to open on the remote host\n");
			printf("-rip\t--remote-ip\t\tIP of the host that is used for forwarding\n");
			printf("-u\t--user\t\t\tUser to connect to on the remote host\n");
			printf("-q\t--quiet\t\t\tDisable output of some messages\n");
			return 0;
		}else if(ARG_CHECK(argv[i],"-lp")){
			lprt = (uint16_t) strtol(argv[++i],0,10);
			modified[0] = 1;
		}else if(ARG_CHECK(argv[i],"-rp")){
			rprt = (uint16_t) strtol(argv[++i],0,10);
			modified[1] = 1;
		}else if(ARG_CHECK(argv[i],"--local-port")){
			lprt = (uint16_t) strtol(argv[++i],0,10);
			modified[0] = 1;
		}else if(ARG_CHECK(argv[i],"--remote-port")){
			rprt = (uint16_t) strtol(argv[++i],0,10);
			modified[1] = 1;
		}else if(ARG_CHECK(argv[i],"-rip")){
			sscanf(argv[++i],"%" SCNu8 ".%" SCNu8 ".%" SCNu8 ".%" SCNu8,p,(p+1),(p+2),(p+3));
			modified[2] = 1;
		}else if(ARG_CHECK(argv[i],"--remote-ip")){
			sscanf(argv[++i],"%" SCNu8 ".%" SCNu8 ".%" SCNu8 ".%" SCNu8,p,(p+1),(p+2),(p+3));
			modified[2] = 1;
		}else if(ARG_CHECK(argv[i],"-u")){
			sprintf(user,"%s",argv[++i]);
			modified[3] = 1;
		}else if(ARG_CHECK(argv[i],"--user")){
			sprintf(user,"%s",argv[++i]);
			modified[3] = 1;
		}else if(ARG_CHECK(argv[i],"-q")){
			modified[4] = 1;
		}else if(ARG_CHECK(argv[i],"--quiet")){
			modified[4] = 1;
		}
	}

	if(argc < 2){
		printf("SSH REVERSE TUNNEL CREATOR\n\n");

		printf("Remote IP(%d.%d.%d.%d): ",*p,*(p+1),*(p+2),*(p+3));
		scanf("%" SCNu8 ".%" SCNu8 ".%" SCNu8 ".%" SCNu8,p,(p+1),(p+2),(p+3));
		//SCNu8 -> for input of 8bit unsigned integers
		//SCNd8 -> for input of 8bit signed integers

		printf("Remote Port(%d): ",rprt);
		scanf("%" SCNu16,&rprt);
		//SCNu16 -> for input of 16bit unsigned integers
		//SCNd16 -> for input of 16bit signed integers

		printf("Local Port(%d): ",lprt);
		scanf("%" SCNu16,&lprt);

		printf("Remote User(%s): ",user);
		scanf("%s",&user);
	} else {
		if(modified[0] == 0){
			printf("[WARNING] using default local port: %d\n", lprt);
		}
		if(modified[1] == 0){
			printf("[WARNING] using default remote port: %d\n", rprt);
		}
		if(modified[2] == 0){
			printf("[WARNING] using default remote ip: %d.%d.%d.%d\n",*p,*(p+1),*(p+2),*(p+3));
		}
		if(modified[3] == 0){
			printf("[WARNING] using default user: %s\n", user);
		}
	}
	sprintf(command,"ssh -N -R %d.%d.%d.%d:%d:localhost:%d %s@%d.%d.%d.%d",
		*p,*(p+1),*(p+2),*(p+3),rprt,lprt,user,*p,*(p+1),*(p+2),*(p+3));
	if(modified[4] == 0){
		printf("RIP: %d.%d.%d.%d RPRT: %d\n", *p,*(p+1),*(p+2),*(p+3),rprt);
		printf("USER: %s LPRT: %d\n", user ,lprt);
		printf("SSH Command: '%s'\n", command);
		printf("Execute command now? (y/n)\n");
		while(q == 10){
			q = getchar();
		}
		if(q == 'y'){
			printf("[STARTED] SSH Session started!\n");
			system(command);
			printf("[STOPPED] SSH Session terminated!\n");
		}
	}else{
		system(command);
	}
	return 0;
}
