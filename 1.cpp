#include <cmath>
#include <cstdlib>
#include <graphics.h>
#include <iostream>

using namespace std;

// Function to draw a line using Bresenham's algorithm
void bresenhamLine(int x0, int y0, int x1, int y1, int val) {
    // Check if the endpoints are the same
    if (x0 == x1 && y0 == y1) {
        putpixel(x1, y1, val);
    } else {
        int dx = x1 - x0; // Change in x
        int dy = y1 - y0; // Change in y

        float m = float(dy) / float(dx); // Calculate slope

        // Check if the slope is valid
        if (m >= 1 || m <= 0) {
            cout << "ERROR: Slope must be between 0 and 1." << endl;
            exit(1);
        }

        // Bresenham's algorithm initialization
        int d = 2 * dy - dx;
        int del_E = 2 * dy;
        int del_NE = 2 * (dy - dx);

        int x = x0;
        int y = y0;
        putpixel(x, y, val); // Plot the initial point

        // Loop through each pixel along the line
        while (x < x1) {
            if (d <= 0) {
                d += del_E; // Move east
            } else {
                d += del_NE; // Move northeast
                y += 1;      // Increment y
            }
            x += 1; // Increment x
            putpixel(x, y, val); // Plot the current point
        }
    }
}

int main(void) {
    int x0, y0, x1, y1;

    // Input endpoints from the user
    cout << "Enter Left Endpoint (x0 y0): ";
    cin >> x0 >> y0;
    cout << "Enter Right Endpoint (x1 y1): ";
    cin >> x1 >> y1;

    cout << "Drawing Line..." << endl;

    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL); // Initialize graphics mode

    bresenhamLine(x0, y0, x1, y1, WHITE); // Draw the line

    delay(5000); // Wait for 5 seconds before closing
    closegraph(); // Close graphics mode

    cout << "Finished..." << endl;

    return 0; // End of program
}
//50 50
//150 100
