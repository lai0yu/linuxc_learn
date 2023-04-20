#include <stdio.h>
#include <string.h>
int main(int argc, char* argv[]){
	if(argc < 3){
		printf("Usage:%s<read_filename> <write_filenname>\n", argv[0]);
		return -1;
	}

	FILE* fp_r = NULL,*fp_w=NULL;
	fp_r = fopen(argv[1],"r");
	
	if(NULL == fp_r){
		printf("Open file:%s failed!\n",argv[1]);
		return -1;
	}

	fp_w = fopen(argv[2],"w");
	if(NULL == fp_w){
		printf("Open file:%s failed!\n",argv[2]);
		return -1;
	}

	char buf[1];
	
	fseek(fp_r,-1,SEEK_END);
	long offset = ftell(fp_r);
	
	while(offset >= 0){
		fseek(fp_r,offset,SEEK_SET);
		bzero(buf,sizeof(buf));
		int ret = fread(buf,sizeof(buf),1,fp_r);
		if(ret <= 0){
			printf("read failed\n");
			break;
		}
		fwrite(buf,sizeof(buf),1,fp_w);
		offset--;
	}
	fclose(fp_r);
	fclose(fp_w);
	return 0;
}
