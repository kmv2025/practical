#include <iostream>
#include <graphics.h>
#include <cmath>

using namespace std;

int main() {
    int tx = 2, ty = 5; // Translation factors
    int window1 = initwindow(800, 800); // Initialize graphics window
    int i, j, k;
    float P[2][3]; // Array to hold the coordinates of the line in homogeneous form

    // Input coordinates for the line
    cout << "Enter the coordinates of the line (x1 y1 x2 y2): " << endl;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            cin >> P[i][j];
            P[i][2] = 1; // Homogeneous coordinate
        }
    }

    // Draw the original line
    line(P[0][0], P[0][1], P[1][0], P[1][1]);
    delay(7000);

    float pp[2][3] = {0}; // Array for transformed coordinates
    int ch;

    do {
        cout << "Enter the 2D transformation:" << endl;
        cout << "1. Translation\n2. Shearing\n3. Reflection\n4. Rotation\n5. Scaling\n6. Exit" << endl;
        cin >> ch;

        switch (ch) {
            case 1: { // Translation
                cout << "Enter the translating factors (tx ty): ";
                cin >> tx >> ty;
                int T[3][3] = {{1, 0, 0},
                               {0, 1, 0},
                               {tx, ty, 1}};

                // Apply transformation
                for (i = 0; i < 2; i++) {
                    for (j = 0; j < 3; j++) {
                        pp[i][j] = 0; // Initialize transformed coordinates
                        for (k = 0; k < 3; k++) {
                            pp[i][j] += P[i][k] * T[k][j];
                        }
                    }
                }
                line(pp[0][0], pp[0][1], pp[1][0], pp[1][1]);
                system("pause");
                break;
            }
            case 2: { // Shearing
                int sh;
                char ax;
                cout << "Enter the shearing axis (x/y): ";
                cin >> ax;
                cout << "Enter the shearing factor: ";
                cin >> sh;

                int T[3][3] = { {1, 0, 0}, {0, 1, 0}, {0, 0, 1} };
				if (ax == 'x') {
    				T[0][1] = sh; // Shearing along x-axis
				} else if (ax == 'y') {
    				T[1][0] = sh; // Shearing along y-axis
				}
				
				// Apply transformation
                for (i = 0; i < 2; i++) {
                    for (j = 0; j < 3; j++) {
                        pp[i][j] = 0; // Initialize transformed coordinates
                        for (k = 0; k < 3; k++) {
                            pp[i][j] += P[i][k] * T[k][j];
                        }
                    }
                }
                line(pp[0][0], pp[0][1], pp[1][0], pp[1][1]);
                system("pause");
                break;
            }
            case 3: { // Reflection
                int midx = getmaxx() / 2;
                int midy = getmaxy() / 2;
                char ax;

                cout << "Enter the axis for reflection (x/y): ";
                cin >> ax;

                if (ax == 'y') {
                    pp[0][0] = (midx - P[0][0]) + midx;
                    pp[0][1] = P[0][1];
                    pp[1][0] = (midx - P[1][0]) + midx;
                    pp[1][1] = P[1][1];
                } else if (ax == 'x') {
                    pp[0][0] = P[0][0];
                    pp[0][1] = (midy - P[0][1]) + midy;
                    pp[1][0] = P[1][0];
                    pp[1][1] = (midy - P[1][1]) + midy;
                }

                line(pp[0][0], pp[0][1], pp[1][0], pp[1][1]);
                system("pause");
                break;
            }
            case 4: { // Rotation
                float theta;
                cout << "Enter the angle of rotation in degrees: ";
                cin >> theta;

                float rx = (theta * M_PI) / 180.0; // Convert degrees to radians
                float T[3][3] = {{cos(rx), sin(rx), 0},
                                 {-sin(rx), cos(rx), 0},
                                 {0,       0,        1}};

                // Apply transformation
                for (i = 0; i < 2; i++) {
                    for (j = 0; j < 3; j++) {
                        pp[i][j] = 0; // Initialize transformed coordinates
                        for (k = 0; k < 3; k++) {
                            pp[i][j] += P[i][k] * T[k][j];
                        }
                    }
                }
                line(pp[0][0], pp[0][1], pp[1][0], pp[1][1]);
                system("pause");
                break;
            }
            case 5: { // Scaling
                int Sx, Sy;

                cout << "Enter the scaling factor for x-axis: ";
                cin >> Sx;

                cout << "Enter the scaling factor for y-axis: ";
                cin >> Sy;

                int T[3][3] = {{Sx, 0,  0},
                               {0,  Sy, 0},
                               {0,  0,  1}};

                // Apply transformation
                for (i = 0; i < 2; i++) {
                    for (j = 0; j < 3; j++) {
                        pp[i][j] = 0; // Initialize transformed coordinates
                        for (k = 0; k < 3; k++) {
                            pp[i][j] += P[i][k] * T[k][j];
                        }
                    }
                }

                line(pp[0][0], pp[0][1], pp[1][0], pp[1][1]);
                system("pause");
                break;
            }
            case 6: // Exit program
                return 0;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (ch != 6);

    return 0;
}
