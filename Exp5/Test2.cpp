#include<stdio.h>
#include<fstream>
#include <vector>
#include <math.h>
using namespace std;

#define SOURCEFILE "source.data"
#define MaxSize 100000
char inpaper[MaxSize];
int Getdata(char paper[]);
int Outputdata(vector<int> &str);

void combineNum(vector<int> &array,vector<int> &str){//转换函数
    int sum=0,j=0;
    for(int i=0;i<=7;i++){
        j=array[i]*(pow(2,8-(i+1)));//二进制转十进制
        sum+=j;
    }
    str.push_back(sum);//将所得值添加至sum
    array.clear();//清空array
}

int main()
{
    Getdata(inpaper);//98488
    /*在此补充代码，实现文本的查找与替换*/

    vector<int> array;
    vector<int> str;
    for(int i=0;i<=strlen(inpaper)-1;i++){
        array.push_back(inpaper[i]-'0');//向array输入01字符
        if(array.size()==8) {//每8个单位为一组
            combineNum(array, str);//转换函数
        }
    }
    Outputdata(str);
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

int Outputdata(vector<int> &str)
{
    FILE *fp;
    if ((fp = fopen("out.data","wb")) == NULL) /* 以写方式打开文本文件 */
    {
        printf("Failure to open score.txt!\n");
        return 0;//写数据失败
    }
    for(int i=0;i<=str.size();i++)
        fprintf(fp,"%c",str[i]);
    fclose(fp);
    return 1;
}

