#include "../header.h"
#include "../util/utils.c"
void read_write(int fd, char *buff, size_t sz){
        if(-1 == read(fd, buff,sz)){
            fprintf(stderr,"error while trying to read from file");
            exit(1);

        }
        if(-1 == write(1, buff,sz)){
            fprintf(stderr,"error while tring to write to stdout");
            exit(1);
        }
}
int *lines(int fd, int lines_num){
	int ix = 0;
	char *buff = calloc(1, sizeof(char));
	int *line_arr = (int*)calloc(2,sizeof(int));
	int cnt=0;
	line_arr[0]=71;
	while(read(fd,buff,1)==1){
		ix++;
		
		if(buff[0] == '\n' ){
			cnt++;

			if(lines_num==cnt ){
				line_arr[0] = ix;
				break;
			}
		}
	}
	if(cnt<lines_num){

		line_arr[0] = ix;
	}
	line_arr[1] = ix;
	free(buff);
	return line_arr;
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
	int flag_n =-1;
	for(int i = 0; i<argc;i++){
		if(string_eq(argv[i], "-n")){
        	flag_n = atoi(argv[i+1]);
			break;
    	}
	}
	if(flag_n <0){
		flag_n = 10;
	}
	int *arr;
	arr = lines(fd,flag_n);

	for(int i = 0 ; i<2;i++){
		printf("%d ", arr[i]);
	}
		printf("\n");
	print_first(fd, arr);

}