int string_eq(char *arg, char *check){
	int min_sz=0;
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