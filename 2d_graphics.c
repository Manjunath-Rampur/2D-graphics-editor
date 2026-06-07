#include <stdio.h>
#include <math.h>
#include <string.h>

#define WIDTH 80
#define HEIGHT 25
#define MAX_OBJECTS 50

char canvas[HEIGHT][WIDTH];

int isWithinBounds(int x, int y) {
    return (x >= 0 && x < WIDTH &&
            y >= 0 && y < HEIGHT);
}


void setPixel(int x, int y, char sym) {
    if(isWithinBounds(x, y)) {
        canvas[y][x] = sym;
    }
}

void drawLine(int x1, int y1, int x2, int y2, char sym)
{
    int dx = x2 - x1;
    int dy = y2 - y1;

    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float xInc = (float)dx / steps;
    float yInc = (float)dy / steps;

    float x = x1;
    float y = y1;

    for (int i = 0; i <= steps; i++)
    {
        int px = (int)(x + 0.5f);
        int py = (int)(y + 0.5f);

        if (isWithinBounds(px, py))
            canvas[py][px] = sym;

        x += xInc;
        y += yInc;
    }
}
void drawRectangle(int x1, int y1,
                   int x2, int y2,
                   char sym) {

    drawLine(x1, y1, x2, y1, sym);
    drawLine(x2, y1, x2, y2, sym);
    drawLine(x2, y2, x1, y2, sym);
    drawLine(x1, y2, x1, y1, sym);
}

void drawTriangle(int x1, int y1,
                  int x2, int y2,
                  int x3, int y3,
                  char sym) {

    drawLine(x1, y1, x2, y2, sym);
    drawLine(x2, y2, x3, y3, sym);
    drawLine(x3, y3, x1, y1, sym);
}

void drawCircle(int h, int k, int r, char sym)
{
    int x, y;

    for (y = 0; y < HEIGHT; y++)
    {
        for (x = 0; x < WIDTH; x++)
        {
            int value = (x - h) * (x - h) +
                        (y - k) * (y - k);

            /* Allow small error because of integer rounding */
            if (abs(value - r * r) <= r)
            {
                canvas[y][x] = sym;
            }
        }
    }
}
int main(){
    for(int i=0;i<WIDTH;i++){
        for(int j=0;j<HEIGHT;j++){
            canvas[j][i]=' ';
        }
    }
    //drawLine(0,0,10,10,'*');
    //drawTriangle(1,1,1,7,7,1,'*');
    //drawRectangle(1,1,10,10,'*');
    drawCircle(9,8,6,'*');
    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            printf("%c", canvas[i][j]);
        }
        printf("\n");
    }
    return 0;
}
