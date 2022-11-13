#include "../util/utils.c"

void print_last(int fd, int *arr){
	if(-1 == lseek(fd, arr[1]-arr[0], SEEK_SET)){
		fprintf(stderr, "error while using lseek");
		exit(1);
	}

    int chunks = arr[0]/4;
    int last_chunk = arr[0]%4;
	char *buff=calloc(4, sizeof(char));

    for(int i = 0 ; i<chunks;i++){
        read_write(fd, buff, 4);
    }
        read_write(fd, buff, last_chunk);
	
	
}
int *lines_backwards(int fd, int line_num){
	int ix = 0;
	char *buff = calloc(1, sizeof(char));
	int *offsets = (int*)calloc(2,sizeof(int)); // first index is used to know when we have encountered the line we need
												//second index is for the size of the file in bytes;
	int cnt=0;
    int cursor = 0;
    offsets[0]=0;
	if(-1 == lseek(fd, -1, SEEK_END)){
		fprintf(stderr, "error while using lseek");
		exit(1);

	}

	while(read(fd,buff,1)==1 && cursor>=0){
		ix++;
		//printf("[%s]\n", buff);
		if(buff[0] == '\n' ){
			cnt++;
			if(line_num==cnt-1){
				offsets[0] = ix;
				
			}
		}
        cursor = lseek(fd, -2, SEEK_CUR);
		
	}
    if(cnt<line_num){
        offsets[0]=ix;
    }
	offsets[1] = ix;
	free(buff);
	return offsets;

}
int main(int argc, char* argv[]){
	int fd = open(argv[1], O_RDONLY);
    if(-1==fd){
		printf("error while trying to open %s\n", argv[1]);
		exit(1);
	}
	int *offsets;

	int n =-1;
	for(int i = 0; i<argc;i++){
		if(string_eq(argv[i], "-n")){
        	n = atoi(argv[i+1]);
			break;
    	}
	}
	if(n < 0){
		n = 10;
	}
	offsets = lines_backwards(fd, n);

	print_last(fd, offsets);
    close(fd);
}