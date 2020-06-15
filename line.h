#ifndef LINE_H
#define LINE_H
#include<cmath>


int height = 768;
int width = 1024;

float camD = 0.84; 
int roadW = 2000; 
int segL = 200; 

class Line
{
private:
    float x,y,z; 
    float X,Y,W; 
    float curve; 
    float scale;
    float spriteX; 
    float coinX;
    sf::Sprite sprite;
    sf::FloatRect texture_rect;
    sf::Sprite coin;
    sf::FloatRect coin_texture;

public:
    Line()
    {
        coinX=spriteX=curve=x=y=z=0;
    }

    ~Line() {}


void projectToScreen(int camX, int camY, int camZ)
    {
        scale = camD/(z-camZ);
        X = (1 + scale*(x - camX)) * width/2;
        Y = (1 - scale*(y - camY)) * height/2;
        W = scale * roadW * width/2;
    }

void drawSprite(sf::RenderWindow &app)
{
    sf::Sprite s = sprite;
    int w = s.getTextureRect().width;
    int h = s.getTextureRect().height;

    float destX = X + scale * spriteX * width/2;
    float destY = Y;
    float destW = w * W/266;
    float destH = h * W/266;

    destX += destW * spriteX;
    destY += destH * (-1);

    s.setTextureRect(sf::IntRect(0,0,w,h-h/destH));
    s.setScale(destW/w,destH/h);
    s.setPosition(destX,destY);

    texture_rect=s.getGlobalBounds();

    app.draw(s);
}

sf::FloatRect getObstacleBounds()
{
    return texture_rect;
}

void drawCoin(sf::RenderWindow &app)
{
    sf::Sprite s = coin;
    int w = s.getTextureRect().width;
    int h = s.getTextureRect().height;

    float destX = X + scale * coinX * width/2;
    float destY = Y-2;
    float destW = w * W/266;
    float destH = h * W/266;

    destX += destW * coinX;
    destY += destH * (-1);

    s.setTextureRect(sf::IntRect(0,0,w,h-h/destH));
    s.setScale(destW/w,destH/h);
    s.setPosition(destX,destY);

    coin_texture=s.getGlobalBounds();

    app.draw(s);
}

sf::FloatRect getCoinBounds()
{
    return coin_texture;
}

    float gety() {return y;}
    float getX() {return X;}
    float getY() {return Y;}
    float getW() {return W;}
    float getCurve() {return curve;}

    friend void generateLines();
    friend void generateObstacles(sf::Sprite[]);
    friend void generateCoins(sf::Sprite&);
};


#endif // LINE_H
