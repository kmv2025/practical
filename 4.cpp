#include <iostream>
#include <graphics.h>

using namespace std;

// Global variables for clipping window and coordinates
int xmin = 100, xmax = 500, ymin = 100, ymax = 500;
int arr[20], m, k;

// Function to clip a line segment from the left
void clipLeft(int x1, int y1, int x2, int y2) {
    if (x2 - x1) {
        m = (y2 - y1) / (x2 - x1);
    } else {
        m = 10000; // Infinite slope
    }

    if (x1 >= xmin && x2 >= xmin) {
        arr[k] = x2;
        arr[k + 1] = y2;
        k += 2;
    }
    if (x1 < xmin && x2 >= xmin) {
        arr[k] = xmin;
        arr[k + 1] = y1 + m * (xmin - x1);
        arr[k + 2] = x2;
        arr[k + 3] = y2;
        k += 4;
    }
    if (x1 >= xmin && x2 < xmin) {
        arr[k] = xmin;
        arr[k + 1] = y1 + m * (xmin - x1);
        k += 2;
    }
}

// Function to clip a line segment from the top
void clipTop(int x1, int y1, int x2, int y2) {
    if (y2 - y1) {
        m = (x2 - x1) / (y2 - y1);
    } else {
        m = 10000; // Infinite slope
    }

    if (y1 <= ymax && y2 <= ymax) {
        arr[k] = x2;
        arr[k + 1] = y2;
        k += 2;
    }
    if (y1 > ymax && y2 <= ymax) {
        arr[k] = x1 + m * (ymax - y1);
        arr[k + 1] = ymax;
        arr[k + 2] = x2;
        arr[k + 3] = y2;
        k += 4;
    }
    if (y1 <= ymax && y2 > ymax) {
        arr[k] = x1 + m * (ymax - y1);
        arr[k + 1] = ymax;
        k += 2;
    }
}

// Function to clip a line segment from the right
void clipRight(int x1, int y1, int x2, int y2) {
    if (x2 - x1) {
        m = (y2 - y1) / (x2 - x1);
    } else {
        m = 10000; // Infinite slope
    }

    if (x1 <= xmax && x2 <= xmax) {
        arr[k] = x2;
        arr[k + 1] = y2;
        k += 2;
    }
    if (x1 > xmax && x2 <= xmax) {
        arr[k] = xmax;
        arr[k + 1] = y1 + m * (xmax - x1);
        arr[k + 2] = x2;
        arr[k + 3] = y2;
        k += 4;
    }
    if (x1 <= xmax && x2 > xmax) {
        arr[k] = xmax;
        arr[k + 1] = y1 + m * (xmax - x1);
        k += 2;
    }
}

// Function to clip a line segment from the bottom
void clipBottom(int x1, int y1, int x2, int y2) {
    if (y2 - y1) {
        m = (x2 - x1) / (y2 - y1);
    } else {
        m = 10000; // Infinite slope
    }

    if (y1 >= ymin && y2 >= ymin) {
        arr[k] = x2;
        arr[k + 1] = y2;
        k += 2;
    }
    if (y1 >= ymin && y2 < ymin) {
        arr[k] = x1 + m * (ymin - y1);
        arr[k + 1] = ymin;
        arr[k + 2] = x2;
        arr[k + 3] = y2;
        k += 4;
    }
    if (y1 < ymin && y2 >= ymin) {
        arr[k] = x1 + m * (ymin - y1);
        arr[k + 1] = ymin;
        k += 2;
    }
}

int main() {
    int poly[20];
    int window1 = initwindow(800, 800); // Initialize graphics window
    int n, i;

    cout << "Enter the number of edges: " << endl; // User input for number of edges
    cin >> n;

    cout << "Enter the coordinates: " << endl; // User input for polygon coordinates
    for (i = 0; i < 2 * n; i++)  
        cin >> poly[i];

    poly[i]     = poly[0]; // Closing the polygon
    poly[i + 1] = poly[1];

    rectangle(xmin, ymax, xmax, ymin); // Draw clipping rectangle
    fillpoly(n, poly);                 // Fill the polygon
    delay(1000);                       // Delay for visibility
    cleardevice();                     // Clear the device

    k = 0; // Reset index for clipped coordinates

    for (i = 0; i < 2 * n; i += 2)
        clipLeft(poly[i], poly[i + 1], poly[i + 2], poly[i + 3]);

    n = k / 2; // Update number of vertices after clipping
    for (i = 0; i < k; i++)
        poly[i] = arr[i];

    poly[i]     = poly[0]; // Closing the polygon again
    poly[i + 1] = poly[1];

    k = 0;

    for (i = 0; i < 2 * n; i += 2)
        clipRight(poly[i], poly[i + 1], poly[i + 2], poly[i + 3]);

    n = k / 2;
    for (i = 0; i < k; i++)
        poly[i] = arr[i];

    poly[i]     = poly[0];
    poly[i + 1] = poly[1];

    k = 0;

    for (i = 0; i < 2 * n; i += 2)
        clipBottom(poly[i], poly[i + 1], poly[i + 2], poly[i + 3]);

    for (i = 0; i < k; i++)
        poly[i] = arr[i];

    rectangle(xmin, ymax, xmax, ymin); // Draw clipping rectangle again

    if (k)
        fillpoly(k / 2, poly); // Fill the clipped polygon

    system("pause"); // Wait for user input before closing
    return 0;       // End of program
}
