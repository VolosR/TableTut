#include <TFT_eSPI.h>
#include "Noto.h"
#include "bigFont.h"
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);

int width[4]={20,45,45,45};
int xpos[4]={3,26,74,122};
int fromTop=60;
unsigned short col[2]={0x563F,0xB73F};
unsigned short orange=0xCC40;
String lbls[4]={"","TMP","HUM","PRE"};

float data[8][3]={{2.34,3.45,1.56},
                  {23.5,1.02,4.5},
                  {3.4,12.56,6.78},
                  {0,4,5.67},
                  {23.5,1.02,4.5},
                  {2.34,3.45,1.56},
                  {1.45,5.67,3.98},
                  {45,6,12.5}};

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
    sprite.loadFont(Noto);

    sprite.setTextColor(TFT_WHITE,TFT_BLACK);
    sprite.drawString("TABLE : WEATHER ",74,24);
    sprite.setTextColor(TFT_WHITE,orange);
    for(int i=0;i<4;i++)
    {
    sprite.fillRect(xpos[i],fromTop-20,width[i],18,orange);
    sprite.drawString(lbls[i],xpos[i]+width[i]/2,fromTop-20+9);
    } 

    for(int r=0;r<8;r++)
    for(int c=0;c<4;c++)
    {
    sprite.fillRect(xpos[c],fromTop+(r*20),width[c],18,col[c%2]);
    sprite.setTextColor(TFT_BLACK,col[c%2]);
      if(c==0)
      sprite.drawString(String(r+1),xpos[c]+10,fromTop+(r*20)+9,2);
      else
      sprite.drawString(String(data[r][c+1]),xpos[c]+width[c]/2,fromTop+(r*20)+9,2);
    }
    sprite.unloadFont();
    sprite.loadFont(bigFont);
    sprite.setTextColor(0x94B2,TFT_BLACK);
    sprite.drawString("Table",84,270);
    sprite.unloadFont();

    sprite.pushSprite(0,0);
  }

void loop() {
  draw();
}