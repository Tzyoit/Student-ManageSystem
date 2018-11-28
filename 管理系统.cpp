#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<conio.h>       //getche的头文件
#define SIZE 50
struct Student{
	char name[10];		//定义结构体
	int ID;
	float Chinese;
	float Math;
	float English;
	float sum;
	float average;
	int xuefen;
}student[SIZE]={0};		//初始化结构体

int p=0;        //统计人数

//H
void add();				//功能 添加 模块
void Menu();			//菜单页面
//T
void rank(); 			//功能 排序 模块
void query();			//功能 查询 模块
void revamp(); 			//功能 修改 模块
void browse();			//功能 浏览 模块
//C
void mysort(int n);		//冒泡排序
void change(int n,int t);//实现结构体数组两个元素的交换
void Print();
//L
void compute(int n);	//用于计算总分和平均分
void student_inf(int n);//打印单个学生信息

int main(){
	//system("color FA");	//设置控制台背景和字体颜色
	int ch;
	FILE *fp;
	fp=fopen("C:\\student.dat","r");		//每次运行读取文件(设置为只读)
			if(fp!=NULL){					//若文件存在,则读取信息到结构体
				while(!feof(fp)){
					if(!feof(fp)){
						fread(&student[p],sizeof(student[0]),1,fp);
						p++;
					}
				}
				p--;				//多加了
			}
			else{
				printf("error!");
				return 0;
			}
			fclose(fp);
	while(1){
		system("cls");	//清除屏幕
		Menu();
		printf("请输入对应编号(1-6):");
		ch=getche()-48;//int getche（）返回一个ascii码，且不显示。减去48为整型
		if(ch==6){
			puts("\n\nThank You For Your Use!");		//退出系统
			break;
		}
		else{

			switch(ch){
				case 1:
					query();//查询
					break;
				case 2:
					add();//添加
					break;
				case 3:
					revamp();//删除
					break;
				case 4:
					browse();//浏览
					break;
				case 5:
					rank();//排序
					break;
				default :
					printf("\a");
					MessageBox(0,"无此功能,请重新输入!","ERROR!",0);
			}
		}
	}
	return 0;
}
void Menu(){
	puts("	╔═══════════════════════════════════════╗");
	puts("	║  成    绩    管    理    系    统        ");
	puts("	╠═══════════════════════════════════════╣");
	puts("	║                                          ");
	puts("	║ 1.查  询            2.添  加             ");
	puts("	║                                          ");
	puts("	║ 3.删  改            4.浏  览             ");
	puts("	║                                          ");
	puts("	║ 5.排  序            6.退  出             ");
	puts("	║                                          ");
	puts("	╚═══════════════════════════════════════╝");
}
void add(){
	FILE *fp;
	fp=fopen("C:\\student.dat","ab+");			//以追加读写模式打开
	if(fp==NULL){
		puts("ERROR!");
		return;
	}
	system("cls");
	puts("╔═════════════════════════════════════════╗");
	puts("║                                                                                  ║");
	puts("║                            学  生  信  息  添  加                                ║");
	puts("║                                                                                  ║");
	puts("╚═════════════════════════════════════════╝");
	printf("请输入学生学号:");
	scanf("%d",&student[p].ID);
	getchar();//读取回车
	
	printf("请输入学生姓名:");
	gets(student[p].name);

	printf("请输入该生的语文成绩:");
	scanf("%f",&student[p].Chinese);
		
	printf("请输入该生的数学成绩:");
	scanf("%f",&student[p].Math);

	printf("请输入该生的英语成绩:");
	scanf("%f",&student[p].English);

	printf("请输入该生的学分:");
	scanf("%d",&student[p].xuefen);
	
	compute(p);//算总分和平均分
	fwrite(&student[p],sizeof(student[p]),1,fp);//原型int fwrite(void *buffer,unsigned siZe数据块,unsigned count,FILE *fp)
	fclose(fp);                       //按二进制形式，将由buffer指定的数据缓冲区内的siZe*count个数据写入由fp指定的文件中去。
	puts("你添加的信息如下:");
	student_inf(p);
	puts("按任意键返回主菜单...");
	getch();
	p++;               				 //学生人数
}
void compute(int n){
	student[n].sum=student[n].Chinese+student[n].Math+student[n].English;
	student[n].average=student[n].sum/3;		//用于计算总分和平均分
}
void query(){
	int id=0,j=0;
	char ch;
	char name[20];
	system("cls");
	puts("╔═════════════════════════════════════════╗");
	puts("║                            学  生  信  息  查  询                                ║");
	puts("║                                                                                  ║");
	puts("║              1.按 学 号 查 询                2.按 姓 名 查 询                    ║");
	puts("║              						                                              ║");
	puts("╚═════════════════════════════════════════╝");
	Print();
	printf("你的选择是:");
	fflush(stdin);
	ch=getche();
	if(ch!='1'&&ch!='2'){
		printf("\a");       //转义字符007，发出滴的声音
		MessageBox(0,"无此功能!","ERROR!",0);
		return;
	}
	if(ch=='1'){
		printf("\n请输入学生学号（输入0结束）:");
		scanf("%d",&id);
		while(student[j].ID!=0){
			if(student[j].ID==id){
				student_inf(j);
				puts("按任意键返回主菜单...");
				getch();	//暂停等待确认
				return;
			}
			j++;
		}
	}
	else if(ch=='2'){
		printf("\n请输入学生姓名:");
		gets(name);
		while(student[j].ID!=0){
			if(strcmp(name,student[j].name)==0){
				student_inf(j);
				puts("按任意键返回主菜单...");
				getch();	//暂停等待确认
				return;
			}
			j++;
		}
	}
	printf("\a");
	MessageBox(0,"未找到该生信息!","ERROR!",0);
	//打印提示信息
}
void student_inf(int n){
	//puts("╔═════╦═════╦═════╦═════╦═════╦═════╦═════╗");
	puts("║姓 名 ║学 号 ║语 文 ║数 学 ║英 语 ║总 分 ║平均分 ║学 分 ║");
	//puts("╠═════╬═════╬═════╬═════╬═════╬═════╬═════╣");
  printf("║%s   %d   %6.1f  ",student[n].name,student[n].ID,student[n].Chinese);
    printf(" %6.1f  %6.1f  %6.1f  %6.1f  %d  ║\n",student[n].Math,student[n].English,student[n].sum,student[n].average,student[n].xuefen);
	//puts("╚═════╩═════╩═════╩═════╩═════╩═════╩═════╝");
}
void revamp(){
	int id,j=0,i,f=0;
	FILE *fp;
	char ch;
	system("cls");
	puts("╔═════════════════════════════════════════╗");
	puts("║                             删    改    功    能                                 ║");
	puts("║                                                                                  ║");
	puts("║                       1.修  改                2.删  除                           ║");
	puts("╚═════════════════════════════════════════╝");
	Print();
	printf("请输入你的选择:");
	fflush(stdin);
	ch=getche();//不用按回车
	if(ch!='1'&&ch!='2'){
		printf("\a");
		MessageBox(0,"无此功能!","ERROR!",0);
		return;
	}
	printf("\n请输入学生学号:");
	scanf("%d",&id);	//保存id用于遍历查找此id
	while(student[j].ID!=0){
			if(student[j].ID==id){		//找到则打印学生信息
				student_inf(j);
				f=1;
				break;
			}
			j++;
	}
	if(f==0){
		printf("\a");
		MessageBox(0,"未找到该生信息!","ERROR!",0);
		//打印提示信息
		return;
	}
	if(ch=='1'){
		printf("请输入该生的语文成绩:");
		scanf("%f",&student[j].Chinese);
		printf("请输入该生的数学成绩:");
		scanf("%f",&student[j].Math);
		printf("请输入该生的英语成绩:");
		scanf("%f",&student[j].English);
		compute(j);
		student_inf(j);
		FILE *fp;
		fp=fopen("C:\\student.dat","wb+");

		i=p-1;
		while(i>=0){
			fwrite(&student[i],sizeof(student[i]),1,fp);    //将结构体数组信息读入到文件
			i--;
		}
		puts("信息修改并保存成功!");
		fclose(fp);
	}
	else if(ch=='2'){
		printf("确认删除该学生信息?是(Y)否(N):");
		ch=getche();
		if(ch!='y'&&ch!='Y'){
			puts("\n未删除该学生信息!");
			puts("\n按任意键返回主菜单...");
			getch();
			return;
		}
		while(student[j].ID!=0){
			if(student[j].ID==id){
				change(j,p-1);
				fp=fopen("C:\\student.dat","wb+");
				i=p-2;
				//删除机制:将最后一位(即p-1)的信息与待删除的信息交换
				//        然后重新写入前数据 (p-1)位数据,最后一位舍弃
				while(i>=0){
					fwrite(&student[i],sizeof(student[i]),1,fp);
					i--;
				}
				puts("\n该学生信息删除成功!");
				fclose(fp);
				break;
			}
		}
	}
	p=0;		//			修改或删除信息后重新读取信息
	fp=fopen("C:\\student.dat","rb+");
	if(fp!=NULL){
			while(!feof(fp)){
				if(!feof(fp)){
				fread(&student[p],sizeof(student[0]),1,fp);
				p++;
				}
			}
			p--;
		}
	fclose(fp);
	puts("\n按任意键返回主菜单...");
	getch();
	return;
}
void mysort(int n){				//冒泡排序,以形参来决定以哪一个属性排序
	int i,j;					//然后调用change(a,b)交换结构体数组两个元素的值
	switch(n){
		case 1:
			for(i=0;i<p;i++){
				for(j=0;j<p-i-1;j++){
					if(student[j].Chinese>student[j+1].Chinese){
						change(j,j+1);
					}
				}
			}
			break;
		case 2:
			for(i=0;i<p;i++){
				for(j=0;j<p-i-1;j++){
					if(student[j].Math>student[j+1].Math){
						change(j,j+1);
					}
				}
			}
			break;
		case 3:
			for(i=0;i<p;i++){
				for(j=0;j<p-i-1;j++){
					if(student[j].English>student[j+1].English){
						change(j,j+1);
					}
				}
			}
			break;
		case 4:
			for(i=0;i<p;i++){
				for(j=0;j<p-i-1;j++){
					if(student[j].average>student[j+1].average){
						change(j,j+1);
					}
				}
			}
			break;
		case 5:
			for(i=0;i<p;i++){
				for(j=0;j<p-i-1;j++){
					if(student[j].sum>student[j+1].sum){
						change(j,j+1);
					}
				}
			}
			break;
	}
}
void change(int n,int t){
	float temp;
	char h[SIZE];
	int x;
	temp=student[n].average;
	student[n].average=student[t].average;
	student[t].average=temp;

	temp=student[n].Chinese;
	student[n].Chinese=student[t].Chinese;
	student[t].Chinese=temp;

	temp=student[n].English;
	student[n].English=student[t].English;
	student[t].English=temp;

	temp=student[n].Math;
	student[n].Math=student[t].Math;
	student[t].Math=temp;

	temp=student[n].xuefen;
	student[n].xuefen=student[t].xuefen;
	student[t].xuefen=temp;
	
	temp=student[n].sum;
	student[n].sum=student[t].sum;
	student[t].sum=temp;

	x=student[n].ID;
	student[n].ID=student[t].ID;
	student[t].ID=x;

	strcpy(h,student[n].name);
	strcpy(student[n].name,student[t].name);
	strcpy(student[t].name,h);
}
void rank(){
	int ch,j;
	system("cls");
	puts("╔═════════════════════════════════════════╗");
	puts("║                              排    序    功    能                                ║");
	puts("║                                                                                  ║");
	puts("║                1.语 文 成 绩 排 序           2.数 学 成 绩 排 序                 ║");
	puts("║                                                                                  ║");
	puts("║                3.英 语 成 绩 排 序           4.平 均 成 绩 排 序                 ║");
	puts("║                                                                                  ║");
	puts("║                              5.总  成  绩  排  序                                ║");
	puts("╚═════════════════════════════════════════╝");
	printf("你的选择是:");
	ch=getche()-48;
	printf("\n");
	if(ch>5){
		printf("\a");
		MessageBox(0,"无此功能!","ERROR!",0);
		return;
	}
	puts("╔═════╦═════╦═════╦═════╦═════╦═════╦═════╗");
	puts("║  姓  名  ║  学  号  ║  语  文  ║  数  学  ║  英  语  ║  总  分  ║ 平 均 分 ║");
	puts("╠═════╬═════╬═════╬═════╬═════╬═════╬═════╣");
	mysort(ch);
	for(j=0;j<p;j++){
		printf("║%-6s  ║%-6d	  ║%-6.1f    ║",student[j].name,student[j].ID,student[j].Chinese);
		printf("%-6.1f   ║%-6.1f    ║%-6.1f    ║%-6.1f    ║\n",
	student[j].Math,student[j].English,student[j].sum,student[j].average);
	}
	puts("╚═════╩═════╩═════╩═════╩═════╩═════╩═════╝");
	puts("按任意键返回主菜单...");
	getch();
}
void browse(){
	int ch,j;
	int x=0,y=0,z=0;
	float c,m,e;
	system("cls");
	puts("╔═════════════════════════════════════════╗");
	puts("║                              浏    览    功    能                                ║");
	puts("║                                                                                  ║");
	puts("║                1.语 文 及 格 学 生 信 息           2.数 学 及 格 学 生 信 息     ║");
	puts("║                                                                                  ║");
	puts("║                3.英 语 及 格 学 生 信 息           4.全 部 成 绩 查 询           ║");
	puts("║                                                                                  ║");
	puts("║                5.显 示 该 班 及 格 率              ( >=90分为及格 )              ║");
	puts("╚═════╩═════╩═════╩═════╩═════╩═════╩═════╝");
	printf("你的选择是:");
	ch=getche()-48;
	printf("\n");
	if(ch>5){
		printf("\n输入错误，3秒后返回并重新输入！\n");
		Sleep(3000);
		browse();
	}
	mysort(ch);
	switch(ch){
				case 1:
			
					puts("╔═════════════════════════════════════════╗");
					puts("║                语    文    及    格    学   生    信    息                       ║");
					puts("╠═════╦═════╦═════╦═════╦═════╦═════╦═════╣");
					puts("║  姓  名  ║  学  号  ║  语  文  ║  数  学  ║  英  语  ║  总  分  ║ 平 均 分 ║");
					puts("╠═════╬═════╬═════╬═════╬═════╬═════╬═════╣");
					for(j=0;j<p;j++)
	 				if(student[j].Chinese>90){
						printf("║%-6s    ║%-6d    ║%-6.1f  ║",student[j].name,student[j].ID,student[j].Chinese);
						printf("  %-6.1f  ║%-6.1f  ║%-6.1f  ║%-6.1f  ║\n",
							student[j].Math,student[j].English,student[j].sum,student[j].average);
					}
					puts("╚═════╩═════╩═════╩═════╩═════╩═════╩═════╝");
					break;

				case 2:
				
					puts("╔═════════════════════════════════════════╗");
					puts("║                数    学     及    格	  学   生    信    息                     ║");
					puts("╠═════╦═════╦═════╦═════╦═════╦═════╦═════╣");
					puts("║  姓  名  ║  学  号  ║  语  文  ║  数  学  ║  英  语  ║  总  分  ║ 平 均 分 ║");
					puts("╠═════╬═════╬═════╬═════╬═════╬═════╬═════╣");
					for(j=0;j<p;j++)
					if(student[j].Math>90){
						printf("║%-6s    ║%-6d    ║%-6.1f  ║",student[j].name,student[j].ID,student[j].Chinese);
						printf("  %-6.1f  ║%-6.1f  ║%-6.1f  ║%-6.1f  ║\n",
							student[j].Math,student[j].English,student[j].sum,student[j].average);
					}
					puts("╚═════╩═════╩═════╩═════╩═════╩═════╩═════╝");
					break;

				case 3:
				
					puts("╔═════════════════════════════════════════╗");
					puts("║                英    语     及    格    学   生    信    息                      ║");
					puts("╠═════╦═════╦═════╦═════╦═════╦═════╦═════╣");
					puts("║  姓  名  ║  学  号  ║  语  文  ║  数  学  ║  英  语  ║  总  分  ║ 平 均 分 ║");
					puts("╠═════╬═════╬═════╬═════╬═════╬═════╬═════╣");
					for(j=0;j<p;j++)
					if(student[j].English>90){
						printf("║%-6s    ║%-6d    ║%-6.1f  ║",student[j].name,student[j].ID,student[j].Chinese);
						printf("  %-6.1f  ║%-6.1f  ║%-6.1f  ║%-6.1f  ║\n",
							student[j].Math,student[j].English,student[j].sum,student[j].average);
					}
					puts("╚═════╩═════╩═════╩═════╩═════╩═════╩═════╝");
					break;
			case 4:
					puts("╔═════════════════════════════════════════╗");
					puts("║          学          生          信          息          浏          览          ║");
					puts("╠═════╦═════╦═════╦═════╦═════╦═════╦═════╣");
					puts("║  姓  名      学  号      语  文      数  学     英  语      总  分     平 均 分 ");
					puts("╠═════╬═════╬═════╬═════╬═════╬═════╬═════╣");
					for(j=0;j<p;j++){
						printf("║%-6s    ║%-6d    ║%-6.1f  ║",student[j].name,student[j].ID,student[j].Chinese);
						printf("  %-6.1f  ║%-6.1f  ║%-6.1f  ║%-6.1f  ║\n",
							student[j].Math,student[j].English,student[j].sum,student[j].average);
					}
					puts("╚═════╩═════╩═════╩═════╩═════╩═════╩═════╝");
					break;
            case 5:
					for(j=0;j<p;j++)
	 				{
	 					if(student[j].Chinese>60)x++;
	 				}   //语文及格人数
	 				printf("x = %d ",x);
					for(j=0;j<p;j++)
					{
	 					if(student[j].Chinese>60)y++;
					}   //数学及格人数
					printf("y = %d ",y);
					for(j=0;j<p;j++)
					{
						if(student[j].Chinese>60)z++;
					}	//英语及格人数
					printf("z = %d ",z);
					c = (float)x/p;
					m = (float)y/p;
					e = (float)z/p;
					printf("\n该班语文录取率为：%0.2f  数学录取率为：%0.2f  英语录取率为：%0.2f\n",c,m,e);
					break;
		}
	puts("按任意键返回主菜单...");
	getch();
}
void Print()
{
	int j;
	printf("现全部学生信息如下：\n");
	puts(" = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =  ");
	puts("║          学          生          信          息          浏          览          ║");
	puts("╠= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = ╣");
	puts("║  姓  名   学  号    语  文    数  学   英  语    总  分   平 均 分   学分	    ");
		for(j=0;j<p;j++){
 	//printf("║%-10s   %10d      %-6.1f    %-6.1f    %-6.1f     %-6.1f   %-6.1f  \n"
//	 ,student[j].name,student[j].ID,student[j].Chinese),student[j].Math,student[j].English,student[j].sum,student[j].average);
		printf("║ %5s    %6d    %6.1f\t",student[j].name,student[j].ID,student[j].Chinese);
		printf("%   6.1f    %6.1f    %6.1f   %6.1f    %d\n",
							student[j].Math,student[j].English,student[j].sum,student[j].average,student[j].xuefen);
	}
}

