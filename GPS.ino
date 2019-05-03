#include <Arduino.h>

#define RXD2 16
#define BUFFER_SIZE 200
char buf[BUFFER_SIZE];
char buf2[BUFFER_SIZE];

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600,SERIAL_8N1, RXD2);

}

void loop() 
{
  String out = "";
  int i = 0;
  buf[BUFFER_SIZE-1]=NULL;
  while ( Serial2.available() && i<BUFFER_SIZE-1)
  {
    buf[i++] = char(Serial2.read());
    
  }
  char * GGAstart=NULL;
  for (int j = 5;j<i;j++)
    {
      if(buf[j-5]=='$'&&
         buf[j-4]=='G'&&
         buf[j-3]=='P'&&
         buf[j-2]=='G'&&
         buf[j-1]=='G'&&
         buf[j]=='A')
         {
           GGAstart = buf+1+j;
         }
      
    }
    if(GGAstart !=NULL && GGAstart!=buf+BUFFER_SIZE)
    {
        int GGAend = 0;
     
        int commas = 0;  
        while(GGAstart + GGAend != buf+BUFFER_SIZE && GGAstart[GGAend] != NULL && commas<8)
        {
         if(GGAstart[GGAend] =='\0') break;
         if(GGAstart[GGAend++] ==',') commas++;
         
        }
        if (commas==8)
        {
          memcpy(buf2,GGAstart,GGAend);
          buf2[GGAend]='\0';
          Serial.println(buf2);
        }
        
    }

}
  
