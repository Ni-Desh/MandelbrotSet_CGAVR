#include <GL/glut.h>
#include <complex.h>
#include <math.h>

// Fractal settings
int max_iter = 1000;  // Maximum iterations for Mandelbrot calculations
double minX = -2.5, maxX = 1.0; // X-axis boundaries
double minY = -1.0, maxY = 1.0; // Y-axis boundaries

// Function to compute if a point is in the Mandelbrot set
int mandelbrot(double real, double imag) {
    double complex c = real + imag * I;
    double complex z = 0.0 + 0.0 * I;
    int iter;

    for (iter = 0; iter < max_iter; iter++) {
        z = z * z + c;
        if (cabs(z) > 2.0) {
            return iter;
        }
    }

    return max_iter;
}

// Function to render the Mandelbrot fractal
void renderFractal() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Loop through pixels in the view window and calculate their Mandelbrot values
    for (int x = 0; x < 800; x++) {
        for (int y = 0; y < 800; y++) {
            double real = minX + (maxX - minX) * x / 800.0;
            double imag = minY + (maxY - minY) * y / 800.0;

            int value = mandelbrot(real, imag);

            // Color the pixel based on the iteration count
            float color = (float)value / max_iter;
            glColor3f(color, color, color);  // grayscale color based on iterations
            glBegin(GL_POINTS);
            glVertex2f(real, imag);  // Plot the point on the screen
            glEnd();
        }
    }

    glFlush();
    glutSwapBuffers();
}

// Timer function to animate the zoom effect
void timer(int value) {
    minX *= 1.1;
    maxX *= 1.1;
    minY *= 1.1;
    maxY *= 1.1;
    glutPostRedisplay();  // Redraw the scene after zooming in
    glutTimerFunc(100, timer, 0);  // Call timer again after 100 ms
}

// Initialize OpenGL settings
void initOpenGL() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set background color to black
    glOrtho(-2.5, 2.5, -2.5, 2.5, -1.0, 1.0); // Set the coordinate system
    glPointSize(1.0);  // Set point size for plotting
}

// Main function to set up the window and run the program
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Mandelbrot Fractal");

    initOpenGL();
    glutDisplayFunc(renderFractal);
    glutTimerFunc(100, timer, 0);  // Start the zooming animation
    glutMainLoop();

    return 0;
}

