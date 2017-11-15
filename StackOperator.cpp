#include <stack>
using namespace std;

stack<int> OVS;
stack<char> OPTR;

int IsNum(char x)
{
    if (x>='0'&&x<='9')
        return 1;
    else
        return 0;
}

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

char Execute(char a, char op, char b)
{
    switch(op)
    {
        case '+':return (char)((int)a + (int)b);
        case '-':return (char)((int)a - (int)b);
        case '*':return (char)((int)a*(int)b);
        case '/':return (char)((int)a / (int)b);
    }
}

int main()
{
    char ch, topsign, op;
    char a, b,result;
    OPTR.push('#');
    printf("input the number:(Ending with '#')");
    ch = getchar();
    ch = getchar();//
    topsign=OPTR.top();
    while (ch != '#'||topsign!='#')
    {
        if (IsNum(ch) == 1)//
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
                        OVS.push((int)result);
                        break;
                    }
                }
            }
        }
        topsign=OPTR.top();
    }
    result= OVS.top();
    printf("%u", (int)result);
    return 0;
}
