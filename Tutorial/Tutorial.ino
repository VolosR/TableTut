#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);

int fromTop=40;
int width[4]={20,45,45,45};
int xpos[4]={3,26,74,122};
String lbl[4]={"","TMP","HUM","PRE"};

int data[8][3]={{3,5,8},
                {23,45,78},
                {12,47,87},
                {34,87,56},
                {23,45,78},
                {12,45,67},
                {2,0,1},
                {0,0,0}};

void setup() {
  tft.init();
  tft.fillScreen(TFT_BLACK);
  sprite.createSprite(170,320);

     //brightness
     ledcSetup(0, 10000, 8);
     ledcAttachPin(38, 0);
     ledcWrite(0, 140); 
}

void draw()
  {
    sprite.fillSprite(TFT_BLACK); 
    sprite.setTextDatum(4); 
    sprite.setTextColor(TFT_BLACK,TFT_ORANGE);
    for(int i=0;i<4;i++)
    {
      sprite.fillRect(xpos[i],fromTop-20,width[i],18,TFT_ORANGE);
      sprite.drawString(lbl[i],xpos[i]+width[i]/2,fromTop-20+9,2); 
    }


    sprite.setTextColor(TFT_BLACK,TFT_SILVER);
 

    for(int r=0;r<8;r++)
    {
      for(int c=0;c<4;c++)
      {
        sprite.fillRect(xpos[c],fromTop+(r*20),width[c],18,TFT_SILVER);
        if(c==0)
          {
            sprite.drawString(String(r+1),xpos[c]+10,fromTop+(r*20)+9,2);
          }
          else
          {
            sprite.drawString(String(data[r][c-1]),xpos[c]+22,fromTop+(r*20)+9,2);
          }
      }
    }

    sprite.pushSprite(0,0);
  }

void loop() {
  draw();
}