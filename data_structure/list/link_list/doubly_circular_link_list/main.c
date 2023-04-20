#include "doubly_circular_link_list.h"

void main_ui_func(fdclink_list list);
void record_fdata(
		fdclink_list list,
		char* number,
		char* staddress,
		char* arraddress,
		char* DATE,
		char* TYPE,
		int stime,
		int atime,
		int value
		){
	flight_data* fdata = create_data(number, staddress, arraddress, DATE, TYPE, stime, atime, value);		
	fdclink_node* node = create_node(fdata);
	fdcllist_add_tail(list, node);
}

void init_sample_list(fdclink_list list){
	record_fdata(list,"F111","深圳","成都","2023年5月1日","A380",  8,  11, 1480);
	record_fdata(list,"F312","深圳","成都","2023年5月1日","747" ,  9,  13, 1350);
	record_fdata(list,"F613","深圳","成都","2023年5月2日","C919",  10, 14, 480);
	record_fdata(list,"F314","深圳","成都","2023年5月2日","A380",  8,  12, 1480);
	record_fdata(list,"F715","深圳","成都","2023年5月3日","C919",  9,  11, 488);
	record_fdata(list,"F016","深圳","北京","2023年5月3日","A380",  10, 13, 1480);
	record_fdata(list,"F117","深圳","北京","2023年5月1日","A380",  14, 16, 890);
	record_fdata(list,"F118","深圳","北京","2023年5月1日","747",7,  11, 2480);
	record_fdata(list,"F119","深圳","北京","2023年5月2日","A380",  12, 18, 560);
	record_fdata(list,"F211","深圳","北京","2023年5月3日","747",   15, 19, 785);
	record_fdata(list,"F985","深圳","南京","2023年5月5日","A380",  17, 20, 1491);
}

void list_ui_func(fdclink_list list){
	printf("***************S:按起飞时间排序**********************\n");
	printf("***************A:按起飞时间排序**********************\n");
	printf("请输入paixu选项:\n");	
	char c = 'Z';
	scanf("%c",&c);
	printf("%d",c);
	while(c != 'S' && c != 'A'){	
		scanf("%c",&c);
	}
	switch(c){
		case 'S':
			printf("按起飞时间排序结果如下：\n");
			fdcllist_sort_by_stime(list);
			fdcllist_print(list);
			break;
		case 'A':
			printf("按到达时间排序结果如下：\n");
			fdcllist_sort_by_atime(list);
			fdcllist_print(list);
			break;
		default:
			break;
	}
	printf("请按'#'返回主菜单");
	scanf("%c",&c);
	while(c != '#'){
		scanf("%c",&c);
	}
	main_ui_func(list);
}

void record_new_func(fdclink_list list){
	char number[18];
	char staddress[18];
	char arraddress[18];
	char DATE[12];
	char TYPE[8];
	int stime;
	int atime;
	int value;
	printf("请输入航班号：");
	scanf("%s",number);
	printf("请输入起飞站：");
	scanf("%s",staddress);
	printf("请输入到达站：");
	scanf("%s",arraddress);
	printf("请输入起飞日期：");
	scanf("%s",DATE);
	printf("请输入机型：");
	scanf("%s",TYPE);
	printf("请输入起飞时间：");
	scanf("%d",&stime);
	printf("请输入到达时间：");
	scanf("%d",&atime);
	printf("请输入票价：");
	scanf("%d",&value);	
	record_fdata(list,number,staddress,arraddress,DATE,TYPE,stime,atime,value);
	printf("录入成功! 按#返回主菜单，按N继续录入\n");
	char c;
	scanf("%c",&c);
	while(c!= '#' && c != 'N'){
		scanf("%c",&c);
	}
	switch(c){
		case '#':
			main_ui_func(list);
			break;
		case 'N':
			record_new_func(list);
			break;
		default:
			break;
	}
}

void find_by_date(fdclink_list list){
	char date[12];
	printf("请输入起飞日期:");
	scanf("%s",date);
	fdclink_list find_list = fdcllist_find_by_date(list,date);
	printf("查询结果如下:\n");
	fdcllist_print(find_list);
	printf("请按#返回主菜单\n");
	char c;
	scanf("%c",&c);
	while(c != '#'){
		scanf("%c",&c);
	}
	fdcllist_destroy(&find_list);
	main_ui_func(list);
}

void find_by_staddress(fdclink_list list){
	char staddress[18];
	printf("请输入起飞站:");
	scanf("%s",staddress);
	fdclink_list find_list = fdcllist_find_by_sta(list,staddress);
	printf("查询结果如下:\n");
	fdcllist_print(find_list);
	printf("请按#返回主菜单\n");
	char c;
	scanf("%c",&c);
	while(c != '#'){
		scanf("%c",&c);
	}
	fdcllist_destroy(&find_list);
	main_ui_func(list);
}
void find_by_arraddress(fdclink_list list){
	char arraddress[18];
	printf("请输入到达站:");
	scanf("%s",arraddress);
	fdclink_list find_list = fdcllist_find_by_arr(list,arraddress);
	printf("查询结果如下:\n");
	fdcllist_print(find_list);
	printf("请按#返回主菜单\n");
	char c;
	scanf("%c",&c);
	while(c != '#'){
		scanf("%c",&c);
	}
	fdcllist_destroy(&find_list);
	main_ui_func(list);
}
void find_func(fdclink_list list){
	printf("************D:按日期查询****************\n");
	printf("************S:按起飞站查询****************\n");
	printf("************A:按到达站查询****************\n");
	printf("************#:返回主界面****************\n");
	char c; 
	scanf("%c",&c);
	while(c != 'D' && c != 'S'&& c!='A' && c != '#'){
		scanf("%c",&c);
	}
	switch(c){
		case '#':
			main_ui_func(list);
			break;
		case 'D':
			find_by_date(list);
			break;
		case 'S':
			find_by_staddress(list);
			break;
		case 'A':
			find_by_arraddress(list);
			break;
		default:
			break;
	}
}
void print_main_ui(){
	printf("**********************************************************\n");
	printf("*               欢迎来到死鬼航空管理系统                 *\n");
	printf("*                                                        *\n");
	printf("*                                                        *\n");
	printf("*                       主菜单                           *\n");
	printf("*                                                        *\n");
	printf("*                                                        *\n");
	printf("*                    A): 航班列表                        *\n");
	printf("*                                                        *\n");
	printf("*                    B): 录入新航班                      *\n");
	printf("*                                                        *\n");
	printf("*                    C): 查询                            *\n");
	printf("*                                                        *\n");
	printf("*                    D): 删除                            *\n");
	printf("*                                                        *\n");
	printf("*                    E): 更新航班信息                    *\n");
	printf("*                                                        *\n");
	printf("*                    X): 退出系统                        *\n");
	printf("*                                                        *\n");
	printf("**********************************************************\n");
}

void main_ui_func(fdclink_list list){
	print_main_ui();
	printf("请输入caidan选项：");
	char c;
	scanf("%c",&c);
	while(c !='X'){
		switch(c){
			case 'A' :
				list_ui_func(list);
				break;	
			case 'B' :
                record_new_func(list);
				break;
			case 'C' :
				find_func(list);
				break;
			case 'D' :
				printf("没时间做了\n");
				break;
			case 'E' :
				printf("没时间做了\n");
				break;
			default:
				break;
		}
		scanf("%c",&c);
	}
	exit(0);
}

int main(void){
	fdclink_list list = fdcllist_init();
	init_sample_list(list);
	main_ui_func(list);
//	fdcllist_print(list);
	return 0;
}

