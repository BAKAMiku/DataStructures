#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SOURCEFILE "source.data"
#define MaxSize 100000
char inpaper[MaxSize];
char outpaper[MaxSize];
char t1[MaxSize]; //���Ҵ� 
char t2[MaxSize]; //�滻�� 
int Getdata(char paper[]);
int Outputdata(int data[],int n);
int main()
{
	
	char *current;
	int i=0;
	int j=0;
	Getdata(inpaper);
	/*�ڴ˲�����룬ʵ���ı��Ĳ������滻*/	
}

int Getdata(char paper[])
{   
	FILE *fp;
    if ((fp = fopen(SOURCEFILE,"rb")) == NULL) /* �Զ���ʽ���ı��ļ� */
	{
		printf("Failure to open score.txt!\n");
		return 0;//������ʧ�� 
	}
	int i=0	; 
	while(!feof(fp))
	{
	   fscanf(fp,"%c",&paper[i]);
	   i++; 
	} 
	fclose(fp); 
    return 1;  //�ɹ�������                          
}

int Outputdata(int paper[])
{
	FILE *fp;
	if ((fp = fopen("out.data","wb")) == NULL) /* ��д��ʽ���ı��ļ� */
	{
		printf("Failure to open score.txt!\n");
		return 0;//д����ʧ�� 
	}
	for(int i=0;paper[i]!='\n';i++)  
        fprintf(fp,"%c",paper[i]);
	fclose(fp);
	return 1;
	
}


