#include "LedControl.h"


LedControl lc=LedControl(12,11,10,1); 

   
     int size1=4;
      int s[64][2]={{3,0},{2,0},{1,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},
      {0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},
      {0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}; 
    
  
  char curr_Move='R';
  char next_Move;
  int vx,vy;
  int  x= random(8);
   int y= random(8);
   int tim=500,inc=1;
   char d=0b10000000,set='L',UI;
   


  void update1()
  {
    
    {
      lc.setLed(0,s[size1-1][1],s[size1-1][0],0);
     for(int i=63;i>0;i--)
     {s[i][0]=s[i-1][0];
     s[i][1]=s[i-1][1];}
      
   
    }
  }
    void move1(int a[],char cM)
  {
    
    switch(cM)
    {
        case 'L':
           {
           if(a[0]==0)
           {// gameOver();
            a[0]=7;}
           else {a[0]--;}
           break;
           }
        case 'R':
           {
             if(a[0]==7)
             { // gameOver();
              a[0]=0;  }
             else
               { a[0]++;}
             break;
           }
        case 'U':
            {
              if(a[1]==0)
               { // gameOver(); 
                a[1]=7;}
              else
              { a[1]--;}
              break;
            }
        case 'D' :
             {
               if(a[1]==7)
                 { //gameOver();
                  a[1]=0;   }
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
      pinMode(0,INPUT);
      setDiff();
      {
        if(inc==1)
        {tim=500;}
        
        else if(inc==2)
        {tim=400;}
        
        else if(inc==3)
        {tim=300;}
        
        else if(inc==4)
        {tim=150;
          }
        
        else if(inc==5)
        {tim=50;}

     } 
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
      return 'X';
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
char digInp()
{
  int x=digitalRead(0);
  if(x==0)
  {
    return 's';
    }
  else
  {
    return 'a';
    }
  
  
  }
 
  void setDiff()
  {
    lc.clearDisplay(0);
    while(1){
      
      
      lc.setColumn(0,inc-1,255);
      delay(500);
      set=userInp();
    if(set=='R')
    {
       if(inc<5)
         { inc++;}
      }
      else if(set=='L')
      {
        if(inc>1)
           {inc--;}
        }
        
        if(digInp()=='s')
        {  
          lc.clearDisplay(0);
          return;
          
          }
          lc.clearDisplay(0);
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
  /*lc.setLed(0,x,y,0);
  delay(30);
  lc.setLed(0,x,y,1);
  delay(30);
   lc.setLed(0,x,y,0);
  delay(30);
   lc.setLed(0,x,y,1);
  delay(30);*/
  UI=userInp();
  if(UI=='X')
  {next_Move=curr_Move;}
  else
  {next_Move=UI;}
  //next_Move='D';
  check_Move(curr_Move,next_Move);
  checkFoodEaten();
  check_Over();
  
}
void gameOver()              //to display game over ;
{
  int alph[8][8]={{60,102,96,110,102,102,60,0},
                {24,60,102,126,102,102,102,0},
                {99,119,127,107,99,99,99,0},
                {126,96,96,120,96,96,126,0},
                { 60,102,102,102,102,102,60,0},
                {102,102,102,102,102,60,24,0},
                {126,96,96,120,96,96,126,0},
                {124,102,102,124,120,108,102,0}};
   for(int i=0;i<8;i++)
   {    lc.clearDisplay(0);
          for(int j=0;j<8;j++)
          {
            lc.setRow(0,j,alph[i][j]);
            }
            delay(200);
            
           
    }  
    lc.clearDisplay(0);
   exit(0);
}
  
  

void check_Over()
{
  int flag=0;
  for(int i=4;i<size1;i++)
  {
    if((s[0][1]==s[i][1])&&(s[0][0]==s[i][0]))
    {
      flag=1;
      break;
      }
  }   
   if(flag==1)
    {
      showSnake();
      delay(100);
      lc.clearDisplay(0);
      showSnake();
      delay(100);
      lc.clearDisplay(0);
      showSnake();
      delay(100);
      lc.clearDisplay(0);
      gameOver();
      }
    
      
}

void loop() {
  showSnake();
  delay(tim);
  next();
  curr_Move=next_Move;

}
