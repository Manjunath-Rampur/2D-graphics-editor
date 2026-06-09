#include <stdio.h>
#include <math.h>
#include <string.h>

#define WIDTH 80
#define HEIGHT 25
#define MAX_OBJECTS 50

// Shape Types
enum ShapeType {
    LINE = 1,
    RECTANGLE,
    TRIANGLE,
    CIRCLE
};

// Object Structure
typedef struct {
    int active;
    int type;

    int x1, y1;
    int x2, y2;

    int x3, y3;     // Triangle

    int radius;     // Circle

    char symbol;
} Object;

char canvas[HEIGHT][WIDTH];
Object objects[MAX_OBJECTS];

int isWithinBounds(int x, int y) {
    return (x >= 0 && x < WIDTH &&
            y >= 0 && y < HEIGHT);
}

void clearCanvas() {
    for(int i = 0; i < HEIGHT; i++) {
        for(int j = 0; j < WIDTH; j++) {
            canvas[i][j] = ' ';
        }
    }
}

void displayCanvas() {
    for(int i = 0; i < HEIGHT; i++) {
        for(int j = 0; j < WIDTH; j++) {
            printf("%c", canvas[i][j]);
        }
        printf("\n");
    }
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

void redrawAll() {

    clearCanvas();

    for(int i = 0; i < MAX_OBJECTS; i++) {

        if(!objects[i].active)
            continue;

        switch(objects[i].type) {

            case LINE:
                drawLine(
                    objects[i].x1,
                    objects[i].y1,
                    objects[i].x2,
                    objects[i].y2,
                    objects[i].symbol);
                break;

            case RECTANGLE:
                drawRectangle(
                    objects[i].x1,
                    objects[i].y1,
                    objects[i].x2,
                    objects[i].y2,
                    objects[i].symbol);
                break;

            case TRIANGLE:
                drawTriangle(
                    objects[i].x1,
                    objects[i].y1,
                    objects[i].x2,
                    objects[i].y2,
                    objects[i].x3,
                    objects[i].y3,
                    objects[i].symbol);
                break;

            case CIRCLE:
                drawCircle(
                    objects[i].x1,
                    objects[i].y1,
                    objects[i].radius,
                    objects[i].symbol);
                break;
        }
    }
}


int addObject(Object obj) {

    for(int i = 0; i < MAX_OBJECTS; i++) {

        if(!objects[i].active) {
            objects[i] = obj;
            objects[i].active = 1;
            return i;
        }
    }

    return -1;
}
void deleteObject(int id) {

    if(id >= 0 && id < MAX_OBJECTS)
        objects[id].active = 0;
}


int main() {

    memset(objects, 0, sizeof(objects));

    Object line = {
        1, LINE,
        2, 2,
        20, 10,
        0, 0,
        0,
        '*'
    };

    Object rect = {
        1, RECTANGLE,
        25, 3,
        45, 12,
        0, 0,
        0,
        '*'
    };

    Object tri = {
        1, TRIANGLE,
        55, 3,
        70, 10,
        60, 18,
        0,
        '*'
    };

    Object cir = {
        1, CIRCLE,
        15, 18,
        0, 0,
        0, 0,
        5,
        '*'
    };

    int lineID = addObject(line);
    int rectID = addObject(rect);
    int triID = addObject(tri);
    int circleID = addObject(cir);

    redrawAll();

    printf("Original Picture:\n\n");
    displayCanvas();

    printf("\nDeleting Rectangle...\n\n");
    deleteObject(rectID);

    redrawAll();
    displayCanvas();

}
