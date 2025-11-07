#include <bits/stdc++.h>
#include <random>
using namespace std;

struct Point {
    double x, y;
};

// Compute Euclidean distance between two towers
double dist(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

// Brute-force algorithm: O(n^2)
double bruteForceClosestPair(vector<Point>& towers) {
    double minDist = DBL_MAX;
    int n = towers.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double d = dist(towers[i], towers[j]);
            if (d < minDist)
                minDist = d;
        }
    }
    return minDist;
}

int main() {
    int n;
    cout << "Enter number of towers: ";
    cin >> n;

    vector<Point> towers(n);

    // Dynamically scale coordinate range with number of towers
    double rangeMax = max(1000.0, sqrt((double)n) * 100.0);

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dist(0.0, rangeMax);

    // Generate random tower coordinates
    for (int i = 0; i < n; ++i) {
        towers[i].x = dist(gen);
        towers[i].y = dist(gen);
    }

    auto start = chrono::high_resolution_clock::now();
    double result = bruteForceClosestPair(towers);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> duration = end - start;

    cout << fixed << setprecision(6);
    cout << "\nNumber of Towers: " << n << endl;
    cout << "Coordinate Range: [0, " << rangeMax << "]" << endl;
    cout << "Minimum distance between towers: " << result << endl;
    cout << "Execution time: " << duration.count() << " seconds" << endl;

    return 0;
}
