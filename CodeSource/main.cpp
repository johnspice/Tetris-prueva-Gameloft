#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "winbgim.h"
#include <cstdlib>
#include <stdlib.h>
#include <time.h>

/* Colors "winbgim.h": 0=BLACK 1=BLUE 2=GREEN 3=CYAN 4=RED 5=MAGENTA 6=BROWN 7=LIGHTGRAY 8=DARKGRAY
9=LIGHTBLUE 10=LIGHTGREEN 11=LIGHTCYAN 12=LIGHTRED 13=LIGHTMAGENTA 14=YELLOW 15=WHITE
functions winbgim.h used: setcolor()-Setting color, rectangle()-for draw rectangle, outtextxy()-draw text,
                          settextstyle()-setting type text.
*/


using namespace std;


int y=14,r=4,c=3,w=15,b=0,g=10,Score=0;
int p0i=1,p0j=14,pi=1,pj=14,rot=0,rot0=0,TimeMovPiece=1000;//i=fila j=columna
int Area[20][30],ColorPiece,CurrentPiece,NextColorPiece,NextPiece;
char Sc[5];//use for show Score in "winbgim"
bool NewPiece=false,StartGame=false;
/////////////////////////////////////////////////       DEFINE PIECES  y rotations     ///////////////////////////////////////////
// PIECE O
int pO[4][4][4]={{{1,1,0,0},
                  {1,1,0,0},
                  {0,0,0,0},
                  {0,0,0,0}},

                {{1,1,0,0},
                 {1,1,0,0},
                 {0,0,0,0},
                 {0,0,0,0}},

                {{1,1,0,0},
                 {1,1,0,0},
                 {0,0,0,0},
                 {0,0,0,0}},

                {{1,1,0,0},
                 {1,1,0,0},
                 {0,0,0,0},
                 {0,0,0,0}}};

//PIECE I
int pI[4][4][4]={{{1,0,0,0},
                  {1,0,0,0},
                  {1,0,0,0},
                  {1,0,0,0}},

                {{1,1,1,1},
                 {0,0,0,0},
                 {0,0,0,0},
                 {0,0,0,0}},

                {{1,0,0,0},
                 {1,0,0,0},
                 {1,0,0,0},
                 {1,0,0,0}},

                {{1,1,1,1},
                 {0,0,0,0},
                 {0,0,0,0},
                 {0,0,0,0}}};

//PIECE S
int pS[4][4][4]={{{0,1,1,0},
                  {1,1,0,0},
                  {0,0,0,0},
                  {0,0,0,0}},

                {{1,0,0,0},
                 {1,1,0,0},
                 {0,1,0,0},
                 {0,0,0,0}},

                {{0,1,1,0},
                 {1,1,0,0},
                 {0,0,0,0},
                 {0,0,0,0}},

                {{1,0,0,0},
                 {1,1,0,0},
                 {0,1,0,0},
                 {0,0,0,0}}};

//PIECE Z
int pZ[4][4][4]={{{1,1,0,0},
                  {0,1,1,0},
                  {0,0,0,0},
                  {0,0,0,0}},

                {{0,1,0,0},
                 {1,1,0,0},
                 {1,0,0,0},
                 {0,0,0,0}},

                {{1,1,0,0},
                 {0,1,1,0},
                 {0,0,0,0},
                 {0,0,0,0}},

                {{0,1,0,0},
                 {1,1,0,0},
                 {1,0,0,0},
                 {0,0,0,0}}};

//PIECE L
int pL[4][4][4]={{{1,0,0,0},
                  {1,0,0,0},
                  {1,1,0,0},
                  {0,0,0,0}},

                {{0,0,1,0},
                 {1,1,1,0},
                 {0,0,0,0},
                 {0,0,0,0}},

                {{1,1,0,0},
                 {0,1,0,0},
                 {0,1,0,0},
                 {0,0,0,0}},

                {{1,1,1,0},
                 {1,0,0,0},
                 {0,0,0,0},
                 {0,0,0,0}}};

//PIECE J
int pJ[4][4][4]={{{0,1,0,0},
                  {0,1,0,0},
                  {1,1,0,0},
                  {0,0,0,0}},

                {{1,1,1,0},
                 {0,0,1,0},
                 {0,0,0,0},
                 {0,0,0,0}},

                {{1,1,0,0},
                 {1,0,0,0},
                 {1,0,0,0},
                 {0,0,0,0}},

                {{1,0,0,0},
                 {1,1,1,0},
                 {0,0,0,0},
                 {0,0,0,0}}};

//PIECE T
int pT[4][4][4]={{{1,1,1,0},
                  {0,1,0,0},
                  {0,0,0,0},
                  {0,0,0,0}},

                {{1,0,0,0},
                 {1,1,0,0},
                 {1,0,0,0},
                 {0,0,0,0}},

                {{0,1,0,0},
                 {1,1,1,0},
                 {0,0,0,0},
                 {0,0,0,0}},

                {{0,1,0,0},
                 {1,1,0,0},
                 {0,1,0,0},
                 {0,0,0,0}}};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////        FUNCTIONS FOR DRAW          /////////////////////////////
void DrawRect(int i, int j,int col){
//This function draws all the squares forming the pieces
setcolor(col);
//rectangle(20+20*(j-1),20+20*(i-1),20+20*j,20+20*i);//This line causes the blocks to be deleted when they are overlaid
rectangle(20+20*(j-1)+j,20+20*(i-1)+i,20+20*j+j,20+20*i+i);//This line is an excellent correction

}

void DrawScore(int s){
setcolor(g); settextstyle(5,0,3);sprintf(Sc, "%d",s); outtextxy(770,180,Sc);
}

void PintaMarco(){

    for(int i=0;i<32;i++){
        DrawRect(0,i,w);  DrawRect(21,i,w);
    }
    for(int i=0;i<22;i++){
        DrawRect(i,0,w);  DrawRect(i,31,w);
    }
    line(20*11+11,0,20*11+11,20*21+21); line(20*21+21,0,20*21+21,20*21+21);
    //zone next piece
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++)
        {
          DrawRect(2+i,34+j,8);
        }
    }
    //zone score and instruccions
    setcolor(g);
    settextstyle(2,0,6);
    outtextxy(690,10,"Next Piece");
    outtextxy(700,180,"Score: ");
    DrawScore(Score);//call function "DrawScore()"
    settextstyle(2,0,6);
    outtextxy(680,290,"Game Instriccions");
    settextstyle(2,0,5);
    outtextxy(680,320,"key Enter : Start Game");
    outtextxy(680,340,"key Up : rotate piece");
    outtextxy(680,360,"key Down : down piece");
    outtextxy(680,380,"key Right : move right piece");
    outtextxy(680,400,"key Left : move left piece");

    // 3 Areas
    settextstyle(2,0,6);
    setcolor(y);
    outtextxy(15,470,"here Yellow Pieces");
    setcolor(r);
    outtextxy(240,470,"here Red Pieces");
    setcolor(c);
    outtextxy(460,470,"here Cyan Pieces");
}

void ClearRect(int i,int j){
DrawRect(i,j,0);
}

void DrawPiece(int rot,int x,int y,int col){
   //delete previous piece
   for(int i=0;i<4;i++){
    for(int j=0;j<4;j++){
     if(CurrentPiece==1){  if(pO[rot0][i][j]!=0){ClearRect(p0i+i,p0j+j);};}
     if(CurrentPiece==2){  if(pI[rot0][i][j]!=0){ClearRect(p0i+i,p0j+j);};}
     if(CurrentPiece==3){  if(pS[rot0][i][j]!=0){ClearRect(p0i+i,p0j+j);};}
     if(CurrentPiece==4){  if(pZ[rot0][i][j]!=0){ClearRect(p0i+i,p0j+j);};}
     if(CurrentPiece==5){  if(pL[rot0][i][j]!=0){ClearRect(p0i+i,p0j+j);};}
     if(CurrentPiece==6){  if(pJ[rot0][i][j]!=0){ClearRect(p0i+i,p0j+j);};}
     if(CurrentPiece==7){  if(pT[rot0][i][j]!=0){ClearRect(p0i+i,p0j+j);};}

   }
   }
   //draw piece
   for(int i=0;i<4;i++){
    for(int j=0;j<4;j++){
       if(CurrentPiece==1){ if(pO[rot][i][j]!=0){DrawRect(x+i,y+j,col);};}
       if(CurrentPiece==2){ if(pI[rot][i][j]!=0){DrawRect(x+i,y+j,col);};}
       if(CurrentPiece==3){ if(pS[rot][i][j]!=0){DrawRect(x+i,y+j,col);};}
       if(CurrentPiece==4){ if(pZ[rot][i][j]!=0){DrawRect(x+i,y+j,col);};}
       if(CurrentPiece==5){ if(pL[rot][i][j]!=0){DrawRect(x+i,y+j,col);};}
       if(CurrentPiece==6){ if(pJ[rot][i][j]!=0){DrawRect(x+i,y+j,col);};}
       if(CurrentPiece==7){ if(pT[rot][i][j]!=0){DrawRect(x+i,y+j,col);};}
    }
   }
}

void DrawNextPiece(int col){
     //zone next piece
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++)
        {
          DrawRect(2+i,34+j,8);
        }
    }

    if(NextPiece==1){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++)
            {
               if(pO[0][i][j]==1)   DrawRect(2+i,34+j,col);
            }
        }
    }

    if(NextPiece==2){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++)
            {
               if(pI[0][i][j]==1)   DrawRect(2+i,34+j,col);
            }
        }
    }

    if(NextPiece==3){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++)
            {
               if(pS[0][i][j]==1)   DrawRect(2+i,34+j,col);
            }
        }
    }
     if(NextPiece==4){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++)
            {
               if(pZ[0][i][j]==1)   DrawRect(2+i,34+j,col);
            }
        }
    }

    if(NextPiece==5){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++)
            {
               if(pL[0][i][j]==1)   DrawRect(2+i,34+j,col);
            }
        }
    }

    if(NextPiece==6){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++)
            {
               if(pJ[0][i][j]==1)   DrawRect(2+i,34+j,col);
            }
        }
    }

    if(NextPiece==7){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++)
            {
               if(pT[0][i][j]==1)   DrawRect(2+i,34+j,col);
            }
        }
    }

}

void ReDrawArea(){
for(int i=0;i<20;i++)
  {
    for(int j=0;j<30;j++){
        if(Area[i][j]==1){ DrawRect(i+1,j+1,y);}
        if(Area[i][j]==2){ DrawRect(i+1,j+1,r);}
        if(Area[i][j]==3){ DrawRect(i+1,j+1,c);}
        if(Area[i][j]==0){ ClearRect(i+1,j+1);}

        }
    }
  //repaint line zone
  setcolor(w);
 line(20*11+11,0,20*11+11,20*21+21); line(20*21+21,0,20*21+21,20*21+21);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////      RANDOM PIECE AND COLOR     ////////////////////////////
 int RandomNum(int lim){
 return (1+rand()%(lim));//return between 1 and lim
 }

 int RandomColor(){
 int color=RandomNum(3);
 int ReturnColor=0;
 if(color==1){ReturnColor=y;}
 if(color==2){ReturnColor=r;}
 if(color==3){ReturnColor=c;}
 return ReturnColor;
 }
////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////   CHECK COLLISION,  UPDATE AREA, delete line complete.           ////////////////////////////
bool CheckCollision(int x,int y,int r){
    //x not is coordenate x is renglon y is columna
bool collision=false;//0=no collision, 1=col. down, 2=col. right, 3=col left
printf(" \n");

for(int i=0;i<4;i++)
{
    for(int j=0;j<4;j++)
    {
        if(CurrentPiece==1)
           {
                if(pO[r][i][j]==1)
                {
                    if(Area[x+i-1][y+j-1]!=0 || (x+i)==21 || (y+j)==0 || (y+j)>30)//collision down
                    {
                    collision=true;
                    } //end collison=1
                }
            }

        if(CurrentPiece==2)
           {
                if(pI[r][i][j]==1)
                {
                    if(Area[x+i-1][y+j-1]!=0 || (x+i)==21 || (y+j)==0 || (y+j)>30)//collision down
                    {
                    collision=true;
                    } //end collison=1
                }
            }

        if(CurrentPiece==3)
           {
                if(pS[r][i][j]==1)
                {
                    if(Area[x+i-1][y+j-1]!=0 || (x+i)==21 || (y+j)==0 || (y+j)>30)//collision down
                    {
                    collision=true;
                    } //end collison=1
                }
            }

        if(CurrentPiece==4)
           {
                if(pZ[r][i][j]==1)
                {
                    if(Area[x+i-1][y+j-1]!=0 || (x+i)==21 || (y+j)==0 || (y+j)>30)//collision down
                    {
                    collision=true;
                    } //end collison=1
                }
            }

        if(CurrentPiece==5)
           {
                if(pL[r][i][j]==1)
                {
                    if(Area[x+i-1][y+j-1]!=0 || (x+i)==21 || (y+j)==0 || (y+j)>30)//collision down
                    {
                    collision=true;
                    } //end collison=1
                }
            }

        if(CurrentPiece==6)
           {
                if(pJ[r][i][j]==1)
                {
                    if(Area[x+i-1][y+j-1]!=0 || (x+i)==21 || (y+j)==0 || (y+j)>30)//collision down
                    {
                    collision=true;
                    } //end collison=1
                }
            }

        if(CurrentPiece==7)
           {
                if(pT[r][i][j]==1)
                {
                    if(Area[x+i-1][y+j-1]!=0 || (x+i)==21 || (y+j)==0 || (y+j)>30)//collision down
                    {
                    collision=true;
                    } //end collison=1
                }
            }
    }
}


return collision;
}

void UpdateArea(int x, int y, int r,int col){

for(int i=0;i<4;i++)
{
    for(int j=0;j<4;j++)
    {      //if piece 1 es current
           if(CurrentPiece==1){
                if(pO[r][i][j]==1){

                        if(col==14){Area[x+i-1][y+j-1]=1;}
                        if(col==4){Area[x+i-1][y+j-1]=2;}
                        if(col==3){Area[x+i-1][y+j-1]=3;}

                        }
            }
            //if piece 2 es current
           if(CurrentPiece==2){
                if(pI[r][i][j]==1){
                       if(col==14){Area[x+i-1][y+j-1]=1;}
                       if(col==4){Area[x+i-1][y+j-1]=2;}
                       if(col==3){Area[x+i-1][y+j-1]=3;}

                }
            }
            //if piece 3 es current
           if(CurrentPiece==3){
                if(pS[r][i][j]==1){
                        if(col==14){Area[x+i-1][y+j-1]=1;}
                        if(col==4){Area[x+i-1][y+j-1]=2;}
                        if(col==3){Area[x+i-1][y+j-1]=3;}

                }
            }
            //if piece 4 es current
           if(CurrentPiece==4){
                if(pZ[r][i][j]==1){
                        if(col==14){Area[x+i-1][y+j-1]=1;}
                        if(col==4){Area[x+i-1][y+j-1]=2;}
                        if(col==3){Area[x+i-1][y+j-1]=3;}

                }
            }
            //if piece 5 es current
           if(CurrentPiece==5){
                if(pL[r][i][j]==1){
                       if(col==14){Area[x+i-1][y+j-1]=1;}
                       if(col==4){Area[x+i-1][y+j-1]=2;}
                       if(col==3){Area[x+i-1][y+j-1]=3;}

                }
            }
            //if piece 6 es current
           if(CurrentPiece==6){
                if(pJ[r][i][j]==1){
                       if(col==14){Area[x+i-1][y+j-1]=1;}
                       if(col==4){Area[x+i-1][y+j-1]=2;}
                       if(col==3){Area[x+i-1][y+j-1]=3;}

                }
            }
            //if piece 7 es current
           if(CurrentPiece==7){
                if(pT[r][i][j]==1){
                       if(col==14){Area[x+i-1][y+j-1]=1;}
                       if(col==4){Area[x+i-1][y+j-1]=2;}
                       if(col==3){Area[x+i-1][y+j-1]=3;}

                }
            }

    }
}

}

void AddTwoSquares(int p,int col){
//this function add 2 squares in other area color. in zone p not.
int column;
bool put=false;
if(p!=1 && p!=0){
    while(put==false){
        column=RandomNum(10)-1;
        for(int i=19;i>=0;i--){
          if(i==19 && Area[i][column]==0 )
          {
           Area[i][column]=col;put=true;break;
          }
          if(i!=19 && Area[i+1][column]!=0)
          {
           Area[i][column]=col;put=true;break;
          }
        }
    }
}
put=false;
if(p!=2 && p!=0){
    while(put==false){
        column=10+RandomNum(10)-1;
        for(int i=19;i>=0;i--){
          if(i==19 && Area[i][column]==0)
          {
            Area[i][column]=col;put=true;break;
          }
          if(i!=19 && Area[i+1][column]!=0 )
          {
           Area[i][column]=col;put=true;break;
          }
        }
    }
}
put=false;
if(p!=3 && p!=0){
    while(put==false){
        column=20+RandomNum(10)-1;
        for(int i=19;i>=0;i--){
          if(i==19 && Area[i][column]==0)
          {
            Area[i][column]=col;put=true;break;
          }
          if(i!=19 && Area[i+1][column]!=0 )
          {
           Area[i][column]=col;put=true;break;
          }
        }

    }
}

}

void ClearLine(int zone, int line){
if(zone==1){
        Score=Score+1;
    for(int i=line;i>0;i--)
    {
        for(int j=0;j<10;j++)
        {
            if(i<line){
                Area[i][j]=Area[i-1][j];
            }
        }
    }
}

if(zone==2){
     Score=Score+1;
      for(int i=line;i>0;i--)
    {
        for(int j=10;j<20;j++)
        {
            if(i<line){
                Area[i][j]=Area[i-1][j];
            }
        }
    }

}

if(zone==3){
     Score=Score+1;
      for(int i=line;i>0;i--)
    {
        for(int j=20;j<30;j++)
        {
            if(i<line){
                Area[i][j]=Area[i-1][j];
            }
        }
    }
}

DrawScore(Score);

}

void IfLineCompleteClear(int zone){
//check zona 1
if(zone==1){
    for(int i=0;i<20;i++){
      bool completei=true;
      for(int j=0;j<10;j++){
        if(Area[i][j]==0){completei=false; break;}
      }
      if(completei){ClearLine(1,i+1);}
    }
}

//check zona 2
if(zone==2){
    for(int i=0;i<20;i++){
      bool completei=true;
      for(int j=10;j<20;j++){
        if(Area[i][j]==0){completei=false; break;}
      }
      if(completei){ClearLine(2,i+1);}
    }
}

//check zona 3
if(zone==3){
    for(int i=0;i<20;i++){
      bool completei=true;
      for(int j=20;j<30;j++){
        if(Area[i][j]==0){completei=false; break;}
      }
      if(completei){ClearLine(3,i+1);}
    }
}





}

void AnalyzeArea(int x, int y,int r ,int col){
int ConMovPieces=0,NotPutIn=0,c;
//if(col==14){c=1;} if(col==4){c=2;}if(col==3){c=3;}

if(CurrentPiece==1)
{
   for(int i=0;i<4;i++)
   {
     for(int j=0;j<4;j++)
     {
       if(pO[r][i][j]==1)
         {
              if((y+j)<11 && col!=14){Area[x+i-1][y+j-1]=0;NotPutIn=1;c=1;}
              if((y+j)>10 &&(y+j)<21 && col!=4){Area[x+i-1][y+j-1]=0;NotPutIn=2;c=2;}
              if((y+j)>20 && col!=3){Area[x+i-1][y+j-1]=0;NotPutIn=3;c=3;}
              ConMovPieces=ConMovPieces+1;
              if(ConMovPieces==2){break;}//out bucle after 2
         }
     }
if(ConMovPieces==2){break;}//out bucle after 2
   }

}
// piece 2

if(CurrentPiece==2)
{
   for(int i=0;i<4;i++)
   {
     for(int j=0;j<4;j++)
     {
       if(pI[r][i][j]==1)
         {
              if((y+j)<11 && col!=14){Area[x+i-1][y+j-1]=0;NotPutIn=1;c=1;}
              if((y+j)>10 &&(y+j)<21 && col!=4){Area[x+i-1][y+j-1]=0;NotPutIn=2;c=2;}
              if((y+j)>20 && col!=3){Area[x+i-1][y+j-1]=0;NotPutIn=3;c=3;}
              ConMovPieces=ConMovPieces+1;
              if(ConMovPieces==2){break;}//out bucle after 2
         }
     }
if(ConMovPieces==2){break;}//out bucle after 2
   }

}
//piece 3

if(CurrentPiece==3)
{
   for(int i=0;i<4;i++)
   {
     for(int j=0;j<4;j++)
     {
       if(pS[r][i][j]==1)
         {
              if((y+j)<11 && col!=14){Area[x+i-1][y+j-1]=0;NotPutIn=1;c=1;}
              if((y+j)>10 &&(y+j)<21 && col!=4){Area[x+i-1][y+j-1]=0;NotPutIn=2;c=2;}
              if((y+j)>20 && col!=3){Area[x+i-1][y+j-1]=0;NotPutIn=3;c=3;}
              ConMovPieces=ConMovPieces+1;
              if(ConMovPieces==2){break;}//out bucle after 2
         }
     }
if(ConMovPieces==2){break;}//out bucle after 2
   }

}
// piece 4

if(CurrentPiece==4)
{
   for(int i=0;i<4;i++)
   {
     for(int j=0;j<4;j++)
     {
       if(pZ[r][i][j]==1)
         {
              if((y+j)<11 && col!=14){Area[x+i-1][y+j-1]=0;NotPutIn=1;c=1;}
              if((y+j)>10 &&(y+j)<21 && col!=4){Area[x+i-1][y+j-1]=0;NotPutIn=2;c=2;}
              if((y+j)>20 && col!=3){Area[x+i-1][y+j-1]=0;NotPutIn=3;c=3;}
              ConMovPieces=ConMovPieces+1;
              if(ConMovPieces==2){break;}//out bucle after 2
         }
     }
if(ConMovPieces==2){break;}//out bucle after 2
   }

}
//piece 5

if(CurrentPiece==5)
{
   for(int i=0;i<4;i++)
   {
     for(int j=0;j<4;j++)
     {
       if(pL[r][i][j]==1)
         {
              if((y+j)<11 && col!=14){Area[x+i-1][y+j-1]=0;NotPutIn=1;c=1;}
              if((y+j)>10 &&(y+j)<21 && col!=4){Area[x+i-1][y+j-1]=0;NotPutIn=2;c=2;}
              if((y+j)>20 && col!=3){Area[x+i-1][y+j-1]=0;NotPutIn=3;c=3;}
              ConMovPieces=ConMovPieces+1;
              if(ConMovPieces==2){break;}//out bucle after 2
         }
     }
    if(ConMovPieces==2){break;}//out bucle after 2
   }

}
//piece 6

if(CurrentPiece==6)
{
   for(int i=0;i<4;i++)
   {
     for(int j=0;j<4;j++)
     {
       if(pJ[r][i][j]==1)
         {
              if((y+j)<11 && col!=14){Area[x+i-1][y+j-1]=0;NotPutIn=1;c=1;}
              if((y+j)>10 &&(y+j)<21 && col!=4){Area[x+i-1][y+j-1]=0;NotPutIn=2;c=2;}
              if((y+j)>20 && col!=3){Area[x+i-1][y+j-1]=0;NotPutIn=3;c=3;}
              ConMovPieces=ConMovPieces+1;
              if(ConMovPieces==2){break;}//out bucle after 2
         }
     }
    if(ConMovPieces==2){break;}//out bucle after 2
   }

}
//piece 7

if(CurrentPiece==7)
{
   for(int i=0;i<4;i++)
   {
     for(int j=0;j<4;j++)
     {
       if(pT[r][i][j]==1)
         {
              if((y+j)<11 && col!=14){Area[x+i-1][y+j-1]=0;NotPutIn=1;c=1;}
              if((y+j)>10 &&(y+j)<21 && col!=4){Area[x+i-1][y+j-1]=0;NotPutIn=2;c=2;}
              if((y+j)>20 && col!=3){Area[x+i-1][y+j-1]=0;NotPutIn=3;c=3;}
              ConMovPieces=ConMovPieces+1;
              if(ConMovPieces==2){break;}//out bucle after 2
         }
     }
     if(ConMovPieces==2){break;}//out bucle after 2
   }

}

//this function draw and update two squares in others areas.
AddTwoSquares(NotPutIn,c);

if(y<11 )IfLineCompleteClear(1);
if(y>=11 && y<20)IfLineCompleteClear(2);
if(y>=20 )IfLineCompleteClear(3);


}




///////////////////////////////////////////////   MAIN MAIN MAIN      ////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
 int main()
{
initwindow(890, 520);
srand(time(NULL));//inicialize Random number
int CounTime=0;
PintaMarco();
//initialize random curren and next
CurrentPiece=RandomNum(7);
ColorPiece=RandomColor();
NextPiece=RandomNum(7);
NextColorPiece=RandomColor();
DrawPiece(0,pi,pj,ColorPiece);//show first piece
//wait key to start
getch();
StartGame=true;
DrawNextPiece(NextColorPiece);//show next piece

while (StartGame==true)//bucle game start
{
    Sleep(30);// 30ms es good frames per second
    CounTime=CounTime+30;

    if(NewPiece)
        {
            pi=1;pj=14;p0i=1;p0j=14;
            CurrentPiece=NextPiece;ColorPiece=NextColorPiece;
            NextPiece=RandomNum(7); NextColorPiece=RandomColor();
            DrawNextPiece(NextColorPiece);
            NewPiece=false;
        }


    if(kbhit()==1)
    {
            switch(getch())
            {
              case KEY_UP: // press key up
                if(CheckCollision(pi,pj,rot+1)){}
                else{if(rot<3){rot=rot+1;}
                     else{rot=0;}}
                 break;
              case KEY_LEFT: // press key left
                 if(CheckCollision(pi,pj-1,rot)  ){}
                 else {pj = pj-1;}
                 break;
              case KEY_RIGHT: // press key right
                  if(CheckCollision(pi,pj+1,rot) ){}
                  else{pj = pj+1;}
                 break;
              case KEY_DOWN: // press key down
                  if(CheckCollision(pi+2,pj,rot)){}
                  else{pi = pi+2;}
                 break;

            }
    }//end kbhit

     if(CounTime>=TimeMovPiece){CounTime=0; pi=pi+1;}//move down piece each "TimeMovePiece"->global variable declare.


     if(CheckCollision(pi,pj,rot))
       {
          pi=pi-1;
          DrawPiece(rot,pi,pj,ColorPiece);
          UpdateArea(pi,pj,rot,ColorPiece);//put new pieza in area
          AnalyzeArea(pi,pj,rot,ColorPiece);//put 2 colors other area, clear line complete
          ReDrawArea();
          NewPiece=true;
       }
      else{ DrawPiece(rot,pi,pj,ColorPiece);}

       //GAME OVER
      if(pi==1 && CheckCollision(pi,pj,rot)){
            StartGame=false;
            settextstyle(2,0,19);setcolor(14);
            outtextxy(220,200,"Game over");
      }

       p0i=pi;p0j=pj;rot0=rot;//save previous position and rotations, necessary for delete previous piece.
}//end bucle StartGame (while)

getch();
return 0;
}
