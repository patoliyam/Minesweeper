#include <bits/stdc++.h>
using namespace std;
void center (char** A,int **B, int R, int C, int r, int c)
{
    //sum of neighbours=(i)0 then A[R][C]=' ' followed by the neighbor check; (ii) !=0 then A[R][C]=sum, and exit.
    if(B[R][C]==1){
        return;
    }
    int cnt=0;

    for(int i=R-1;i<R+2;i++)
    {
        for(int j=C-1;j<C+2;j++)
        {   if(j<0||i<0||j>=c||i>=r)
                continue;
            if(i==R&&j==C)
                continue;
            cnt+=B[i][j];
        }
    }

    if(cnt==0)
    {   A[R][C]=' ';
        for(int i=R-1;i<R+2;i++)
        {
            for (int j = C-1; j<C+2; j++)
            {   if(j<0||i<0||j>=c||i>=r)
                    continue;
                if(i==R&&j==C)
                    continue;
                if(A[i][j]=='*'||A[i][j]=='@')
                    center(A,B,i,j,r,c);
            }
        }
    }

    else
    {
        A[R][C]= cnt+'0';
    }
}

void printB(int**B,int r,int c)
{int i,j;
    for(i=0;i<r;i++)
    {   cout<<"\t";
        for(j=0;j<c;j++)
        {
            cout<<B[i][j];
        }
        cout<<endl;
    }
}

int main()
{   int flag1=0, flag2=0;
    int r, c, b;
    cout << "Number of rows : ";
    cin >> r;
    cout << "Number of columns : ";
    cin >> c;
    cout << "Number of bombs : ";
    cin >> b;
    srand(time(NULL));
    set<int> random;
    set<int>::iterator it = random.begin();
    while (random.size() < b)
    {
        int t = rand() % ((r-1) * (c-1) );
        random.insert(t);
    }
   /*
    To print site of bombs:
    for (set<int>::iterator it = random.begin(); it != random.end(); it++)
    {
        cout << *it << endl;
    }
    */
    int i,j;

    int **B= new int*[r];

    for(int i= 0; i<r; i++)
    {
        B[i] = new int[c];
        for(int j=0;j<c;j++){
            B[i][j] = 0;
        }
    }
    for (it = random.begin(); it != random.end(); it++)
    {
        B[(*it)/c][(*it)-((*it)/c)*c]=1;
    }

    char **A;
    A=new char*[r];
    for(i=0;i<r;i++)
    {
        A[i]=new char[c];
        for(j=0;j<c;j++)
        {
            A[i][j]='*';
        }
    }
    while(flag1==0 && flag2==0)
    {
        int count = 0;
        for (i = 0; i < r; i++)
        {
            for (j = 0; j < c; j++)
            {
                if (A[i][j] == '*'||A[i][j]=='@')
                {
                    count++;
                }
            }

        }
        
        if (count == b)
        {
            printB(B,r,c);
            cout << "CONGRATULATIONS!! You won the game.\n";  // if number of *s left =b then print that u hasve won the game.
            flag1=1;

        }
        else
        {   cout<<"   \t";
            for(j=0;j<=c;j++)
            {
                printf("%3d",j);
            }
            cout<<"\n";
            for (i = 0; i < r; i++)
            {   cout<<"\t";
                printf("%3d",i+1);
                cout<<"\t";
                for (j = 0; j < c; j++)
                {
                    cout <<" "<<A[i][j]<<" ";
                }
                cout << endl;
            }


            int x, y;
            cout<<"Press 1 for opening, 2 for putting flag, 3 for removing flag  \nEnter row and column :\n ";
            int z;
            cin>>z;
            cin >> x;
            cin>>y;

            if(z==2)
            {   if(A[x-1][y-1]=='@'||A[x-1][y-1]=='*')
                    A[x-1][y-1]='@';
                else
                    cout<<"Wrong entry\n";
            }
                else if(z==3)
            {
                if(A[x-1][y-1]=='@')
                    A[x-1][y-1]='*';
                else
                    cout<<"Wrong Entry\n";
            }
            else
            {
                if (B[x - 1][y - 1] == 1) {
                    printB(B, r, c);
                    cout << "\n Game Over!\n \n";//Now print B matrix with highlighting the wrong one.
                    flag2 = 1;
                }
                else {
                    center(A, B, x - 1, y - 1, r, c);
                }
            }
        }
    }
    return 0;
}
