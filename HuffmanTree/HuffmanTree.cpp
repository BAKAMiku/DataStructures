/*create by BakaMiku
//_DEBUG
 1.bmp  1036918b 1MB
 2.bmp
 3.png  13535b  16KB
 4.docx 17469b  20KB
 5.txt  14b 4KB
 6.m4v  6309403b   7.4MB
//DEBUG*/
#include <cstdlib>
#include <iostream>
#include <queue>
using namespace std;
struct Huffman_Tree{//链表实现储存哈夫曼树
    unsigned char ch='0';
    long value=0;//权值：出现的次数
    int parent=-1;//双亲节点编号
    int Lchild=-1;
    int Rchild=-1;
    char code[256];
};
void _DEBUG(Huffman_Tree *huffman);
void count_file(Huffman_Tree *huffman,char filename[]);
int backNot0(Huffman_Tree *ht);
void selcet(Huffman_Tree *huffman,int p,int *x1,int *x2);
void createHuffmanTree(Huffman_Tree *ht,int count);
void createHuffmanCode(Huffman_Tree *ht,int count);
char Str2byte(const char *pBinStr);
char Byte2str(char pCharStr,char com[]);
void filepress();
void fileunpress();

void count_file(Huffman_Tree *huffman,char filename[]){//统计源文件各字节出现次数
    FILE *fp;
    unsigned char ch;
    printf("Input the file name:");
    scanf("%s",filename);
    if((fp=fopen(filename,"rb"))== nullptr){
        printf("Open the file incorrect!");
        exit(0);
    }
    for(;;){
        int i=fread(&ch, sizeof(unsigned char),1,fp);
        if(i==0) break;
        huffman[ch].ch=ch;//传递字符串给结构体的ch
        huffman[ch].value++;
    }
    fclose(fp);
}

int backNot0(Huffman_Tree *ht){//统计出现字符的个数，即为生成哈夫曼树的叶子节点个数
    int count=0;
    for(int i=0;i<256;i++){
        if(ht[i].value!=0)  count++;
    }
    return count;
}

void selcet(Huffman_Tree *huffman,int p,int *x1,int *x2){//选择两个最小值
    long m1,m2;
    m1=m2=INT_MAX;
    *x1=*x2=0;
    for(int k=0;k<=p;k++){
        if((huffman[k].value<m1)&&(huffman[k].value>=1)&&(huffman[k].parent==-1)){
            m2=m1;
            *x2=*x1;
            m1=huffman[k].value;
            *x1=k;
        }
        else if((huffman[k].value<m2)&&(huffman[k].value>=1)&&(huffman[k].parent==-1)){
            m2=huffman[k].value;
            *x2=k;
        }
    }
}

void createHuffmanTree(Huffman_Tree *ht,int count){//生成哈夫曼树
    int s1,s2;
    for(int i=256;i<=256+(count-2);i++){
        selcet(ht,i-1,&s1,&s2);
        ht[i].value=ht[s1].value+ht[s2].value;
        ht[s1].parent=ht[s2].parent=i;
        ht[i].Lchild=s1;
        ht[i].Rchild=s2;
    }
}

void createHuffmanCode(Huffman_Tree *ht,int count){//生成哈夫曼编码
    int p;
    int c=0;
    int start;
    char cd[count];
    cd[count-1]='\0';
    for(int i=0;i<=255;i++){
        if(ht[i].value!=0){
            start=count-1;
            c=i;
            p=ht[i].parent;
            while(p!=-1){
              --start;
                if(ht[p].Lchild==c){
                    cd[start]='1';
                } else{
                    cd[start]='0';
                }
                c=p;
                p=ht[p].parent;
            }
            strcpy(ht[i].code,&cd[start]);
        }
    }
}

void _DEBUG(Huffman_Tree *huffman,long total,long count){//Debug function
    printf("编号 权值            左   右 双亲节点  哈夫曼编码\n");
    for (int i = 0; i <= 511; i++) {
        if (huffman[i].value != 0) {
            printf("%d\t%-12ld\t%d\t%d\t%d\t\t%s\n", i,
 huffman[i].value, huffman[i].Lchild,huffman[i].Rchild, huffman[i].parent, huffman[i].code);
        } else {}
    }
    cout<<total<<" "<<count;
}

char Str2byte(const char *pBinStr){
    char b=0x00;
    for(int i=0;i<8;i++){
        b=b<<1;
        if(pBinStr[i]=='1'){
            b=b|0x01;
        }
    }
    return b;
}

char Byte2str(char pCharStr,char com[]){
    char b=0x80;
    unsigned int t;
    for(int i=0;i<8;i++){
        t=(pCharStr)&(b);
        if(t>1){
            com[i]='1';
        } else{
            com[i]='0';
        }
        pCharStr=pCharStr<<1;
    }
    return 0;
}
void filepress() {
    char filename[100];
    int count;//出现的字符个数
    Huffman_Tree huffman[512];//huffman[0]~huffman[511]//huffman[0]~huffuman[255]

    count_file(huffman,filename);//得到每个字符出现的次数，并且将频率存入结构体
    count = backNot0(huffman);//统计叶子节点个数
    createHuffmanTree(huffman, count);//生成哈夫曼树
    createHuffmanCode(huffman, count);//生成哈夫曼编码


    FILE *fp, *wfp;
    unsigned char str;
    queue<char> queBuffer;
    fp = fopen(filename, "rb");
    //获取文件名及后缀
    char name[50];
    char huf[5]=".huf";
    strcpy(name,filename);
    strcat(name,huf);
    for(;;){
        int swi=fread(&str, sizeof(unsigned char),1,fp);
        if(swi==0)  break;
        for(int i=0;i<strlen(huffman[str].code);i++){
            queBuffer.push((huffman[str].code)[i]);
        }
    }

    long total=queBuffer.size();
    wfp = fopen(name, "wb");
    //写文件头部
    //文件名+后缀名
    //已在文件名中实现

    //_DEBUG(huffman,total,count);

    //数据的总数
    fwrite(&total, sizeof(long),1,wfp);
    fwrite(&count, sizeof(int),1,wfp);
    //字节编号+出现频次
    for(int x=0;x<=255;x++){
        if(huffman[x].value!=0){
            fwrite(&huffman[x].ch, sizeof(unsigned char),1,wfp);
            fwrite(&huffman[x].value, sizeof(long),1,wfp);
        }
    }
    //

    //写入压缩后的哈夫曼编码
    int num=8-(queBuffer.size()%8);//补0至8的倍数
    if(num!=8){
        for(int t=0;t<=num-1;t++){
            queBuffer.push('0');
        }
    } else{
        goto Next;
    }

    Next:do{
        char pstr[8];
        char res[1];
        for(int p=0;p<=7;p++){

            pstr[p]=queBuffer.front();
            queBuffer.pop();
        }
        res[0]=Str2byte(pstr);
        fwrite(res, sizeof(char),1,wfp);
    }while (!queBuffer.empty());

    fclose(fp);
    fclose(wfp);
}

void fileunpress(){//解压文件
    FILE *unf;
    char unpfilename[15];//还原后的文件名
    char unpfilen[15];//全称（包含.huf）
    long total;//记录总的字节个数
    int count;//记录节点个数

    Huffman_Tree unhuffman[512];

    printf("Input the unpress filename:");
    scanf("%s",unpfilen);
    if((unf=fopen(unpfilen,"rb"))== nullptr){
        printf("Open the unpressfile incorrect!");
        exit(0);
    }

    fread(&total, sizeof(long),1,unf);//读取头部
    fread(&count, sizeof(int),1,unf);

    unsigned char t;
    long num;
    for(int i=0;i<count;i++){
        fread(&t, sizeof(unsigned char),1,unf);
        int x=(int)t;
        fread(&num, sizeof(long),1,unf);
        unhuffman[x].value=num;
        unhuffman[x].ch=t;
    }

    //count = backNot0(unhuffman);
    //读取正文
    char rbyte;
    queue<char> unBuffer;

    for(;;){
        int swi=fread(&rbyte, sizeof(char), 1, unf);
        if(swi==0) break;
        char com[8];
        Byte2str(rbyte, com);
        for (int i = 0; i < 8; i++) {
            unBuffer.push(com[i]);
        }
    }
    fclose(unf);


    createHuffmanTree(unhuffman,count);
    createHuffmanCode(unhuffman,count);
    //_DEBUG(unhuffman,total,count);
    //跟节点必然是unhuffman[256+(count-1)-1]
    //FILE *uputfile=fopen(unpfilename,"w");
    FILE *uputfile=fopen("out.txt","wb");

    int con=1;
    while(con<=total){
        int root=256+(count-1)-1;
        while(unhuffman[root].Lchild!=-1){
            char flag=unBuffer.front();
            unBuffer.pop();
            con++;
            if(flag=='1'){
                root=unhuffman[root].Lchild;
            } else{
                root=unhuffman[root].Rchild;
            }
        }
        fwrite(&unhuffman[root].ch, sizeof(unsigned char),1,uputfile);
    }
}

int main() {
    printf("压缩/解压小工具\n");
    printf("压缩文件请按1,解压文件请按2,推出请按0\n");
    int inputNum=0;
    scanf("%d",&inputNum);
    if(inputNum==1){
        filepress();//压缩文件
    } else if(inputNum==2){
        fileunpress();//解压文件
    } else{
        exit(0);
    }
}











