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
void print_last(int fd, int *arr){
	lseek(fd, arr[1]-arr[0], SEEK_SET);

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
	int *line_arr = (int*)calloc(2,sizeof(int));
	int cnt=0;
    int cursor = 0;
    line_arr[0]=0;
	lseek(fd, -1, SEEK_END);
	while(read(fd,buff,1)==1 && cursor>=0){
		ix++;
		//printf("[%s]\n", buff);
		if(buff[0] == '\n' ){
			cnt++;
			if(line_num==cnt-1){
				line_arr[0] = ix;
				
			}
		}
        cursor = lseek(fd, -2, SEEK_CUR);
		
	}
    if(cnt<line_num){
        line_arr[0]=ix;
    }
	line_arr[1] = ix;
	free(buff);
	return line_arr;

}
int main(int argc, char* argv[]){
	int fd = open(argv[1], O_RDONLY);
    if(-1==fd){
		printf("error while trying to open %s\n", argv[1]);
		exit(1);
	}
	int *arr;

	int flag_n =-1;
	for(int i = 0; i<argc;i++){
		if(string_eq(argv[i], "-n")){
        	flag_n = atoi(argv[i+1]);
			break;
    	}
	}
	if(flag_n < 0){
		flag_n = 10;
	}
	arr = lines_backwards(fd, flag_n);
	for(int i = 0 ; i<2;i++){
		printf("%d ", arr[i]);
	}
		printf("\n");
	print_last(fd, arr);
    close(fd);
}