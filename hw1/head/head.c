#include "../util/utils.c"
int *lines(int fd, int lines_num){
	int ix = 0;
	char *buff = calloc(1, sizeof(char));
	int offsets[2];// first index is used to know when we have encountered the line we need
												//second index is for the size of the file in bytes;
	int all_lines=0;
	while(read(fd,buff,1)==1){
		ix++;
		
		if(buff[0] == '\n' ){
			all_lines++;

			if(lines_num==all_lines ){
				offsets[0] = ix;
				break;
			}
		}
	}
	if(all_lines<lines_num){

		offsets[0] = ix;
	}
	offsets[1] = ix;
	free(buff);
	return offsets;
}

void print_first(int fd, int *arr){
	if(-1 == lseek(fd, 0, SEEK_SET)){
		fprintf(stderr,"error while using lseek");
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
int main(int argc, char* argv[]){
	if(argc<2){
		fprintf(stderr,"not enough arguments");
		exit(1);
	}
	int fd = open(argv[1], O_RDONLY);
	if(-1==fd){
		fprintf(stderr,"error while trying to open %s\n", argv[1]);
		exit(1);

	}
	int n =-1;
	for(int i = 0; i<argc;i++){
		if(string_eq(argv[i], "-n")){
        	n = atoi(argv[i+1]);
			break;
    	}
	}
	if(n <0){
		n = 10;
	}
	int *offsets;
	offsets = lines(fd,n);
	print_first(fd, offsets);

}
