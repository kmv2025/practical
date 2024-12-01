#include <iostream>
#include <graphics.h>

using namespace std;

int main() {
    int c, r, xc, yc;

    // Input center coordinates and radius of the circle
    cout << "Enter the center coordinates of the circle: ";
    cin >> xc >> yc;
    cout << "Enter the radius of the circle: ";
    cin >> r;

    // Initial values for Bresenham's circle algorithm
    int x = 0;
    int y = r;
    int p = 1 - r; // Decision parameter

    int gd = DETECT, gMode;
    initgraph(&gd, &gMode, NULL); // Initialize graphics mode

    // Draw the circle using Bresenham's algorithm
    do {
        // Plotting the points in all octants
        putpixel(x + xc, y + yc, 2);   // Octant 1
        putpixel(xc + x, yc - y, 2);   // Octant 2
        putpixel(xc - x, yc - y, 2);   // Octant 3
        putpixel(xc + y, yc + x, 2);   // Octant 4
        putpixel(xc + y, yc - x, 2);   // Octant 5
        putpixel(xc - x, yc + y, 2);   // Octant 6
        putpixel(xc - y, yc + x, 2);   // Octant 7
        putpixel(xc - y, yc - x, 2);   // Octant 8

        // Update decision parameter and coordinates
        if (p < 0) {
            x = x + 1;                  // Move to next point in x direction
            p = p + 2 * x + 1;          // Update decision parameter
        } else {
            x = x + 1;                  // Move to next point in x direction
            y = y - 1;                  // Move down in y direction
            p = p + 2 * x - 2 * y + 1;  // Update decision parameter
        }
    } while (x <= y); // Continue until we reach the midpoint

    delay(10000); // Wait for a while before closing
    closegraph(); // Close graphics mode

    return 0; // End of program
}
