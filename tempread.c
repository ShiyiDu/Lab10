#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void usage();
void tempread(char device[], int verbose);

int main(int argc, char *argv[]) {
	char *device = "28-01131e7c7bfd";
	int verbose = 0;
	/* process the arguments */
	argc--; argv++;
	while(argc > 0) {
		printf("%d %s\n", argc, argv[0]);
		if(!strcmp("-v", argv[0])) {
			verbose = 1;
		} else if(!strcmp("-d", argv[0])) {
			if(argc == 0) usage();
				argc--; argv++;
				device = argv[0];
	 	} else{
			usage();
		}
		argc--; argv++;
	}
	tempread(device, verbose);
	exit(0);
}

void usage(){
	fprintf(stderr, "Command line argument incorrect!\n");
}

void tempread(char device[], int verbose){
	char dir[] = "/sys/bus/w1/devices/00-000000000000/w1_slave";
	int i, n;
	int result;
	char buf[101];
	FILE *fd;
	for(i = 0; i < 15; i++){
		int index = i + 20;
		dir[index] = device[i];
	}  

	if((fd = fopen(dir, "r")) == (FILE *)NULL){
		exit(1);
	}
	
	n = fread(buf, 1, 100, fd);
	buf[n] = '\0';
	
	result = ((buf[n-2] - 48) + (buf[n-3] - 48) * 10 + (buf[n-4] - 48) * 100 + (buf[n-5] - 48) * 1000 + (buf[n-6] - 48) * 10000);
	
	fclose(fd);
	
	if(verbose) fprintf(stdout, "%s", buf);
	
	fprintf(stdout, "%d\n", result);
	exit(0);
}
