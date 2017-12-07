#include "LedControl.h"   /*Install this library by searching for "LEDControl" in ARDUINO application> Sketch >> Include Library >> 
                                Manage Libraries.It is "LED Control" by Eberhard Fahle.It is a library for Max7219 LED display Driver*/

LedControl lc=LedControl(12,11,10,1);   //To set the LED Controls.


     int size1=4;              //Setting an initial size for the Snake.

      int s[64][2]={{3,0},{2,0},{1,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},
      {0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},
      {0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}; 
    
  
  char curr_Move='R';    // Initially the Snake is set to move in Right Direction.
  char next_Move;
  int vx,vy;                   // Variables to read values from Analog Input by the JoyStick.
  int  x= random(8);            // x,y are used to set co-ordinates for Food for Snake.
   int y= random(8);


  void update1()                                   //This function sets the every following segment of the snake to its leading segment
  {
    
    
      lc.setLed(0,s[size1-1][1],s[size1-1][0],0);
    
      for(int i=63;i>0;i--)
         { 
             s[i][0]=s[i-1][0];
             s[i][1]=s[i-1][1];
          }
  }
    

void move1(int a[],char cM)                      //To move the head segment in a desired direction.
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

 
void turn(char nM)           //To do a Turn ,by turning the head.
  {
    update1();
      
    move1(s[0],nM);
  }


  void check_Move(char cM,char nM)       // To check whether the input move by user is a valid move.
  {
    if((cM=='R')||(cM=='L'))
    {
      if((nM=='R')||(nM=='L'))
      {
        update1();
        
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
        
        move1(s[0],nM);
      }
      else {
        turn(nM);
      } 
    
    }
 }
  
void setup() {
  
      
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
          
   }
    delay(500);
  
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
  
  lc.setLed(0,x,y,0);             //Flashing the food.
  delay(30);
  lc.setLed(0,x,y,1);
  delay(30);
   lc.setLed(0,x,y,0);
  delay(30);
   lc.setLed(0,x,y,1);
  delay(30);
  
  
  next_Move=userInp();
  
  check_Move(curr_Move,next_Move);
  
  checkFoodEaten();
  
}

void loop() 
{
  showSnake();
  
  next();
  
  curr_Move=next_Move;

}
