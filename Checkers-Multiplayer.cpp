#include<iostream>
#include<graphics.h>
#include<string>
#include<stdlib.h>
#include<cmath>
#include<windows.h>
#include<fstream>
using namespace std;
ifstream o_save("save.save");
ofstream save("save.save", ios::app);
int men[8][8],xx=-1,yy=-1,numRed=12,numWhite=12;
bool en=false,mouse=1,bot=0;
void draw_circle(int x,int y,int type)//x,y: 1-8 ; type: 1-white, 2-white_king, (-1)-red, (-2)-red_king
{

    if (type!=0)
    {
        setcolor(2);
        if(type>0)setfillstyle(1,7);
        if(type<0)setfillstyle(1,4);
        fillellipse((y-1)*60+50+10,(x-1)*60+50+10,26,26);
        if(abs(type)==2)
        {
            if(type>0){setcolor(4);setfillstyle(1,4);}
            if(type<0){setcolor(7);setfillstyle(1,7);}
            fillellipse((y-1)*60+50+10,(x-1)*60+50+10,5,5);
        }
    }
}
void markman(int y,int x)
{
     setcolor(14);
     circle(y*60+50+10,(x-1)*60+50+10,26);
     circle(y*60+50+10,(x-1)*60+50+10,25);
}
void draw_board()
{
    for(int i=1;i<=8;i++)
    {
        for(int j=1;j<=8;j++)
        {
                if((i%2)==(j%2))
                {
                            setfillstyle(1,15);
                }
                else
                {
                            setfillstyle(1,2);
                }

                bar((i-1)*60+20+10,(j-1)*60+20+10,i*60+20+10,j*60+20+10);

        }
    }
    for(int i=1;i<=8;i++)
    for(int j=1;j<=8;j++)
    {
            draw_circle(i,j,men[i-1][j-1]);
    }

    setcolor(15);
    settextstyle(1,0,1);

    //right column

    moveto(10-5,50-5);
    outtext("1");
    moveto(10-5,110-5);
    outtext("2");
    moveto(10-5,170-5);
    outtext("3");
    moveto(10-5,230-5);
    outtext("4");
    moveto(10-5,290-5);
    outtext("5");
    moveto(10-5,350-5);
    outtext("6");
    moveto(10-5,410-5);
    outtext("7");
    moveto(10-5,470-5);
    outtext("8");

    //top row

    moveto(50-5,4);
    outtext("A");
    moveto(110-5,4);
    outtext("B");
    moveto(170-5,4);
    outtext("C");
    moveto(230-5,4);
    outtext("D");
    moveto(290-5,4);
    outtext("E");
    moveto(350-5,4);
    outtext("F");
    moveto(410-5,4);
    outtext("G");
    moveto(470-5,4);
    outtext("H");

    //left column

    moveto(510+5,50-5);
    outtext("1");
    moveto(510+5,110-5);
    outtext("2");
    moveto(510+5,170-5);
    outtext("3");
    moveto(510+5,230-5);
    outtext("4");
    moveto(510+5,290-5);
    outtext("5");
    moveto(510+5,350-5);
    outtext("6");
    moveto(510+5,410-5);
    outtext("7");
    moveto(510+5,470-5);
    outtext("8");

    //bottom row

    moveto(50-5,510+5);
    outtext("A");
    moveto(110-5,510+5);
    outtext("B");
    moveto(170-5,510+5);
    outtext("C");
    moveto(230-5,510+5);
    outtext("D");
    moveto(290-5,510+5);
    outtext("E");
    moveto(350-5,510+5);
    outtext("F");
    moveto(410-5,510+5);
    outtext("G");
    moveto(470-5,510+5);
    outtext("H");

}
void spawn ()
{
    for (int i=1;i<4;i++)
    {
        for (int j=1;j<9;j++)
        {
            if ((i%2)!=(j%2))
            {
                         men[i-1][j-1]=-1;
            }
        }
    }
    for (int i=6;i<9;i++)
    {
        for (int j=1;j<9;j++)
        {
            if ((i%2)!=(j%2))
            {
                         men[i-1][j-1]=1;
            }
        }
    }
}
void crown()
{
    for (int i=0;i<8;i++) if (men[0][i]==1) men[0][i]=2;
    for (int i=0;i<8;i++) if (men[7][i]==-1) men[7][i]=-2;
}
bool check_capture_man(int x,int y)
{
     if(men[y][x]>0)
     {
            if(men[y][x]==1)
            {
                    if(y>1)
                    {
                            if(x>1)
                            {
                                    if(men[y-1][x-1]<0 && men[y-2][x-2]==0)return true;
                            }
                            if(x<6)
                            {
                                    if(men[y-1][x+1]<0 && men[y-2][x+2]==0)return true;
                            }
                    }
            }
            if(men[y][x]==2)
            {
                    if(y>1)
                    {
                            if(x>1)
                            {
                                    if(men[y-1][x-1]<0 && men[y-2][x-2]==0)return true;
                            }
                            if(x<6)
                            {
                                    if(men[y-1][x+1]<0 && men[y-2][x+2]==0)return true;
                            }
                    }
                    if(y<6)
                    {
                            if(x>1)
                            {
                                    if(men[y+1][x-1]<0 && men[y+2][x-2]==0)return true;
                            }
                            if(x<6)
                            {
                                    if(men[y+1][x+1]<0 && men[y+2][x+2]==0)return true;
                            }
                    }
            }
     }
     if(men[y][x]<0)
     {
            if(men[y][x]==-1)
            {
                    if(y<6)
                    {
                            if(x>1)
                            {
                                    if(men[y+1][x-1]>0 && men[y+2][x-2]==0)return true;
                            }
                            if(x<6)
                            {
                                    if(men[y+1][x+1]>0 && men[y+2][x+2]==0)return true;
                            }
                    }
            }
            if(men[y][x]==-2)
            {
                    if(y<6)
                    {
                            if(x>1)
                            {
                                    if(men[y+1][x-1]>0 && men[y+2][x-2]==0)return true;
                            }
                            if(x<6)
                            {
                                    if(men[y+1][x+1]>0 && men[y+2][x+2]==0)return true;
                            }
                    }
                    if(y>1)
                    {
                            if(x>1)
                            {
                                    if(men[y-1][x-1]>0 && men[y-2][x-2]==0)return true;
                            }
                            if(x<6)
                            {
                                    if(men[y-1][x+1]>0 && men[y-2][x+2]==0)return true;
                            }
                    }
            }
     }
     return false;
}
bool check_move_man(int x,int y)
{
     if(men[y][x]>0)
     {
            if(men[y][x]==1)
            {
                    if(y>0)
                    {
                            if(x>0)
                            {
                                    if(men[y-1][x-1]==0)return true;
                            }
                            if(x<7)
                            {
                                    if(men[y-1][x+1]==0)return true;
                            }
                    }
            }
            if(men[y][x]==2)
            {
                    if(y>0)
                    {
                            if(x>0)
                            {
                                    if(men[y-1][x-1]==0)return true;
                            }
                            if(x<7)
                            {
                                    if(men[y-1][x+1]==0)return true;
                            }
                    }
                    if(y<7)
                    {
                            if(x>0)
                            {
                                    if(men[y+1][x-1]==0)return true;
                            }
                            if(x<7)
                            {
                                    if(men[y+1][x+1]==0)return true;
                            }
                    }
            }
     }
     if(men[y][x]<0)
     {
            if(men[y][x]==-1)
            {
                    if(y<7)
                    {
                            if(x>0)
                            {
                                    if(men[y+1][x-1]==0)return true;
                            }
                            if(x<7)
                            {
                                    if(men[y+1][x+1]==0)return true;
                            }
                    }
            }
            if(men[y][x]==-2)
            {
                    if(y<7)
                    {
                            if(x>0)
                            {
                                    if(men[y+1][x-1]==0)return true;
                            }
                            if(x<7)
                            {
                                    if(men[y+1][x+1]==0)return true;
                            }
                    }
                    if(y>0)
                    {
                            if(x>0)
                            {
                                    if(men[y-1][x-1]==0)return true;
                            }
                            if(x<7)
                            {
                                    if(men[y-1][x+1]==0)return true;
                            }
                    }
            }
     }
     return false;
}
bool check_capture_king_man(int x,int y)
{
     if(men[y][x]>0)
     {
            if(men[y][x]==1)
            {
                    if(y>1)
                    {
                            if(x>1)
                            {
                                    if(men[y-1][x-1]==-2 && men[y-2][x-2]==0)return true;
                            }
                            if(x<6)
                            {
                                    if(men[y-1][x+1]==-2 && men[y-2][x+2]==0)return true;
                            }
                    }
            }
            if(men[y][x]==2)
            {
                    if(y>1)
                    {
                            if(x>1)
                            {
                                    if(men[y-1][x-1]==-2 && men[y-2][x-2]==0)return true;
                            }
                            if(x<6)
                            {
                                    if(men[y-1][x+1]==-2 && men[y-2][x+2]==0)return true;
                            }
                    }
                    if(y<6)
                    {
                            if(x>1)
                            {
                                    if(men[y+1][x-1]==-2 && men[y+2][x-2]==0)return true;
                            }
                            if(x<6)
                            {
                                    if(men[y+1][x+1]==-2 && men[y+2][x+2]==0)return true;
                            }
                    }
            }
     }
     if(men[y][x]<0)
     {
            if(men[y][x]==-1)
            {
                    if(y<6)
                    {
                            if(x>1)
                            {
                                    if(men[y+1][x-1]==2 && men[y+2][x-2]==0)return true;
                            }
                            if(x<6)
                            {
                                    if(men[y+1][x+1]==2 && men[y+2][x+2]==0)return true;
                            }
                    }
            }
            if(men[y][x]==-2)
            {
                    if(y<6)
                    {
                            if(x>1)
                            {
                                    if(men[y+1][x-1]==2 && men[y+2][x-2]==0)return true;
                            }
                            if(x<6)
                            {
                                    if(men[y+1][x+1]==2 && men[y+2][x+2]==0)return true;
                            }
                    }
                    if(y>1)
                    {
                            if(x>1)
                            {
                                    if(men[y-1][x-1]==2 && men[y-2][x-2]==0)return true;
                            }
                            if(x<6)
                            {
                                    if(men[y-1][x+1]==2 && men[y-2][x+2]==0)return true;
                            }
                    }
            }
     }
     return false;
}
bool check_capture(int type)//type: 1-white,(-1)-red
{
     for(int i=0;i<8;i++)
     for(int j=0;j<8;j++)
     {
             if(type>0&&men[j][i]>0)if(check_capture_man(i,j)) return true;
             if(type<0&&men[j][i]<0)if(check_capture_man(i,j)) return true;
     }
     return false;
}
bool check_move(int type)
{
     for(int i=0;i<8;i++)
     for(int j=0;j<8;j++)
     {
             if(type>0&&men[j][i]>0)if(check_move_man(i,j)) return true;
             if(type<0&&men[j][i]<0)if(check_move_man(i,j)) return true;
     }
     return false;
}
bool check_capture_king(int type)//type: 1-white,(-1)-red
{
     for(int i=0;i<8;i++)
     for(int j=0;j<8;j++)
     {
             if(type>0&&men[j][i]>0)if(check_capture_king_man(i,j)) return true;
             if(type<0&&men[j][i]<0)if(check_capture_king_man(i,j)) return true;
     }
     return false;
}
bool possible_turn(int type)
{
    if (check_move(type)==true || check_capture(type)==true) return true;
    return false;
}
int winner()//returns 1 when White is winner and (-1) when Red is winner
{
    if(numRed==0 || possible_turn(-1)==0) {ofstream d_save("save.save");return 1;}
    if(numWhite==0 || possible_turn(1)==0) {ofstream d_save("save.save");return -1;}
    return 0;
}
int turn(int type)
{
    int mx,my;
    char x1='A',x2='A';
    bool fff=1;
    int y1=-1,y2=-1;
    int ff=1;
    if(type<0){if(en)cout<<"Player 1"<<endl;else cout<<"Играч 1"<<endl;}
    if(type>0){if(en)cout<<"Player 2"<<endl;else cout<<"Играч 2"<<endl;}
    int index=-1;char ch;
    while(1)
    {
            if (mouse==1)
            {
                if (((GetKeyState(VK_LBUTTON) & 0x100) != 0) && fff==1)
                {
                    fff=0;
                }
                if (!((GetKeyState(VK_LBUTTON) & 0x100) != 0) && fff==0)
                {
                    fff=1;
                    mx=mousex();
                    my=mousey();
                    if (mx>=30 && my>=30 && mx<510 && my<510)
                    {
                        if (index==-1)
                        {
                            mx-=30;
                            my-=30;
                            x1=mx/60-1+1+'A';
                            y1=my/60+1;
                            cout<<x1<<" "<<y1;
                            index+=2;
                            markman(x1-'A',y1);
                        }
                        else
                        {
                            mx-=30;
                            my-=30;
                            x2=mx/60-1+1+'A';
                            y2=my/60+1;
                            cout<<" "<<x2<<" "<<y2<<endl;
                            markman(x2-'A',y2);
                            break;
                        }
                    }
                }
            }
            else
            {
                cin.get(ch);
                if(ch=='\n'&&index>=0)break;
                if(ch!=' '&&ch!='\n')
                {
                     index++;
                     if(index==0)x1=ch;
                     else
                     if(index==1)y1=ch-'0';
                     else
                     if(index==2)x2=ch;
                     else
                     if(index==3)y2=ch-'0';
                }
            }
    }
    if (x1>='a' && x1<='z') x1+='A'-'a';
    if (x2>='a' && x2<='z') x2+='A'-'a';
    if(type>0)
    {
        if(x1-'A'>=0 && x1-'A'<8 && y1-1>=0 && y1-1<8 && x2-'A'>=0 && x2-'A'<8 && y2-1>=0 && y2-1<8 && men[y1-1][x1-'A']==1 && abs(x1-x2)==1 && y2-y1==-1 && men[y2-1][x2-'A']==0 && check_capture(1)==0 && (xx==x1 && yy==y1)==(xx!=-1))
        {
                men[y1-1][x1-'A']=0;
                men[y2-1][x2-'A']=1;
                ff=0;
                save<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
        }
        if(x1-'A'>=0 && x1-'A'<8 && y1-1>=0 && y1-1<8 && x2-'A'>=0 && x2-'A'<8 && y2-1>=0 && y2-1<8 && men[y1-1][x1-'A']==2 && abs(x1-x2)==1 && abs(y2-y1)==1 && men[y2-1][x2-'A']==0 && check_capture(1)==0 && (xx==x1 && yy==y1)==(xx!=-1))
        {
                men[y1-1][x1-'A']=0;
                men[y2-1][x2-'A']=2;
                ff=0;
                save<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
        }
        if(x1-'A'>=0 && x1-'A'<8 && y1-1>=0 && y1-1<8 && x2-'A'>=0 && x2-'A'<8 && y2-1>=0 && y2-1<8 && men[y1-1][x1-'A']==1 && abs(x1-x2)==2 && y2-y1==-2 && men[y2-1][x2-'A']==0 && men[(y1+y2)/2-1][(x1-'A'+x2-'A')/2]<0 && (xx==x1 && yy==y1)==(xx!=-1))
        {
                men[y1-1][x1-'A']=0;
                men[(y1+y2)/2-1][(x1-'A'+x2-'A')/2]=0;
                men[y2-1][x2-'A']=1;
                numRed--;
                if (check_capture_man (x2-'A',y2-1)==1) {xx=x2;yy=y2;ff=2;}
                else ff=0;
                save<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
        }
        if(x1-'A'>=0 && x1-'A'<8 && y1-1>=0 && y1-1<8 && x2-'A'>=0 && x2-'A'<8 && y2-1>=0 && y2-1<8 && men[y1-1][x1-'A']==2 && abs(x1-x2)==2 && abs(y2-y1)==2 && men[y2-1][x2-'A']==0 && men[(y1+y2)/2-1][(x1-'A'+x2-'A')/2]<0 && (xx==x1 && yy==y1)==(xx!=-1))
        {
                men[y1-1][x1-'A']=0;
                men[(y1+y2)/2-1][(x1-'A'+x2-'A')/2]=0;
                men[y2-1][x2-'A']=2;
                numRed--;
                if (check_capture_man (x2-'A',y2-1)==1) {xx=x2;yy=y2;ff=2;}
                else ff=0;
                save<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
        }
    }
    if(type<0)
    {
        if(x1-'A'>=0 && x1-'A'<8 && y1-1>=0 && y1-1<8 && x2-'A'>=0 && x2-'A'<8 && y2-1>=0 && y2-1<8 && men[y1-1][x1-'A']==-1 && abs(x1-x2)==1 && y2-y1==1 && men[y2-1][x2-'A']==0 && check_capture(-1)==0 && (xx==x1 && yy==y1)==(xx!=-1))
        {
                men[y1-1][x1-'A']=0;
                men[y2-1][x2-'A']=-1;
                ff=0;
                save<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
        }
        if(x1-'A'>=0 && x1-'A'<8 && y1-1>=0 && y1-1<8 && x2-'A'>=0 && x2-'A'<8 && y2-1>=0 && y2-1<8 && men[y1-1][x1-'A']==-2 && abs(x1-x2)==1 && abs(y2-y1)==1 && men[y2-1][x2-'A']==0 && check_capture(-1)==0 && (xx==x1 && yy==y1)==(xx!=-1))
        {
                men[y1-1][x1-'A']=0;
                men[y2-1][x2-'A']=-2;
                ff=0;
                save<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
        }
        if(x1-'A'>=0 && x1-'A'<8 && y1-1>=0 && y1-1<8 && x2-'A'>=0 && x2-'A'<8 && y2-1>=0 && y2-1<8 && men[y1-1][x1-'A']==-1 && abs(x1-x2)==2 && y2-y1==2 && men[y2-1][x2-'A']==0 && men[(y1+y2)/2-1][(x1-'A'+x2-'A')/2]>0 && (xx==x1 && yy==y1)==(xx!=-1))
        {
                men[y1-1][x1-'A']=0;
                men[(y1+y2)/2-1][(x1-'A'+x2-'A')/2]=0;
                men[y2-1][x2-'A']=-1;
                numWhite--;
                if (check_capture_man (x2-'A',y2-1)==1) {xx=x2;yy=y2;ff=2;}
                else ff=0;
                save<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
        }
        if(x1-'A'>=0 && x1-'A'<8 && y1-1>=0 && y1-1<8 && x2-'A'>=0 && x2-'A'<8 && y2-1>=0 && y2-1<8 && men[y1-1][x1-'A']==-2 && abs(x1-x2)==2 && abs(y2-y1)==2 && men[y2-1][x2-'A']==0 && men[(y1+y2)/2-1][(x1-'A'+x2-'A')/2]>0 && (xx==x1 && yy==y1)==(xx!=-1))
        {
                men[y1-1][x1-'A']=0;
                men[(y1+y2)/2-1][(x1-'A'+x2-'A')/2]=0;
                men[y2-1][x2-'A']=-2;
                numWhite--;
                if (check_capture_man (x2-'A',y2-1)==1) {xx=x2;yy=y2;ff=2;}
                else ff=0;
                save<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
        }
    }
    return ff;
}
int pc_turn(int type)
{
    char x1,x2;
    bool king=check_capture_king(type);
    int y1,y2;
    int ff=1;
    x1='A'+rand()%8;
    y1=1+rand()%8;
    x2='A'+rand()%8;
    y2=1+rand()%8;
    if(type>0)
    {
        if(x1-'A'>=0 && x1-'A'<8 && y1-1>=0 && y1-1<8 && x2-'A'>=0 && x2-'A'<8 && y2-1>=0 && y2-1<8 && men[y1-1][x1-'A']==1 && abs(x1-x2)==1 && y2-y1==-1 && men[y2-1][x2-'A']==0 && check_capture(1)==0 && (xx==x1 && yy==y1)==(xx!=-1))
        {
                men[y1-1][x1-'A']=0;
                men[y2-1][x2-'A']=1;
                ff=0;
                if(en)cout<<"Robot"<<endl;else cout<<"Робот"<<endl;
                markman(x1-'A',y1);
                Sleep(1000);
                save<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
                cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
        }
        if(x1-'A'>=0 && x1-'A'<8 && y1-1>=0 && y1-1<8 && x2-'A'>=0 && x2-'A'<8 && y2-1>=0 && y2-1<8 && men[y1-1][x1-'A']==2 && abs(x1-x2)==1 && abs(y2-y1)==1 && men[y2-1][x2-'A']==0 && check_capture(1)==0 && (xx==x1 && yy==y1)==(xx!=-1))
        {
                men[y1-1][x1-'A']=0;
                men[y2-1][x2-'A']=2;
                ff=0;
                if(en)cout<<"Robot"<<endl;else cout<<"Робот"<<endl;
                markman(x1-'A',y1);
                Sleep(1000);
                save<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
                cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
        }
        if(x1-'A'>=0 && x1-'A'<8 && y1-1>=0 && y1-1<8 && x2-'A'>=0 && x2-'A'<8 && y2-1>=0 && y2-1<8 && men[y1-1][x1-'A']==1 && abs(x1-x2)==2 && y2-y1==-2 && men[y2-1][x2-'A']==0 && men[(y1+y2)/2-1][(x1-'A'+x2-'A')/2]<0 && (xx==x1 && yy==y1)==(xx!=-1))
        {
                if (men[(y1+y2)/2-1][(x1-'A'+x2-'A')/2]==-2 || king==0)
                {
                    men[y1-1][x1-'A']=0;
                    men[(y1+y2)/2-1][(x1-'A'+x2-'A')/2]=0;
                    men[y2-1][x2-'A']=1;
                    numRed--;
                    if (check_capture_man (x2-'A',y2-1)==1) {xx=x2;yy=y2;ff=2;}
                    else ff=0;
                    if(en)cout<<"Robot"<<endl;else cout<<"Робот"<<endl;
                    markman(x1-'A',y1);
                    Sleep(1000);
                    save<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
                    cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
                }
        }
        if(x1-'A'>=0 && x1-'A'<8 && y1-1>=0 && y1-1<8 && x2-'A'>=0 && x2-'A'<8 && y2-1>=0 && y2-1<8 && men[y1-1][x1-'A']==2 && abs(x1-x2)==2 && abs(y2-y1)==2 && men[y2-1][x2-'A']==0 && men[(y1+y2)/2-1][(x1-'A'+x2-'A')/2]<0 && (xx==x1 && yy==y1)==(xx!=-1))
        {
                if (men[(y1+y2)/2-1][(x1-'A'+x2-'A')/2]==-2 || king==0)
                {
                    men[y1-1][x1-'A']=0;
                    men[(y1+y2)/2-1][(x1-'A'+x2-'A')/2]=0;
                    men[y2-1][x2-'A']=2;
                    numRed--;
                    if (check_capture_man (x2-'A',y2-1)==1) {xx=x2;yy=y2;ff=2;}
                    else ff=0;
                    if(en)cout<<"Robot"<<endl;else cout<<"Робот"<<endl;
                    markman(x1-'A',y1);
                    Sleep(1000);
                    save<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
                    cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
                }
        }
    }
    if(type<0)
    {
        if(x1-'A'>=0 && x1-'A'<8 && y1-1>=0 && y1-1<8 && x2-'A'>=0 && x2-'A'<8 && y2-1>=0 && y2-1<8 && men[y1-1][x1-'A']==-1 && abs(x1-x2)==1 && y2-y1==1 && men[y2-1][x2-'A']==0 && check_capture(-1)==0 && (xx==x1 && yy==y1)==(xx!=-1))
        {
                men[y1-1][x1-'A']=0;
                men[y2-1][x2-'A']=-1;
                ff=0;
                if(en)cout<<"Robot"<<endl;else cout<<"Робот"<<endl;
                markman(x1-'A',y1);
                Sleep(1000);
                save<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
                cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
        }
        if(x1-'A'>=0 && x1-'A'<8 && y1-1>=0 && y1-1<8 && x2-'A'>=0 && x2-'A'<8 && y2-1>=0 && y2-1<8 && men[y1-1][x1-'A']==-2 && abs(x1-x2)==1 && abs(y2-y1)==1 && men[y2-1][x2-'A']==0 && check_capture(-1)==0 && (xx==x1 && yy==y1)==(xx!=-1))
        {
                men[y1-1][x1-'A']=0;
                men[y2-1][x2-'A']=-2;
                ff=0;
                if(en)cout<<"Robot"<<endl;else cout<<"Робот"<<endl;
                markman(x1-'A',y1);
                Sleep(1000);
                save<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
                cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
        }
        if(x1-'A'>=0 && x1-'A'<8 && y1-1>=0 && y1-1<8 && x2-'A'>=0 && x2-'A'<8 && y2-1>=0 && y2-1<8 && men[y1-1][x1-'A']==-1 && abs(x1-x2)==2 && y2-y1==2 && men[y2-1][x2-'A']==0 && men[(y1+y2)/2-1][(x1-'A'+x2-'A')/2]>0 && (xx==x1 && yy==y1)==(xx!=-1))
        {
                if (men[(y1+y2)/2-1][(x1-'A'+x2-'A')/2]==2 || king==0)
                {
                    men[y1-1][x1-'A']=0;
                    men[(y1+y2)/2-1][(x1-'A'+x2-'A')/2]=0;
                    men[y2-1][x2-'A']=-1;
                    numWhite--;
                    if (check_capture_man (x2-'A',y2-1)==1) {xx=x2;yy=y2;ff=2;}
                    else ff=0;
                    if(en)cout<<"Robot"<<endl;else cout<<"Робот"<<endl;
                    markman(x1-'A',y1);
                    Sleep(1000);
                    save<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
                    cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
                }
        }
        if(x1-'A'>=0 && x1-'A'<8 && y1-1>=0 && y1-1<8 && x2-'A'>=0 && x2-'A'<8 && y2-1>=0 && y2-1<8 && men[y1-1][x1-'A']==-2 && abs(x1-x2)==2 && abs(y2-y1)==2 && men[y2-1][x2-'A']==0 && men[(y1+y2)/2-1][(x1-'A'+x2-'A')/2]>0 && (xx==x1 && yy==y1)==(xx!=-1))
        {
                if (men[(y1+y2)/2-1][(x1-'A'+x2-'A')/2]==2 || king==0)
                {
                    men[y1-1][x1-'A']=0;
                    men[(y1+y2)/2-1][(x1-'A'+x2-'A')/2]=0;
                    men[y2-1][x2-'A']=-2;
                    numWhite--;
                    if (check_capture_man (x2-'A',y2-1)==1) {xx=x2;yy=y2;ff=2;}
                    else ff=0;
                    if(en)cout<<"Robot"<<endl;else cout<<"Робот"<<endl;
                    markman(x1-'A',y1);
                    Sleep(1000);
                    save<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
                    cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
                }
        }
    }
    return ff;
}
int continue_turn(int type)
{
    char x1='A',x2='A';
    int y1=-1,y2=-1;
    int ff=1;
    o_save>>x1>>y1>>x2>>y2;
    if (x1>='a' && x1<='z') x1+='A'-'a';
    if (x2>='a' && x2<='z') x2+='A'-'a';
    if(type>0)
    {
        if(x1-'A'>=0 && x1-'A'<8 && y1-1>=0 && y1-1<8 && x2-'A'>=0 && x2-'A'<8 && y2-1>=0 && y2-1<8 && men[y1-1][x1-'A']==1 && abs(x1-x2)==1 && y2-y1==-1 && men[y2-1][x2-'A']==0 && check_capture(1)==0 && (xx==x1 && yy==y1)==(xx!=-1))
        {
                men[y1-1][x1-'A']=0;
                men[y2-1][x2-'A']=1;
                ff=0;
                if(bot==0){if(en)cout<<"Player 2"<<endl;else cout<<"Играч 2"<<endl;}
                else {if(en)cout<<"Robot"<<endl;else cout<<"Робот"<<endl;}
                cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
        }
        if(x1-'A'>=0 && x1-'A'<8 && y1-1>=0 && y1-1<8 && x2-'A'>=0 && x2-'A'<8 && y2-1>=0 && y2-1<8 && men[y1-1][x1-'A']==2 && abs(x1-x2)==1 && abs(y2-y1)==1 && men[y2-1][x2-'A']==0 && check_capture(1)==0 && (xx==x1 && yy==y1)==(xx!=-1))
        {
                men[y1-1][x1-'A']=0;
                men[y2-1][x2-'A']=2;
                ff=0;
                if(bot==0){if(en)cout<<"Player 2"<<endl;else cout<<"Играч 2"<<endl;}
                else {if(en)cout<<"Robot"<<endl;else cout<<"Робот"<<endl;}
                cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
        }
        if(x1-'A'>=0 && x1-'A'<8 && y1-1>=0 && y1-1<8 && x2-'A'>=0 && x2-'A'<8 && y2-1>=0 && y2-1<8 && men[y1-1][x1-'A']==1 && abs(x1-x2)==2 && y2-y1==-2 && men[y2-1][x2-'A']==0 && men[(y1+y2)/2-1][(x1-'A'+x2-'A')/2]<0 && (xx==x1 && yy==y1)==(xx!=-1))
        {
                men[y1-1][x1-'A']=0;
                men[(y1+y2)/2-1][(x1-'A'+x2-'A')/2]=0;
                men[y2-1][x2-'A']=1;
                numRed--;
                if (check_capture_man (x2-'A',y2-1)==1) {xx=x2;yy=y2;ff=2;}
                else ff=0;
                if(bot==0){if(en)cout<<"Player 2"<<endl;else cout<<"Играч 2"<<endl;}
                else {if(en)cout<<"Robot"<<endl;else cout<<"Робот"<<endl;}
                cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
        }
        if(x1-'A'>=0 && x1-'A'<8 && y1-1>=0 && y1-1<8 && x2-'A'>=0 && x2-'A'<8 && y2-1>=0 && y2-1<8 && men[y1-1][x1-'A']==2 && abs(x1-x2)==2 && abs(y2-y1)==2 && men[y2-1][x2-'A']==0 && men[(y1+y2)/2-1][(x1-'A'+x2-'A')/2]<0 && (xx==x1 && yy==y1)==(xx!=-1))
        {
                men[y1-1][x1-'A']=0;
                men[(y1+y2)/2-1][(x1-'A'+x2-'A')/2]=0;
                men[y2-1][x2-'A']=2;
                numRed--;
                if (check_capture_man (x2-'A',y2-1)==1) {xx=x2;yy=y2;ff=2;}
                else ff=0;
                if(bot==0){if(en)cout<<"Player 2"<<endl;else cout<<"Играч 2"<<endl;}
                else {if(en)cout<<"Robot"<<endl;else cout<<"Робот"<<endl;}
                cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
        }
    }
    if(type<0)
    {
        if(x1-'A'>=0 && x1-'A'<8 && y1-1>=0 && y1-1<8 && x2-'A'>=0 && x2-'A'<8 && y2-1>=0 && y2-1<8 && men[y1-1][x1-'A']==-1 && abs(x1-x2)==1 && y2-y1==1 && men[y2-1][x2-'A']==0 && check_capture(-1)==0 && (xx==x1 && yy==y1)==(xx!=-1))
        {
                men[y1-1][x1-'A']=0;
                men[y2-1][x2-'A']=-1;
                ff=0;
                if(en)cout<<"Player 1"<<endl;else cout<<"Играч 1"<<endl;
                cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
        }
        if(x1-'A'>=0 && x1-'A'<8 && y1-1>=0 && y1-1<8 && x2-'A'>=0 && x2-'A'<8 && y2-1>=0 && y2-1<8 && men[y1-1][x1-'A']==-2 && abs(x1-x2)==1 && abs(y2-y1)==1 && men[y2-1][x2-'A']==0 && check_capture(-1)==0 && (xx==x1 && yy==y1)==(xx!=-1))
        {
                men[y1-1][x1-'A']=0;
                men[y2-1][x2-'A']=-2;
                ff=0;
                if(en)cout<<"Player 1"<<endl;else cout<<"Играч 1"<<endl;
                cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
        }
        if(x1-'A'>=0 && x1-'A'<8 && y1-1>=0 && y1-1<8 && x2-'A'>=0 && x2-'A'<8 && y2-1>=0 && y2-1<8 && men[y1-1][x1-'A']==-1 && abs(x1-x2)==2 && y2-y1==2 && men[y2-1][x2-'A']==0 && men[(y1+y2)/2-1][(x1-'A'+x2-'A')/2]>0 && (xx==x1 && yy==y1)==(xx!=-1))
        {
                men[y1-1][x1-'A']=0;
                men[(y1+y2)/2-1][(x1-'A'+x2-'A')/2]=0;
                men[y2-1][x2-'A']=-1;
                numWhite--;
                if (check_capture_man (x2-'A',y2-1)==1) {xx=x2;yy=y2;ff=2;}
                else ff=0;
                if(en)cout<<"Player 1"<<endl;else cout<<"Играч 1"<<endl;
                cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
        }
        if(x1-'A'>=0 && x1-'A'<8 && y1-1>=0 && y1-1<8 && x2-'A'>=0 && x2-'A'<8 && y2-1>=0 && y2-1<8 && men[y1-1][x1-'A']==-2 && abs(x1-x2)==2 && abs(y2-y1)==2 && men[y2-1][x2-'A']==0 && men[(y1+y2)/2-1][(x1-'A'+x2-'A')/2]>0 && (xx==x1 && yy==y1)==(xx!=-1))
        {
                men[y1-1][x1-'A']=0;
                men[(y1+y2)/2-1][(x1-'A'+x2-'A')/2]=0;
                men[y2-1][x2-'A']=-2;
                numWhite--;
                if (check_capture_man (x2-'A',y2-1)==1) {xx=x2;yy=y2;ff=2;}
                else ff=0;
                if(en)cout<<"Player 1"<<endl;else cout<<"Играч 1"<<endl;
                cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
        }
    }
    return ff;
}
void play(bool who=0)
{
    int ff;
    if (who==1)
    {
        draw_board();
        ff=turn (1);
        while (ff!=0)
        {
            if (ff==1){if(en)cout<<"Invalid Move"<<endl;else cout<<"Грешен ход\n";}
            draw_board();
            if (winner())break;
            ff=turn (1);
        }
        xx=-1;
        yy=-1;
        crown();
    }
    while(1)
    {
        draw_board();
        if (winner())break;
        ff=turn (-1);
        while (ff!=0)
        {
            if (ff==1){if(en)cout<<"Invalid Move"<<endl;else cout<<"Грешен ход\n";}
            draw_board();
            if (winner())break;
            ff=turn (-1);
        }
        xx=-1;
        yy=-1;
        crown();
        draw_board();
        if (winner())break;
        ff=turn (1);
        while (ff!=0)
        {
            if (ff==1){if(en)cout<<"Invalid Move"<<endl;else cout<<"Грешен ход\n";}
            draw_board();
            if (winner())break;
            ff=turn (1);
        }
        xx=-1;
        yy=-1;
        crown();
    }
    if (winner()==1)
    {
        setfillstyle(1,0);
        bar(30+3*60-20,30+3*60+20,30+5*60+20,30+5*60-20);
        setcolor(15);
        moveto(30+3*60-10,30+3*60+30);
        settextstyle(1,0,1);
        outtext("   WHITE");
        moveto(30+3*60-10,30+4*60+10);
        outtext("    WINS");
        if(en)cout<<"Player 2 wins!!!"<<endl;
        else cout<<"Играч 2 печели!!!"<<endl;
    }
    else
    {
        setfillstyle(1,0);
        bar(30+3*60-20,30+3*60+20,30+5*60+20,30+5*60-20);
        setcolor(15);
        moveto(30+3*60-10,30+3*60+30);
        settextstyle(1,0,1);
        outtext("      RED");
        moveto(30+3*60-10,30+4*60+10);
        outtext("     WINS");
        if(en)cout<<"Player 1 wins!!!"<<endl;
        else cout<<"Играч 1 печели!!!"<<endl;
    }
}
void pc_play(bool who=0)
{
    int ff;
    if (who==1)
    {
        draw_board();
        ff=pc_turn (1);
        while (ff!=0)
        {
            if (ff==2) draw_board();
            if (winner())break;
            ff=pc_turn (1);
        }
        xx=-1;
        yy=-1;
        crown();
    }
    while(1)
    {
        draw_board();
        if (winner())break;
        ff=turn (-1);
        while (ff!=0)
        {
            if (ff==1){if(en)cout<<"Invalid Move"<<endl;else cout<<"Грешен ход"<<endl;}
            draw_board();
            if (winner())break;
            ff=turn (-1);
        }
        xx=-1;
        yy=-1;
        crown();
        draw_board();
        if (winner())break;
        ff=pc_turn (1);
        while (ff!=0)
        {
            if (ff==2) draw_board();
            if (winner())break;
            ff=pc_turn (1);
        }
        xx=-1;
        yy=-1;
        crown();
    }
    if (winner()==1)
    {
        setfillstyle(1,0);
        bar(30+3*60-20,30+3*60+20,30+5*60+20,30+5*60-20);
        setcolor(15);
        moveto(30+3*60-10,30+3*60+30);
        settextstyle(1,0,1);
        outtext("     YOU");
        moveto(30+3*60-15,30+4*60+10);
        outtext("     LOSE");
        if(en)cout<<"The Robot wins!!!"<<endl;
        else cout<<"Роботът печели!!!"<<endl;
    }
    else
    {
        setfillstyle(1,0);
        bar(30+3*60-20,30+3*60+20,30+5*60+20,30+5*60-20);
        setcolor(15);
        moveto(30+3*60-10,30+3*60+30);
        settextstyle(1,0,1);
        outtext("     YOU");
        moveto(30+3*60-10,30+4*60+10);
        outtext("     WIN");
        if(en)cout<<"Player 1 wins!!!"<<endl;
        else cout<<"Играч 1 печели!!!"<<endl;
    }
}
void continue_game()
{
    int ff;
    int who=0;
    bool br=1;
    while (1)
    {
        draw_board();
        ff=continue_turn (-1);
        while (ff!=0)
        {
            if (ff==1) {br=0;break;}
            draw_board();
            ff=continue_turn (-1);
        }
        if (br==0) break;
        who++;
        xx=-1;
        yy=-1;
        crown();
        draw_board();
        ff=continue_turn (1);
        while (ff!=0)
        {
            if (ff==1) {br=0;break;}
            draw_board();
            ff=continue_turn (1);
        }
        if (br==0) break;
        who--;
        xx=-1;
        yy=-1;
        crown();
    }
    if (bot==0) play(who);
    else pc_play(who);
}
void example(int exmpl_num)
{
     setfillstyle(1,0);
     bar(0,164,800,804);
     if(exmpl_num==1)
     {
          moveto(20,164);if(en)outtext("Example for rule 1.");else outtext("Пример за правило 1.");
          for(int i=1;i<=8;i++)
          {
               for(int j=1;j<=8;j++)
               {
                    if((i%2)==(j%2))
                    {
                         setfillstyle(1,15);
                    }
                    else
                    {
                         setfillstyle(1,2);
                    }
                    bar((i-1)*30+20+10,(j-1)*30+185,i*30+20+10,j*30+185);
               }
          }
     }
     else if(exmpl_num==2)
     {
          moveto(20,164);if(en)outtext("Example for rule 2.");else outtext("Пример за правило 2.");
          for(int i=1;i<=3;i++)
          {
               for(int j=1;j<=2;j++)
               {
                    if((i%2)==(j%2))
                    {
                         setfillstyle(1,2);
                    }
                    else
                    {
                         setfillstyle(1,15);
                    }
                    bar((i-1)*30+20+10,(j-1)*30+185,i*30+20+10,j*30+185);
                    if(i==2&&j==2){setcolor(2);setfillstyle(1,4);fillellipse((i-1)*30+45,(j-1)*30+200,13,13);}
               }
          }
          setcolor(15);moveto(30,275);if(en)outtext("--Before--");else outtext("--Преди--");
          for(int i=1;i<=3;i++)
          {
               for(int j=1;j<=2;j++)
               {
                    if((i%2)==(j%2))
                    {
                         setcolor(2);
                         setfillstyle(1,2);
                    }
                    else
                    {
                         setcolor(15);
                         setfillstyle(1,15);
                    }
                    bar((i-1)*30+20+10+120,(j-1)*30+185,i*30+20+130,j*30+185);
               }
          }
          setcolor(2);setfillstyle(1,4);fillellipse((1-1)*30+45+120,(1-1)*30+200,13,13);
          fillellipse((3-1)*30+45+120,(1-1)*30+200,13,13);
          setcolor(15);moveto(30+120,255);if(en)outtext("The figure is at one of these positions.");else outtext("Пулчетo е в една от позициите.");
          setcolor(15);moveto(30+120,275);if(en)outtext("--After--");else outtext("--След--");
     }
     else if(exmpl_num==3)
     {
          moveto(20,164);if(en)outtext("Example for rule 3.");else outtext("Пример за правило 3.");
          for(int i=1;i<=3;i++)
          {
               for(int j=1;j<=3;j++)
               {
                    if((i%2)==(j%2))
                    {
                         setfillstyle(1,2);
                    }
                    else
                    {
                         setfillstyle(1,15);
                    }
                    bar((i-1)*30+20+10,(j-1)*30+185,i*30+20+10,j*30+185);
               }
          }
          for(int i=1;i<=3;i++)
          {
               for(int j=1;j<=3;j++)
               {
                    if((i%2)==(j%2))
                    {
                         setfillstyle(1,2);
                    }
                    else
                    {
                         setfillstyle(1,15);
                    }
                    bar((i-1)*30+20+10,(j-1)*30+185+110,i*30+20+10,j*30+185+110);
               }
          }
          setcolor(15);moveto(30,285+110);if(en)outtext("--Before--");else outtext("--Преди--");
          for(int i=1;i<=3;i++)
          {
               for(int j=1;j<=3;j++)
               {
                    if((i%2)==(j%2))
                    {
                         setfillstyle(1,2);
                    }
                    else
                    {
                         setfillstyle(1,15);
                    }
                    bar((i-1)*30+20+10+110,(j-1)*30+185,i*30+20+10+110,j*30+185);
               }
          }
          for(int i=1;i<=3;i++)
          {
               for(int j=1;j<=3;j++)
               {
                    if((i%2)==(j%2))
                    {
                         setfillstyle(1,2);
                    }
                    else
                    {
                         setfillstyle(1,15);
                    }
                    bar((i-1)*30+20+10+110,(j-1)*30+185+110,i*30+20+10+110,j*30+185+110);
               }
          }
          setcolor(2);setfillstyle(1,4);
          fillellipse((3-1)*30+45+110,(1-1)*30+200,13,13);
          fillellipse((1-1)*30+45+110,(1-1)*30+200+110,13,13);
          fillellipse((1-1)*30+45,(3-1)*30+200,13,13);
          fillellipse((3-1)*30+45,(3-1)*30+200+110,13,13);
          setcolor(2);setfillstyle(1,7);
          fillellipse((2-1)*30+45,(2-1)*30+200,13,13);
          fillellipse((2-1)*30+45,(2-1)*30+200+110,13,13);
          setcolor(15);moveto(30+120,285+110);if(en)outtext("--After--");else outtext("--След--");
     }
     else if(exmpl_num==4)
     {
          moveto(20,164);if(en)outtext("Example for rule 4.");else outtext("Пример за правило 4.");
          for(int i=1;i<=3;i++)
          {
               for(int j=1;j<=8;j++)
               {
                    if((i%2)==(j%2))
                    {
                         setfillstyle(1,15);
                    }
                    else
                    {
                         setfillstyle(1,2);
                    }
                    bar((i-1)*30+20+10,(j-1)*30+185,i*30+20+10,j*30+185);
               }
          }
          setcolor(2);setfillstyle(1,4);
          fillellipse((2-1)*30+45,(1-1)*30+200,13,13);
          setcolor(4);
          line((2-1)*30+45,(1-1)*30+200+210,(2-1)*30+45,(1-1)*30+200+20);
          line((2-1)*30+45-10,(1-1)*30+200+40,(2-1)*30+45,(1-1)*30+200+20);
          line((2-1)*30+45+10,(1-1)*30+200+40,(2-1)*30+45,(1-1)*30+200+20);
          setcolor(15);moveto(30,430);if(en)outtext("--Before--");else outtext("--Преди--");
          for(int i=1;i<=3;i++)
          {
               for(int j=1;j<=8;j++)
               {
                    if((i%2)==(j%2))
                    {
                         setcolor(2);
                         setfillstyle(1,15);
                    }
                    else
                    {
                         setcolor(15);
                         setfillstyle(1,2);
                    }
                    bar((i-1)*30+20+10+120,(j-1)*30+185,i*30+20+130,j*30+185);
               }
          }
          setcolor(2);setfillstyle(1,4);
          fillellipse((2-1)*30+45+120,(1-1)*30+200,13,13);
          setcolor(7);setfillstyle(1,7);
          fillellipse((2-1)*30+45+120,(1-1)*30+200,4,4);
          setcolor(15);moveto(30+120,430);if(en)outtext("--After--");else outtext("--След--");
     }
     else if(exmpl_num==5)
     {
          moveto(20,164);if(en)outtext("Example for rule 5.");else outtext("Пример за правило 5.");
          for(int i=1;i<=3;i++)
          {
               for(int j=1;j<=3;j++)
               {
                    if((i%2)==(j%2))
                    {
                         setfillstyle(1,2);
                    }
                    else
                    {
                         setfillstyle(1,15);
                    }
                    bar((i-1)*30+20+10,(j-1)*30+185,i*30+20+10,j*30+185);
               }
          }
          setcolor(2);setfillstyle(1,4);
          fillellipse((2-1)*30+45,(2-1)*30+200,13,13);
          setcolor(7);setfillstyle(1,7);
          fillellipse((2-1)*30+45,(2-1)*30+200,4,4);
          setcolor(15);moveto(30,305);if(en)outtext("--Before--");else outtext("--Преди--");
          for(int i=1;i<=3;i++)
          {
               for(int j=1;j<=3;j++)
               {
                    if((i%2)==(j%2))
                    {
                         setcolor(2);
                         setfillstyle(1,2);
                    }
                    else
                    {
                         setcolor(15);
                         setfillstyle(1,15);
                    }
                    bar((i-1)*30+20+10+120,(j-1)*30+185,i*30+20+130,j*30+185);
               }
          }
          setcolor(2);setfillstyle(1,4);
          fillellipse((1-1)*30+45+120,(1-1)*30+200,13,13);
          fillellipse((1-1)*30+45+120,(3-1)*30+200,13,13);
          fillellipse((3-1)*30+45+120,(1-1)*30+200,13,13);
          fillellipse((3-1)*30+45+120,(3-1)*30+200,13,13);
          setcolor(7);setfillstyle(1,7);
          fillellipse((1-1)*30+45+120,(1-1)*30+200,4,4);
          fillellipse((1-1)*30+45+120,(3-1)*30+200,4,4);
          fillellipse((3-1)*30+45+120,(1-1)*30+200,4,4);
          fillellipse((3-1)*30+45+120,(3-1)*30+200,4,4);
          setcolor(15);moveto(30+120,285);if(en)outtext("The king is at one of these positions.");else outtext("Кралското пулче е в една от позициите.");
          setcolor(15);moveto(30+120,305);if(en)outtext("--After--");else outtext("--След--");
     }
     if(exmpl_num==6)
     {
          moveto(20,164);if(en)outtext("Example for rule 6.");else outtext("Пример за правило 6.");
          for(int i=1;i<=3;i++)
          {
               for(int j=1;j<=3;j++)
               {
                    if((i%2)==(j%2))
                    {
                         setfillstyle(1,2);
                    }
                    else
                    {
                         setfillstyle(1,15);
                    }
                    bar((i-1)*30+20+10,(j-1)*30+185,i*30+20+10,j*30+185);
               }
          }
          for(int i=1;i<=3;i++)
          {
               for(int j=1;j<=3;j++)
               {
                    if((i%2)==(j%2))
                    {
                         setfillstyle(1,2);
                    }
                    else
                    {
                         setfillstyle(1,15);
                    }
                    bar((i-1)*30+20+10,(j-1)*30+185+110,i*30+20+10,j*30+185+110);
               }
          }
          setcolor(15);moveto(30,285+110);if(en)outtext("--Before--");else outtext("--Преди--");
          for(int i=1;i<=3;i++)
          {
               for(int j=1;j<=3;j++)
               {
                    if((i%2)==(j%2))
                    {
                         setfillstyle(1,2);
                    }
                    else
                    {
                         setfillstyle(1,15);
                    }
                    bar((i-1)*30+20+10+110,(j-1)*30+185,i*30+20+10+110,j*30+185);
               }
          }
          for(int i=1;i<=3;i++)
          {
               for(int j=1;j<=3;j++)
               {
                    if((i%2)==(j%2))
                    {
                         setfillstyle(1,2);
                    }
                    else
                    {
                         setfillstyle(1,15);
                    }
                    bar((i-1)*30+20+10+110,(j-1)*30+185+110,i*30+20+10+110,j*30+185+110);
               }
          }
          setcolor(2);setfillstyle(1,4);
          fillellipse((3-1)*30+45+110,(1-1)*30+200,13,13);
          fillellipse((1-1)*30+45+110,(1-1)*30+200+110,13,13);
          fillellipse((1-1)*30+45,(3-1)*30+200,13,13);
          fillellipse((3-1)*30+45,(3-1)*30+200+110,13,13);
          setcolor(2);setfillstyle(1,7);
          fillellipse((2-1)*30+45,(2-1)*30+200,13,13);
          fillellipse((2-1)*30+45,(2-1)*30+200+110,13,13);
          setcolor(7);setfillstyle(1,7);
          fillellipse((3-1)*30+45+110,(1-1)*30+200,4,4);
          fillellipse((1-1)*30+45+110,(1-1)*30+200+110,4,4);
          fillellipse((1-1)*30+45,(3-1)*30+200,4,4);
          fillellipse((3-1)*30+45,(3-1)*30+200+110,4,4);
          setcolor(15);moveto(30+120,285+110);if(en)outtext("--After--");else outtext("--След--");
          //---------------------------------------------------
          //===================================================
          //---------------------------------------------------
          for(int i=1;i<=3;i++)
          {
               for(int j=1;j<=3;j++)
               {
                    if((i%2)==(j%2))
                    {
                         setfillstyle(1,2);
                    }
                    else
                    {
                         setfillstyle(1,15);
                    }
                    bar((i-1)*30+20+10+120+150,(j-1)*30+185,i*30+20+10+270,j*30+185);
               }
          }
          for(int i=1;i<=3;i++)
          {
               for(int j=1;j<=3;j++)
               {
                    if((i%2)==(j%2))
                    {
                         setfillstyle(1,2);
                    }
                    else
                    {
                         setfillstyle(1,15);
                    }
                    bar((i-1)*30+20+10+120+150,(j-1)*30+185+110,i*30+20+10+270,j*30+185+110);
               }
          }
          setcolor(15);moveto(30+270,285+110);if(en)outtext("--Before--");else outtext("--Преди--");
          for(int i=1;i<=3;i++)
          {
               for(int j=1;j<=3;j++)
               {
                    if((i%2)==(j%2))
                    {
                         setfillstyle(1,2);
                    }
                    else
                    {
                         setfillstyle(1,15);
                    }
                    bar((i-1)*30+20+10+110+270,(j-1)*30+185,i*30+20+10+110+270,j*30+185);
               }
          }
          for(int i=1;i<=3;i++)
          {
               for(int j=1;j<=3;j++)
               {
                    if((i%2)==(j%2))
                    {
                         setfillstyle(1,2);
                    }
                    else
                    {
                         setfillstyle(1,15);
                    }
                    bar((i-1)*30+20+10+110+270,(j-1)*30+185+110,i*30+20+10+110+270,j*30+185+110);
               }
          }
          setcolor(2);setfillstyle(1,4);
          fillellipse((3-1)*30+45+110+150+120,(3-1)*30+200,13,13);
          fillellipse((1-1)*30+45+110+150+120,(3-1)*30+200+110,13,13);
          fillellipse((1-1)*30+45+150+120,(1-1)*30+200,13,13);
          fillellipse((3-1)*30+45+150+120,(1-1)*30+200+110,13,13);
          setcolor(2);setfillstyle(1,7);
          fillellipse((2-1)*30+45+150+120,(2-1)*30+200,13,13);
          fillellipse((2-1)*30+45+150+120,(2-1)*30+200+110,13,13);
          setcolor(7);setfillstyle(1,7);
          fillellipse((3-1)*30+45+110+150+120,(3-1)*30+200,4,4);
          fillellipse((1-1)*30+45+110+150+120,(3-1)*30+200+110,4,4);
          fillellipse((1-1)*30+45+150+120,(1-1)*30+200,4,4);
          fillellipse((3-1)*30+45+150+120,(1-1)*30+200+110,4,4);
          setcolor(15);moveto(30+120+150+120,285+110);if(en)outtext("--After--");else outtext("--След--");
     }
}
void main_en()
{
    initwindow(655,460,"Rules");
    moveto(40,5);outtext("This computer version of checkers is made by Dimitar Tomov and Emil Indjev.");
    moveto(20,20+1);outtext("Rules:");
    moveto(20,35+2);outtext("     (1)The board is 8x8. (2)The player with the dark men is first. Every turn you have to");
    moveto(20,50+3);outtext("move one of your men by one square on one of the front diagonals. You win when your");
    moveto(20,65+4);outtext("opponent is out of men. (3)If you can capture you have to do it. If there is an opponent's");
    moveto(20,80+5);outtext("man on one of the front diagonals you have to capture it by jumping over the opponent's");
    moveto(20,95+6);outtext("man and it's removed from the board. If in the end of a capturing you are able to capture ");
    moveto(20,110+7);outtext("again with the same man you have to do it. (4)Also, when a man gets to the end of the ");
    moveto(20,125+8);outtext("board it becomes a king. A king can (5)move and (6)take on every diagonal.");
    system("color 2F");
    cout<<"\tThe rules of the game are shown in the other window.\nIf you want to see an example picture to help you understand the rules, please \nenter the number of the rule. If you don't want more examples enter 0.\n";
    char exmpl_num='9';
    while(exmpl_num-'0')
    {
         cin>>exmpl_num;
         if(exmpl_num-'0'>6||exmpl_num-'0'<0){cout<<"This is not a correct number of a rule! Please try again!\n";continue;}
         example(exmpl_num-'0');
    }
    cout<<"\tFor 2 players enter 2. For 1 player enter 1.\n";
    char oo;
    cin>>oo;
    while (oo!='1' && oo!='2')
    {
         cout<<"This is not a correct command! Please try again!\n";
         cin>>oo;
    }
    cout<<"\tIf you are ready to play the game please enter 'G'. To continue your \nlast game enter 'C'. Player 1 is the person with the red men.\n\t\tWISH YOU HAVE FUN!\n";
    char o;
    cin>>o;
    while(o!='G' && o!='g' && o!='C' && o!='c')
    {
         cout<<"This is not a correct command! Please try again!\n";
         cin>>o;
    }
    cout<<"\tTo play with the keyboard enter 1. To play with the mouse enter 2. If\nyou choose the keyboard the game will ask you to enter coordinates of your man\nand the coordinates to which you want to move him. Coordinates have to be as\nthe following - the letter has to be first and the number - second. If you\nenter wrong coordinates the game will ask again. If you choose the mouse you\nhave to click on your man and then click on the square to which you want to\nmove him."<<endl;
    char op;
    cin>>op;
    while(op!='1' && op!='2')
    {
         cout<<"This is not a correct command! Please try again!\n";
         cin>>op;
    }
    if (op=='1') mouse=0;
    else mouse=1;
    system("cls");
    if (oo=='2')
    {
        bot=0;
        if(o=='g'||o=='G')
        {
            initwindow(550,550,"English Checkers 1.0 Multiplayer");
            ofstream dd_save("save.save");
            spawn();
            play(0);
        }
        if(o=='c'||o=='C')
        {
            initwindow(550,550,"English Checkers 1.0 Multiplayer");
            spawn();
            continue_game();
        }
    }
    else
    {
        bot=1;
        if(o=='g'||o=='G')
        {
            initwindow(550,550,"English Checkers 1.0 Multiplayer");
            ofstream dd_save("save.save");
            spawn();
            pc_play(0);
        }
        if(o=='c'||o=='C')
        {
            initwindow(550,550,"English Checkers 1.0 Multiplayer");
            spawn();
            continue_game();
        }
    }
}
void main_bg()
{
    initwindow(655,460,"Rules");
    moveto(40,3);outtext("Тази версия на шашки за компютър е направена от Димитър Томов и Емил Инджев.");
    moveto(20,20-1);outtext("Правила:");
    moveto(20,35);outtext("     (1)Дъската е 8x8. (2)Играчът с тъмните пулчета е пръв. Местенето на пулче става като");
    moveto(20,50+1);outtext("го изместин напред с едно квадратче по диагонал. Играч печели, когато противникът му ");
    moveto(20,65+2);outtext("остане без пулчета. (3)Ако можете да вземете пулче, сте длъжни да го направите. Ако ");
    moveto(20,80+3);outtext("има противниково пулче на съседното квадратче от предните диагонали, вие го вземате ");
    moveto(20,95+4);outtext("като го прескочите, ако на мястото където ще кацне пулчето Ви няма друго пулче и про- ");
    moveto(20,110+5);outtext("тивниковото пулче се изважда от дъската. Ако след вземане можете да вземете със съ-");
    moveto(20,125+6);outtext("щото пулче, то сте длъжни да го направите. (4)Ако пулче стигне до края на дъскaта, то");
    moveto(20,147);outtext("става кралско. Кралското пулче се (5)движи и (6)взема по всеки диагонал.");
    system("color 2F");
    cout<<"\tПравилата на играта са показани в отделен прозорец.\nАко искате да видите илюстрация, която да ви помогне да разберето по-добре\nнякое правило, моля въведете номер на правилото. Ако сте разбрали правилата и\nискате да продължите към играта, моля въведете 0.\n";
    char exmpl_num='9';
    while(exmpl_num-'0')
    {
         cin>>exmpl_num;
         if(exmpl_num-'0'>6||exmpl_num-'0'<0){cout<<"Това не е валиден номер на правило! Моля опитайте отново\n";continue;}
         example(exmpl_num-'0');
    }
    cout<<"\tЗа двама играчи въведете 2. За 1 играч въведете 1.\n";
    char oo;
    cin>>oo;
    while (oo!='1' && oo!='2')
    {
         cout<<"Това не е правилна команда! Моля опитайте отново!\n";
         cin>>oo;
    }
    cout<<"\tАко сте готови да играете, въведете 'И'. За да продължите последната си\nигра въведете 'П'. Играч 1 е играчът с червените пулчета.\n\t\tПОЖЕЛАВАМЕ ВИ ПРИЯТНА ИГРА!\n";
    char o;
    cin>>o;
    while(o!='И' && o!='и' && o!='П' && o!='п')
    {
         cout<<"Това не е валидна команда! Моля опитайте отново!\n";
         cin>>o;
    }
    cout<<"\tЗа да играете с клавиатурата въведете 1. За да играете с мишката\nвъведете 2. Ако изберете клавиатурата, играта ще изчаква да въведете координати\nна пулчето, което искате да преместите и координати на мястото, където искате\nда го преместите. Координатите трябва да съдържат буква на първо място и цифра\nна второ. Ако въведете грешни координати, ще имате възможност да въведете\nверни. Ако изберете мишката, трябва да кликнете на пулчето си и после да\nкликнете на квадрата, на който искате да се премести."<<endl;
    char op;
    cin>>op;
    while(op!='1' && op!='2')
    {
         cout<<"This is not a correct command! Please try again!\n";
         cin>>op;
    }
    if (op=='1') mouse=0;
    else mouse=1;
    system("cls");
    if (oo=='2')
    {
        bot=0;
        if(o=='и'||o=='И')
        {
            initwindow(550,550,"English Checkers 1.0 Multiplayer");
            ofstream dd_save("save.save");
            spawn();
            play(0);
        }
        if(o=='п'||o=='П')
        {
            initwindow(550,550,"English Checkers 1.0 Multiplayer");
            spawn();
            continue_game();
        }
    }
    else
    {
        bot=1;
        if(o=='и'||o=='И')
        {
            initwindow(550,550,"English Checkers 1.0 Multiplayer");
            ofstream dd_save("save.save");
            spawn();
            pc_play(0);
        }
        if(o=='п'||o=='П')
        {
            initwindow(550,550,"English Checkers 1.0 Multiplayer");
            spawn();
            continue_game();
        }
    }
}
int main()
{
    system("chcp 1251");
	system("cls");
	system("color 2f");
    while(1)
	{
		string lang="";
		cout<<"Please choose language.\nМоля изберете език.\nFor English enter 'english' (without the quotes).\nЗа Български въведете 'български' (без кавичките).\n";
		cin>>lang;
        for(int i=0;i<lang.size();i++)
		{
			if(lang[i]>='a' && lang[i]<='z') lang[i]+='A'-'a';
			if(lang[i]>='а' && lang[i]<='я') lang[i]+='А'-'а';
		}
		if(lang=="ENGLISH"){en=true;system("cls");main_en();break;}
		if(lang=="БЪЛГАРСКИ"){system("cls");main_bg();break;}
		cout<<"Press any key to continue.\nНатиснете произволен клавиш за да продължите.\n";
		char c;cin.get(c);system("cls");
		cout<<"Please try again.\nМоля опитайте отново.\n";
	}
    system("pause");
    return 0;
}
