#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

const int MAX_X = 800, MAX_Y = 800;
const int N = 10000;

float randomFloat(int max_val) {
    return static_cast<float>(rand() % max_val);
}

void drawLine(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;
    while (true) {
        glVertex2i(x1, y1);
        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

void render() {
    srand(time(0));
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    clock_t start = clock();
    for (int i = 0; i < N; i++) {
        float x1 = randomFloat(MAX_X), y1 = randomFloat(MAX_Y);
        float x2 = randomFloat(MAX_X), y2 = randomFloat(MAX_Y);
        int ix1 = static_cast<int>(x1 + 0.5), iy1 = static_cast<int>(y1 + 0.5);
        int ix2 = static_cast<int>(x2 + 0.5), iy2 = static_cast<int>(y2 + 0.5);
        drawLine(ix1, iy1, ix2, iy2);
    }
    clock_t end = clock();
    double time_taken = double(end - start) / CLOCKS_PER_SEC;
    cout << "Time taken: " << time_taken << " seconds" << endl;
    glEnd();
}

int main() {
    if (!glfwInit()) return -1;
    GLFWwindow* window = glfwCreateWindow(MAX_X, MAX_Y, "Line Drawing", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) return -1;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, MAX_X, 0.0, MAX_Y, -1.0, 1.0);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(2.0);
    while (!glfwWindowShouldClose(window)) {
        render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}