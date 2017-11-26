#include<stdio.h>
#include <iostream>
#include <string>
#include<stdlib.h>
#include<string.h>
using namespace std;

#define SOURCEFILE "inpaper.data"
#define MaxSize 100000
#define MaxLength 10
char inpaper[MaxSize];
char outpaper[MaxSize];
char t1[MaxSize]; //查找串
char t2[MaxSize]; //替换串
class inpaper;

int Getdata(char paper[]);
int Outputdata(int data[],int n);

int main()
{
    char *current;
    int i=0;
    int j=0;

    char replace[MaxLength],replace_to[MaxLength];
    int Location;
    char *ptr;
    int sizer,sizert;
    Getdata(inpaper);

    cout<<"输入替换的字符："<<endl;
    cin>>replace;
    cout<<"输入被替换的字符："<<endl;
    cin>>replace_to;
    sizer=strlen(replace);//得到替换字符的长度
    sizert=strlen(replace_to);// 得到被替换字符的长度

    while(strstr(inpaper,replace_to)!=NULL){
        ptr=strstr(inpaper,replace_to);//得到被替换字符的位置指针
        Location=ptr-inpaper;//得到被替换字符的数字位置
        for(int i=strlen(inpaper)-1;i>=Location;i--){
            inpaper[i+(sizer-sizert)]=inpaper[i];
        }
        for(int j=Location, k=0;j<=Location+sizer,k<=sizer-1;j++,k++) {
            inpaper[j] = replace[k];
        }
    }
    cout<<"替换后的文本是：\n"<<inpaper;


    /*问题：
     * 老师给的文本有问题，读取""是乱码
     * 我觉得应该是编码的问题
     * 故将老师所给文件的""改为英文字符""
     */

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


