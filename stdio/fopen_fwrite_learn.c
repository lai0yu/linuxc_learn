#include <stdio.h>
#include <string.h>
int main(int argc, char* argv[]){
	FILE* fp = NULL;

	if(argc < 3){
		printf("args number is not enough\n");
		return -1;
	}

	fp = fopen(argv[1],argv[2]);
	if(strcmp(argv[2],"r") == 0){	
		if(NULL == fp){
			printf("Open file:%s with read mode failed, is file exist?\n",argv[1]);
			return -1;
		}
		printf("Open file:%s with read mode successfully, only read is allowed\n",argv[1]);
	}else if(strcmp(argv[2],"w") == 0){
		if(NULL == fp){
			printf("Open file:%s with write mode failed\n",argv[1]);
			return -1;
		}
		printf("Open file:%s with write mode successfully, if file is already exist, the file will be overwriten, ohterwise will create a new file name %s\n",argv[1],argv[1]);
	}else if(strcmp(argv[2],"a") == 0){
		if(NULL == fp){
			printf("Open file:%s with append mode failed\n",argv[1]);
			return -1;
		}
		printf("Open file:%s with append mode successfully, if the file is already exist, content will be append file into the file, otherwise will create a new file name of %s,\n",argv[1],argv[1]);
	}else if(strcmp(argv[2],"r+")==0){
		if(NULL == fp){
			printf("Open file:%s with readplus mode failed, check the file is exist;\n",argv[1]);
			return -1;
		}
		printf("Open file:%s with readplus mode successfully\n",argv[1]);
	}else if(strcmp(argv[2],"w+")==0){
		if(NULL == fp){
			printf("Open file:%s with writeplus mode failed\n",argv[1]);
			return -1;
		}
		printf("Open file:%s with writeplus mode successfully, read and write is alllowed, if the file is exists, the file will be overwite, otherwise will create a new file named: %s\n",argv[1], argv[1]);
	}else if(strcmp(argv[2],"a+")==0){
		if(NULL == fp){
			printf("Open file:%s with appendplus mode failed\n",argv[1]);
			return -1;
		}
		printf("Open file:%s with appendplus successfully, if file is exsit, read from head, write with append, otherwise will create a new file named:%s\n",argv[1],argv[1]);
	}else{
		printf("Unkonw mod:%s\n",argv[2]);
	}

	if(NULL == fp){
		printf("don't forget close the file\n");
		fclose(fp);
		fp = NULL;
	}

	return 0;
}
