#include "../header.h"

int string_eq(char *arg, char *check){
	int min_sz=0;
	if(!arg || !check){
		return 0;
	}
	for(int i = 0; arg[i] != '\0' || check[i] != '\0';i++){
		if(arg[i] != check[i]){
			return 0;
		}
		min_sz = i;
	}
	if((arg[min_sz]=='\0' && check[min_sz] != '\0') || (arg[min_sz] != '\0' && check[min_sz] == '\0')){
	//	printf("arg = %c , arg") 
		return 0;
	
	}
	return 1;

}
void read_write(int fd, char *buff, size_t sz){
        if(-1 == read(fd, buff,sz)){
            fprintf(stderr,"error while trying to read from file");
			close(fd);
			free(buff);
            exit(1);

        }
        if(-1 == write(1, buff,sz)){
            fprintf(stderr,"error while tring to write to stdout");
			close(fd);
			free(buff);
            exit(1);
        }
}