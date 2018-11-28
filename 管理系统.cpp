#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<conio.h>       //getche��ͷ�ļ�
#define SIZE 50
struct Student{
	char name[10];		//����ṹ��
	int ID;
	float Chinese;
	float Math;
	float English;
	float sum;
	float average;
	int xuefen;
}student[SIZE]={0};		//��ʼ���ṹ��

int p=0;        //ͳ������

//H
void add();				//���� ��� ģ��
void Menu();			//�˵�ҳ��
//T
void rank(); 			//���� ���� ģ��
void query();			//���� ��ѯ ģ��
void revamp(); 			//���� �޸� ģ��
void browse();			//���� ��� ģ��
//C
void mysort(int n);		//ð������
void change(int n,int t);//ʵ�ֽṹ����������Ԫ�صĽ���
void Print();
//L
void compute(int n);	//���ڼ����ֺܷ�ƽ����
void student_inf(int n);//��ӡ����ѧ����Ϣ

int main(){
	//system("color FA");	//���ÿ���̨������������ɫ
	int ch;
	FILE *fp;
	fp=fopen("C:\\student.dat","r");		//ÿ�����ж�ȡ�ļ�(����Ϊֻ��)
			if(fp!=NULL){					//���ļ�����,���ȡ��Ϣ���ṹ��
				while(!feof(fp)){
					if(!feof(fp)){
						fread(&student[p],sizeof(student[0]),1,fp);
						p++;
					}
				}
				p--;				//�����
			}
			else{
				printf("error!");
				return 0;
			}
			fclose(fp);
	while(1){
		system("cls");	//�����Ļ
		Menu();
		printf("�������Ӧ���(1-6):");
		ch=getche()-48;//int getche��������һ��ascii�룬�Ҳ���ʾ����ȥ48Ϊ����
		if(ch==6){
			puts("\n\nThank You For Your Use!");		//�˳�ϵͳ
			break;
		}
		else{

			switch(ch){
				case 1:
					query();//��ѯ
					break;
				case 2:
					add();//���
					break;
				case 3:
					revamp();//ɾ��
					break;
				case 4:
					browse();//���
					break;
				case 5:
					rank();//����
					break;
				default :
					printf("\a");
					MessageBox(0,"�޴˹���,����������!","ERROR!",0);
			}
		}
	}
	return 0;
}
void Menu(){
	puts("	�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[");
	puts("	�U  ��    ��    ��    ��    ϵ    ͳ        ");
	puts("	�d�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�g");
	puts("	�U                                          ");
	puts("	�U 1.��  ѯ            2.��  ��             ");
	puts("	�U                                          ");
	puts("	�U 3.ɾ  ��            4.�  ��             ");
	puts("	�U                                          ");
	puts("	�U 5.��  ��            6.��  ��             ");
	puts("	�U                                          ");
	puts("	�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a");
}
void add(){
	FILE *fp;
	fp=fopen("C:\\student.dat","ab+");			//��׷�Ӷ�дģʽ��
	if(fp==NULL){
		puts("ERROR!");
		return;
	}
	system("cls");
	puts("�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[");
	puts("�U                                                                                  �U");
	puts("�U                            ѧ  ��  ��  Ϣ  ��  ��                                �U");
	puts("�U                                                                                  �U");
	puts("�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a");
	printf("������ѧ��ѧ��:");
	scanf("%d",&student[p].ID);
	getchar();//��ȡ�س�
	
	printf("������ѧ������:");
	gets(student[p].name);

	printf("��������������ĳɼ�:");
	scanf("%f",&student[p].Chinese);
		
	printf("�������������ѧ�ɼ�:");
	scanf("%f",&student[p].Math);

	printf("�����������Ӣ��ɼ�:");
	scanf("%f",&student[p].English);

	printf("�����������ѧ��:");
	scanf("%d",&student[p].xuefen);
	
	compute(p);//���ֺܷ�ƽ����
	fwrite(&student[p],sizeof(student[p]),1,fp);//ԭ��int fwrite(void *buffer,unsigned siZe���ݿ�,unsigned count,FILE *fp)
	fclose(fp);                       //����������ʽ������bufferָ�������ݻ������ڵ�siZe*count������д����fpָ�����ļ���ȥ��
	puts("����ӵ���Ϣ����:");
	student_inf(p);
	puts("��������������˵�...");
	getch();
	p++;               				 //ѧ������
}
void compute(int n){
	student[n].sum=student[n].Chinese+student[n].Math+student[n].English;
	student[n].average=student[n].sum/3;		//���ڼ����ֺܷ�ƽ����
}
void query(){
	int id=0,j=0;
	char ch;
	char name[20];
	system("cls");
	puts("�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[");
	puts("�U                            ѧ  ��  ��  Ϣ  ��  ѯ                                �U");
	puts("�U                                                                                  �U");
	puts("�U              1.�� ѧ �� �� ѯ                2.�� �� �� �� ѯ                    �U");
	puts("�U              						                                              �U");
	puts("�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a");
	Print();
	printf("���ѡ����:");
	fflush(stdin);
	ch=getche();
	if(ch!='1'&&ch!='2'){
		printf("\a");       //ת���ַ�007�������ε�����
		MessageBox(0,"�޴˹���!","ERROR!",0);
		return;
	}
	if(ch=='1'){
		printf("\n������ѧ��ѧ�ţ�����0������:");
		scanf("%d",&id);
		while(student[j].ID!=0){
			if(student[j].ID==id){
				student_inf(j);
				puts("��������������˵�...");
				getch();	//��ͣ�ȴ�ȷ��
				return;
			}
			j++;
		}
	}
	else if(ch=='2'){
		printf("\n������ѧ������:");
		gets(name);
		while(student[j].ID!=0){
			if(strcmp(name,student[j].name)==0){
				student_inf(j);
				puts("��������������˵�...");
				getch();	//��ͣ�ȴ�ȷ��
				return;
			}
			j++;
		}
	}
	printf("\a");
	MessageBox(0,"δ�ҵ�������Ϣ!","ERROR!",0);
	//��ӡ��ʾ��Ϣ
}
void student_inf(int n){
	//puts("�X�T�T�T�T�T�j�T�T�T�T�T�j�T�T�T�T�T�j�T�T�T�T�T�j�T�T�T�T�T�j�T�T�T�T�T�j�T�T�T�T�T�[");
	puts("�U�� �� �Uѧ �� �U�� �� �U�� ѧ �UӢ �� �U�� �� �Uƽ���� �Uѧ �� �U");
	//puts("�d�T�T�T�T�T�p�T�T�T�T�T�p�T�T�T�T�T�p�T�T�T�T�T�p�T�T�T�T�T�p�T�T�T�T�T�p�T�T�T�T�T�g");
  printf("�U%s   %d   %6.1f  ",student[n].name,student[n].ID,student[n].Chinese);
    printf(" %6.1f  %6.1f  %6.1f  %6.1f  %d  �U\n",student[n].Math,student[n].English,student[n].sum,student[n].average,student[n].xuefen);
	//puts("�^�T�T�T�T�T�m�T�T�T�T�T�m�T�T�T�T�T�m�T�T�T�T�T�m�T�T�T�T�T�m�T�T�T�T�T�m�T�T�T�T�T�a");
}
void revamp(){
	int id,j=0,i,f=0;
	FILE *fp;
	char ch;
	system("cls");
	puts("�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[");
	puts("�U                             ɾ    ��    ��    ��                                 �U");
	puts("�U                                                                                  �U");
	puts("�U                       1.��  ��                2.ɾ  ��                           �U");
	puts("�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a");
	Print();
	printf("���������ѡ��:");
	fflush(stdin);
	ch=getche();//���ð��س�
	if(ch!='1'&&ch!='2'){
		printf("\a");
		MessageBox(0,"�޴˹���!","ERROR!",0);
		return;
	}
	printf("\n������ѧ��ѧ��:");
	scanf("%d",&id);	//����id���ڱ������Ҵ�id
	while(student[j].ID!=0){
			if(student[j].ID==id){		//�ҵ����ӡѧ����Ϣ
				student_inf(j);
				f=1;
				break;
			}
			j++;
	}
	if(f==0){
		printf("\a");
		MessageBox(0,"δ�ҵ�������Ϣ!","ERROR!",0);
		//��ӡ��ʾ��Ϣ
		return;
	}
	if(ch=='1'){
		printf("��������������ĳɼ�:");
		scanf("%f",&student[j].Chinese);
		printf("�������������ѧ�ɼ�:");
		scanf("%f",&student[j].Math);
		printf("�����������Ӣ��ɼ�:");
		scanf("%f",&student[j].English);
		compute(j);
		student_inf(j);
		FILE *fp;
		fp=fopen("C:\\student.dat","wb+");

		i=p-1;
		while(i>=0){
			fwrite(&student[i],sizeof(student[i]),1,fp);    //���ṹ��������Ϣ���뵽�ļ�
			i--;
		}
		puts("��Ϣ�޸Ĳ�����ɹ�!");
		fclose(fp);
	}
	else if(ch=='2'){
		printf("ȷ��ɾ����ѧ����Ϣ?��(Y)��(N):");
		ch=getche();
		if(ch!='y'&&ch!='Y'){
			puts("\nδɾ����ѧ����Ϣ!");
			puts("\n��������������˵�...");
			getch();
			return;
		}
		while(student[j].ID!=0){
			if(student[j].ID==id){
				change(j,p-1);
				fp=fopen("C:\\student.dat","wb+");
				i=p-2;
				//ɾ������:�����һλ(��p-1)����Ϣ���ɾ������Ϣ����
				//        Ȼ������д��ǰ���� (p-1)λ����,���һλ����
				while(i>=0){
					fwrite(&student[i],sizeof(student[i]),1,fp);
					i--;
				}
				puts("\n��ѧ����Ϣɾ���ɹ�!");
				fclose(fp);
				break;
			}
		}
	}
	p=0;		//			�޸Ļ�ɾ����Ϣ�����¶�ȡ��Ϣ
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
	puts("\n��������������˵�...");
	getch();
	return;
}
void mysort(int n){				//ð������,���β�����������һ����������
	int i,j;					//Ȼ�����change(a,b)�����ṹ����������Ԫ�ص�ֵ
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
	puts("�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[");
	puts("�U                              ��    ��    ��    ��                                �U");
	puts("�U                                                                                  �U");
	puts("�U                1.�� �� �� �� �� ��           2.�� ѧ �� �� �� ��                 �U");
	puts("�U                                                                                  �U");
	puts("�U                3.Ӣ �� �� �� �� ��           4.ƽ �� �� �� �� ��                 �U");
	puts("�U                                                                                  �U");
	puts("�U                              5.��  ��  ��  ��  ��                                �U");
	puts("�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a");
	printf("���ѡ����:");
	ch=getche()-48;
	printf("\n");
	if(ch>5){
		printf("\a");
		MessageBox(0,"�޴˹���!","ERROR!",0);
		return;
	}
	puts("�X�T�T�T�T�T�j�T�T�T�T�T�j�T�T�T�T�T�j�T�T�T�T�T�j�T�T�T�T�T�j�T�T�T�T�T�j�T�T�T�T�T�[");
	puts("�U  ��  ��  �U  ѧ  ��  �U  ��  ��  �U  ��  ѧ  �U  Ӣ  ��  �U  ��  ��  �U ƽ �� �� �U");
	puts("�d�T�T�T�T�T�p�T�T�T�T�T�p�T�T�T�T�T�p�T�T�T�T�T�p�T�T�T�T�T�p�T�T�T�T�T�p�T�T�T�T�T�g");
	mysort(ch);
	for(j=0;j<p;j++){
		printf("�U%-6s  �U%-6d	  �U%-6.1f    �U",student[j].name,student[j].ID,student[j].Chinese);
		printf("%-6.1f   �U%-6.1f    �U%-6.1f    �U%-6.1f    �U\n",
	student[j].Math,student[j].English,student[j].sum,student[j].average);
	}
	puts("�^�T�T�T�T�T�m�T�T�T�T�T�m�T�T�T�T�T�m�T�T�T�T�T�m�T�T�T�T�T�m�T�T�T�T�T�m�T�T�T�T�T�a");
	puts("��������������˵�...");
	getch();
}
void browse(){
	int ch,j;
	int x=0,y=0,z=0;
	float c,m,e;
	system("cls");
	puts("�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[");
	puts("�U                              �    ��    ��    ��                                �U");
	puts("�U                                                                                  �U");
	puts("�U                1.�� �� �� �� ѧ �� �� Ϣ           2.�� ѧ �� �� ѧ �� �� Ϣ     �U");
	puts("�U                                                                                  �U");
	puts("�U                3.Ӣ �� �� �� ѧ �� �� Ϣ           4.ȫ �� �� �� �� ѯ           �U");
	puts("�U                                                                                  �U");
	puts("�U                5.�� ʾ �� �� �� �� ��              ( >=90��Ϊ���� )              �U");
	puts("�^�T�T�T�T�T�m�T�T�T�T�T�m�T�T�T�T�T�m�T�T�T�T�T�m�T�T�T�T�T�m�T�T�T�T�T�m�T�T�T�T�T�a");
	printf("���ѡ����:");
	ch=getche()-48;
	printf("\n");
	if(ch>5){
		printf("\n�������3��󷵻ز��������룡\n");
		Sleep(3000);
		browse();
	}
	mysort(ch);
	switch(ch){
				case 1:
			
					puts("�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[");
					puts("�U                ��    ��    ��    ��    ѧ   ��    ��    Ϣ                       �U");
					puts("�d�T�T�T�T�T�j�T�T�T�T�T�j�T�T�T�T�T�j�T�T�T�T�T�j�T�T�T�T�T�j�T�T�T�T�T�j�T�T�T�T�T�g");
					puts("�U  ��  ��  �U  ѧ  ��  �U  ��  ��  �U  ��  ѧ  �U  Ӣ  ��  �U  ��  ��  �U ƽ �� �� �U");
					puts("�d�T�T�T�T�T�p�T�T�T�T�T�p�T�T�T�T�T�p�T�T�T�T�T�p�T�T�T�T�T�p�T�T�T�T�T�p�T�T�T�T�T�g");
					for(j=0;j<p;j++)
	 				if(student[j].Chinese>90){
						printf("�U%-6s    �U%-6d    �U%-6.1f  �U",student[j].name,student[j].ID,student[j].Chinese);
						printf("  %-6.1f  �U%-6.1f  �U%-6.1f  �U%-6.1f  �U\n",
							student[j].Math,student[j].English,student[j].sum,student[j].average);
					}
					puts("�^�T�T�T�T�T�m�T�T�T�T�T�m�T�T�T�T�T�m�T�T�T�T�T�m�T�T�T�T�T�m�T�T�T�T�T�m�T�T�T�T�T�a");
					break;

				case 2:
				
					puts("�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[");
					puts("�U                ��    ѧ     ��    ��	  ѧ   ��    ��    Ϣ                     �U");
					puts("�d�T�T�T�T�T�j�T�T�T�T�T�j�T�T�T�T�T�j�T�T�T�T�T�j�T�T�T�T�T�j�T�T�T�T�T�j�T�T�T�T�T�g");
					puts("�U  ��  ��  �U  ѧ  ��  �U  ��  ��  �U  ��  ѧ  �U  Ӣ  ��  �U  ��  ��  �U ƽ �� �� �U");
					puts("�d�T�T�T�T�T�p�T�T�T�T�T�p�T�T�T�T�T�p�T�T�T�T�T�p�T�T�T�T�T�p�T�T�T�T�T�p�T�T�T�T�T�g");
					for(j=0;j<p;j++)
					if(student[j].Math>90){
						printf("�U%-6s    �U%-6d    �U%-6.1f  �U",student[j].name,student[j].ID,student[j].Chinese);
						printf("  %-6.1f  �U%-6.1f  �U%-6.1f  �U%-6.1f  �U\n",
							student[j].Math,student[j].English,student[j].sum,student[j].average);
					}
					puts("�^�T�T�T�T�T�m�T�T�T�T�T�m�T�T�T�T�T�m�T�T�T�T�T�m�T�T�T�T�T�m�T�T�T�T�T�m�T�T�T�T�T�a");
					break;

				case 3:
				
					puts("�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[");
					puts("�U                Ӣ    ��     ��    ��    ѧ   ��    ��    Ϣ                      �U");
					puts("�d�T�T�T�T�T�j�T�T�T�T�T�j�T�T�T�T�T�j�T�T�T�T�T�j�T�T�T�T�T�j�T�T�T�T�T�j�T�T�T�T�T�g");
					puts("�U  ��  ��  �U  ѧ  ��  �U  ��  ��  �U  ��  ѧ  �U  Ӣ  ��  �U  ��  ��  �U ƽ �� �� �U");
					puts("�d�T�T�T�T�T�p�T�T�T�T�T�p�T�T�T�T�T�p�T�T�T�T�T�p�T�T�T�T�T�p�T�T�T�T�T�p�T�T�T�T�T�g");
					for(j=0;j<p;j++)
					if(student[j].English>90){
						printf("�U%-6s    �U%-6d    �U%-6.1f  �U",student[j].name,student[j].ID,student[j].Chinese);
						printf("  %-6.1f  �U%-6.1f  �U%-6.1f  �U%-6.1f  �U\n",
							student[j].Math,student[j].English,student[j].sum,student[j].average);
					}
					puts("�^�T�T�T�T�T�m�T�T�T�T�T�m�T�T�T�T�T�m�T�T�T�T�T�m�T�T�T�T�T�m�T�T�T�T�T�m�T�T�T�T�T�a");
					break;
			case 4:
					puts("�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[");
					puts("�U          ѧ          ��          ��          Ϣ          �          ��          �U");
					puts("�d�T�T�T�T�T�j�T�T�T�T�T�j�T�T�T�T�T�j�T�T�T�T�T�j�T�T�T�T�T�j�T�T�T�T�T�j�T�T�T�T�T�g");
					puts("�U  ��  ��      ѧ  ��      ��  ��      ��  ѧ     Ӣ  ��      ��  ��     ƽ �� �� ");
					puts("�d�T�T�T�T�T�p�T�T�T�T�T�p�T�T�T�T�T�p�T�T�T�T�T�p�T�T�T�T�T�p�T�T�T�T�T�p�T�T�T�T�T�g");
					for(j=0;j<p;j++){
						printf("�U%-6s    �U%-6d    �U%-6.1f  �U",student[j].name,student[j].ID,student[j].Chinese);
						printf("  %-6.1f  �U%-6.1f  �U%-6.1f  �U%-6.1f  �U\n",
							student[j].Math,student[j].English,student[j].sum,student[j].average);
					}
					puts("�^�T�T�T�T�T�m�T�T�T�T�T�m�T�T�T�T�T�m�T�T�T�T�T�m�T�T�T�T�T�m�T�T�T�T�T�m�T�T�T�T�T�a");
					break;
            case 5:
					for(j=0;j<p;j++)
	 				{
	 					if(student[j].Chinese>60)x++;
	 				}   //���ļ�������
	 				printf("x = %d ",x);
					for(j=0;j<p;j++)
					{
	 					if(student[j].Chinese>60)y++;
					}   //��ѧ��������
					printf("y = %d ",y);
					for(j=0;j<p;j++)
					{
						if(student[j].Chinese>60)z++;
					}	//Ӣ�Ｐ������
					printf("z = %d ",z);
					c = (float)x/p;
					m = (float)y/p;
					e = (float)z/p;
					printf("\n�ð�����¼ȡ��Ϊ��%0.2f  ��ѧ¼ȡ��Ϊ��%0.2f  Ӣ��¼ȡ��Ϊ��%0.2f\n",c,m,e);
					break;
		}
	puts("��������������˵�...");
	getch();
}
void Print()
{
	int j;
	printf("��ȫ��ѧ����Ϣ���£�\n");
	puts(" = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =  ");
	puts("�U          ѧ          ��          ��          Ϣ          �          ��          �U");
	puts("�d= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = �g");
	puts("�U  ��  ��   ѧ  ��    ��  ��    ��  ѧ   Ӣ  ��    ��  ��   ƽ �� ��   ѧ��	    ");
		for(j=0;j<p;j++){
 	//printf("�U%-10s   %10d      %-6.1f    %-6.1f    %-6.1f     %-6.1f   %-6.1f  \n"
//	 ,student[j].name,student[j].ID,student[j].Chinese),student[j].Math,student[j].English,student[j].sum,student[j].average);
		printf("�U %5s    %6d    %6.1f\t",student[j].name,student[j].ID,student[j].Chinese);
		printf("%   6.1f    %6.1f    %6.1f   %6.1f    %d\n",
							student[j].Math,student[j].English,student[j].sum,student[j].average,student[j].xuefen);
	}
}

