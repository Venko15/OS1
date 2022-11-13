#include "../header.h"
#include "../util/utils.c"

int lines(int fd){
	char *buff=calloc(1, sizeof(char));
	int lines_num = 1;
	while(read(fd,buff,1)==1){
		if(buff[0] == '\n'){
			lines_num++;
		}
	}
	return lines_num;
}
int bytes(int fd){
	int num_bytes = lseek(fd, 0 , SEEK_END);
	if(-1 == num_bytes){
		fprintf(stderr,"error while using lseek");
		exit(1);
	}
	if(-1 == lseek(fd, 0 ,  SEEK_SET)){
		printf("error while using lseek");
		exit(1);
	}
	return num_bytes;


}
int main(int argc, char *argv[]){
	int fd = open(argv[1], O_RDONLY);
	int flag_l = 0;
	int flag_c = 0;
	if(-1==fd){
		fprintf(stderr,"error while trying to open %s", argv[1]);
		exit(1);

	}
	//printf("%d\n",string_eq(argv[1], argv[2]));
	if(argc == 3){
		if(string_eq(argv[2], "-l")){
			flag_l = 1;			
		}else if(string_eq(argv[2],"-c" )){
			flag_c = 1; 	
		}
	
	}else if(argc>3){	
		for(int i =2; i<argc; i++){
			if(flag_l && flag_c){
			 	break;
			}
			if(string_eq(argv[i], "-l")){
				flag_l = 1;
			
			}else if(string_eq(argv[i], "-c")){
				flag_c = 1;
			
			}
		}
	}
	if((flag_l == 1 && flag_c == 1) || (flag_l == 0 && flag_c == 0 )){
		printf("%d  %d\n",bytes(fd), lines(fd) );
	}else if(flag_l == 1){
		printf("%d \n", lines(fd));
	}else if(flag_c == 1 ){
		printf("%d \n", bytes(fd));
	}
	close(fd);
return 0;

}
