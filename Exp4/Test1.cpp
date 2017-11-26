#include <stack>
#include <stdlib.h>
using namespace std;
stack<int> OVS;
stack<char> OPTR;

char list[7][7] = {//{+-*/()#}
        { '>','>','<','<','<','>','>' },
        { '>','>','<','<','<','>','>' },
        { '>','>','>','>','<','>','>' },
        { '>','>','>','>','<','>','>' },
        { '<','<','<','<','<','>','>' },
        { '>','>','>','>','>','=','>' },
        { '<','<','<','<','<','<','=' },
};
char Compare(char op1, char op2)
{
    int i, j;
    switch (op1)
    {
        case '+':i = 0; break;
        case '-':i = 1; break;
        case '*':i = 2; break;
        case '/':i = 3; break;
        case '(':i = 4; break;
        case ')':i = 5; break;
        case '#':i = 6; break;
    }
    switch (op2)
    {
        case '+':j = 0; break;
        case '-':j = 1; break;
        case '*':j = 2; break;
        case '/':j = 3; break;
        case '(':j = 4; break;
        case ')':j = 5; break;
        case '#':j = 6; break;
    }
    return list[i][j];
}
int Execute(int a, char op, int b)
{
    switch(op)
    {
        case '+':return a+b;
        case '-':return a-b;
        case '*':return a*b;
        case '/':return a/b;
    }
}

char getNext(int *flag){//得到一个整形数字
    char ch;
    int *n;
    n=(int *)malloc(sizeof(int));
    *n=0;
    if(isdigit(ch=getchar())==1){//读取了5
        do{
           *n=(*n)*10+(ch-'0');
            ch=getchar();
        }while(isdigit(ch)==1);
        *flag=*n;
        ungetc(ch,stdin);
    } else{
        return ch;
    }
}

int main()//#56+78#
{
    char ch, topsign, op;
    int a, b,result;
    int flag;//=56
    OPTR.push('#');
    printf("input the number:(Ending with '#')");
    getchar();//读取#
    //ch=getNext(&flag);
    ch=getchar();
    topsign=OPTR.top();
    while (ch != '#'||topsign!='#')
    {
        if (isdigit(ch) == 1)//
        {
            OVS.push(ch-'0');//
            ch = getchar();//

        }
        else
        {
            switch (Compare(topsign,ch))
            {
                case '<':
                {
                    OPTR.push(ch);
                    ch = getchar();
                    break;
                }
                case '>':
                {
                    if((ch==')')&&(topsign=='(')){
                        OPTR.pop();
                        ch=getchar();
                    }else{
                        op=OPTR.top();
                        OPTR.pop();
                        b=OVS.top();
                        OVS.pop();
                        a=OVS.top();
                        OVS.pop();
                        result = Execute(a, op, b);
                        OVS.push(result);
                        break;
                    }
                }
            }
        }
        topsign=OPTR.top();
    }
    result= OVS.top();
    printf("%u",result);
    return 0;
}
