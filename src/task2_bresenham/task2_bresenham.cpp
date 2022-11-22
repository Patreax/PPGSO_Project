// Task 3 - Implement Bresenham drawing alg.
//        - Draw a star using lines
//        - Make use of std::vector to define the shape
#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>

#include <ppgso/ppgso.h>

// Size of the framebuffer
const unsigned int SIZE = 512;

struct Point {
    int x, y;
};

// Bresenham drawing algorithm
void drawLine(ppgso::Image &framebuffer, Point &from, Point &to) {
    // TODO: Implement Bresenham drawing algorithm

    if(from.x > to.x){
        Point temp = from;
        from = to;
        to = temp;
    }

    int x = from.x;
    int y = from.y;
    int e = -(to.x - from.x);
    int dx = abs(to.x - from.x);
    int dy = abs(to.y - from.y);

    bool downWard = true;
    if(to.y > from.y)
        downWard = true;
    else
        downWard = false;

    if(dx >= dy){
//        std::cout << "Podla x" << std::endl;
        while (x <= to.x) {
            framebuffer.setPixel(x, y, 250, 250, 250);
            x += 1;
            if(downWard)
                e += 2 * (to.y - from.y);
            else
                e -= 2 * (to.y - from.y);
            if (e > 0) {
                if(downWard)
                    y += 1;
                else
                    y -= 1;
                e -= 2 * (to.x - from.x);
            }
        }
    } else {
//        std::cout << "Podla y" << std::endl;
        if (downWard) {
            while (y <= to.y) {
                framebuffer.setPixel(x, y, 250, 250, 250);
                y += 1;
                e += 2 * (to.x - from.x);

                if (e > 0) {
                    x += 1;
                    e -= 2 * (to.y - from.y);
                }
            }
        } else {
            while (y >= to.y) {
                framebuffer.setPixel(x, y, 250, 250, 250);
                y -= 1;
                e += 2 * (to.x - from.x);
                if (e > 0) {
                    x += 1;
                    e -= 2 * (to.y - from.y);
                }
            }
        }
    }
}

int main() {
    // Use ppgso::Image as our framebuffer
    ppgso::Image framebuffer(SIZE, SIZE);

    // TODO: Generate star points
    // points to generate five-sided polygon
    std::vector<Point> points;
    Point point1 = *new Point();
    point1.x = 150;
    point1.y = 500;

    Point point2 = *new Point();
    point2.x = 100;
    point2.y = 450;

    Point point3 = *new Point();
    point3.x = 200;
    point3.y = 400;

    Point point4 = *new Point();
    point4.x = 300;
    point4.y = 450;

    Point point5 = *new Point();
    point5.x = 250;
    point5.y = 500;

    points.push_back(point1);
    points.push_back(point2);
    points.push_back(point3);
    points.push_back(point4);
    points.push_back(point5);
    points.push_back(point1);

    drawLine(framebuffer, point1, point2);
//    drawLine(framebuffer, point2, point3);
//    drawLine(framebuffer, point3, point4);
//    drawLine(framebuffer, point4, point5);
//    drawLine(framebuffer, point5, point1);

    // Draw lines
//    for (unsigned int i = 0; i < points.size() - 1; i++)
//        drawLine(framebuffer, points[i], points[i + 1]);

    // Save the result
    std::cout << "Generating task2_bresenham.bmp file ..." << std::endl;
    ppgso::image::saveBMP(framebuffer, "task2_bresenham.bmp");

    std::cout << "Done." << std::endl;
    return EXIT_SUCCESS;
}

