#include "LedControl.h"


LedControl lc=LedControl(12,11,10,1); 
/*class Snake
{
  public :
  int i;
  int j;
  
  Snake1(int x,int y)
  {
    i=x;
    j=y;
  }
   void rePosition(int x,int y)
  {
    i=x;
    j=y;
  }
   int x_C()
   {
     return i;
   }
   int y_C()
   {
     return j;
   }
}*/
     /* Snake s[4];
      s[0].Snake1(0,4);
      s[1].Snake1(0,5);
      s[2].Snake1(0,6);
      s[3].Snake1(0,7);*/
     int size1=4;
      int s[64][2]={{3,0},{2,0},{1,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},
      {0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},
      {0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}; 
     // int x,y;
      // head=>s[0];
// int h[2]={3,0};
// int b1[2]={2,0};
// int b2[2]={1,0};
// int t[2]={0,0};
  
  char curr_Move='R';
  char next_Move;
  int vx,vy;
  int  x= random(8);
   int y= random(8);


  void update1()
  {
    
    {
      lc.setLed(0,s[size1-1][1],s[size1-1][0],0);
     for(int i=63;i>0;i--)
     {s[i][0]=s[i-1][0];
     s[i][1]=s[i-1][1];}
      
     /* lc.setLed(0,t[1],t[0],0);
       t[0]=b2[0];
      t[1]=b2[1];
       b2[0]=b1[0];
      b2[1]=b1[1];
       b1[0]=h[0];
      b1[1]=h[1];*/
      
    }
  }
    void move1(int a[],char cM)
  {
    
    switch(cM)
    {
        case 'L':
           {
           if(a[0]==0)
           { a[0]=7;}
           else {a[0]--;}
           break;
           }
        case 'R':
           {
             if(a[0]==7)
             {  a[0]=0;  }
             else
               { a[0]++;}
             break;
           }
        case 'U':
            {
              if(a[1]==0)
               { a[1]=7;}
              else
              { a[1]--;}
              break;
            }
        case 'D' :
             {
               if(a[1]==7)
                 { a[1]=0;   }
               else
                { a[1]++;}
               break;
             }
    }
  }
  void turn(char nM)      //nM =>next_Move;
  {
    update1();
   // move1(h, nM);    
    move1(s[0],nM);
  }
  void check_Move(char cM,char nM)
  {
    if((cM=='R')||(cM=='L'))
    {
      if((nM=='R')||(nM=='L'))
      {
        update1();
       // move1(h,cM); 
        move1(s[0],cM);
      }
      else {
        turn(nM);
      }
    }
    else
    {    
           if((nM=='U')||(nM=='D'))
      {
        update1();
       // move1(h,cM);  
        move1(s[0],nM);
      }
      else {
        turn(nM);
      } 
    
    }
 }
  
void setup() {
  // put your setup code here, to run once:
      
      lc.shutdown(0,false);  // Wake up displays
      lc.setIntensity(0,5);  // Set intensity levels
      lc.clearDisplay(0);
      pinMode(A0,INPUT);
      pinMode(A1,INPUT);
}
void showSnake()
{
  
  {    for(int i=0;i<size1;i++)
          {
             lc.setLed(0,s[i][1],s[i][0],1);
          }
          
   /* lc.setLed(0,h[1],h[0],1);
    
    lc.setLed(0,b1[1],b1[0],1);
    
    lc.setLed(0,b2[1],b2[0],1);
    
    lc.setLed(0,t[1],t[0],1);*/
    
   // delay(500);
    }
    delay(500);
   // lc.clearDisplay(0);
    
  
  
}
char userInp()
{
  vx=analogRead(A0);
  vy=analogRead(A1);
  if((vy>750))
  {
    return 'D';
    }
 else if((vy<250))
  {
    return 'U';
    }
 else if((vx>850))
  {
    return 'R';
    }
    else if((vx<250))
  {
    return 'L';
    }
    else{
      return curr_Move;
      }
  
}
void food()
{
 
 lc.setLed(0,x,y,1);
}
void checkFoodEaten()
{
  if((x==s[0][1])&&(y==s[0][0]))
  {
     lc.setLed(0,x,y,0);
  delay(100);
  size1++;
   regenerate(); 
   }
   
}
void regenerate()
{
    x= random(8);
    y= random(8);

  }

void next()
{
  food();
  lc.setLed(0,x,y,0);
  delay(30);
  lc.setLed(0,x,y,1);
  delay(30);
   lc.setLed(0,x,y,0);
  delay(30);
   lc.setLed(0,x,y,1);
  delay(30);
  next_Move=userInp();
  //next_Move='D';
  check_Move(curr_Move,next_Move);
  checkFoodEaten();
  
}

void loop() {
  showSnake();
  next();
  curr_Move=next_Move;

}
