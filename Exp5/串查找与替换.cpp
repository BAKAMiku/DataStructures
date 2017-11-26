#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SOURCEFILE "source.data"
#define MaxSize 100000
char inpaper[MaxSize];
char outpaper[MaxSize];
char t1[MaxSize]; //查找串 
char t2[MaxSize]; //替换串 
int Getdata(char paper[]);
int Outputdata(int data[],int n);
int main()
{
	
	char *current;
	int i=0;
	int j=0;
	Getdata(inpaper);
	/*在此补充代码，实现文本的查找与替换*/	
}

int Getdata(char paper[])
{   
	FILE *fp;
    if ((fp = fopen(SOURCEFILE,"rb")) == NULL) /* 以读方式打开文本文件 */
	{
		printf("Failure to open score.txt!\n");
		return 0;//读数据失败 
	}
	int i=0	; 
	while(!feof(fp))
	{
	   fscanf(fp,"%c",&paper[i]);
	   i++; 
	} 
	fclose(fp); 
    return 1;  //成功读数据                          
}

int Outputdata(int paper[])
{
	FILE *fp;
	if ((fp = fopen("out.data","wb")) == NULL) /* 以写方式打开文本文件 */
	{
		printf("Failure to open score.txt!\n");
		return 0;//写数据失败 
	}
	for(int i=0;paper[i]!='\n';i++)  
        fprintf(fp,"%c",paper[i]);
	fclose(fp);
	return 1;
	
}


