#include <bits/stdc++.h>
#include <random>
using namespace std;

struct Point {
    double x, y;
};

// Function to compute Euclidean distance between two points
double dist(Point a, Point b) {
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

// Brute-force approach for small datasets
double bruteForce(vector<Point>& P, int left, int right) {
    double minDist = DBL_MAX;
    for (int i = left; i < right; ++i)
        for (int j = i + 1; j <= right; ++j)
            minDist = min(minDist, dist(P[i], P[j]));
    return minDist;
}

// Find the minimum distance in a vertical strip of points
double stripClosest(vector<Point>& strip, double d) {
    double minDist = d;
    sort(strip.begin(), strip.end(), [](Point a, Point b){ return a.y < b.y; });

    for (size_t i = 0; i < strip.size(); ++i)
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < minDist; ++j)
            minDist = min(minDist, dist(strip[i], strip[j]));
    return minDist;
}

// Recursive divide and conquer function
double closestPairRec(vector<Point>& P, int left, int right) {
    if (right - left <= 3)
        return bruteForce(P, left, right);

    int mid = (left + right) / 2;
    double midX = P[mid].x;

    double dLeft = closestPairRec(P, left, mid);
    double dRight = closestPairRec(P, mid + 1, right);
    double d = min(dLeft, dRight);

    vector<Point> strip;
    for (int i = left; i <= right; ++i)
        if (fabs(P[i].x - midX) < d)
            strip.push_back(P[i]);

    return min(d, stripClosest(strip, d));
}

// Wrapper function
double closestPair(vector<Point>& points) {
    sort(points.begin(), points.end(), [](Point a, Point b){ return a.x < b.x; });
    return closestPairRec(points, 0, points.size() - 1);
}

// Main function
int main() {
    int n;
    cout << "Enter number of towers: ";
    cin >> n;

    vector<Point> towers(n);

    // Dynamically set coordinate range based on number of towers
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
    double result = closestPair(towers);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> duration = end - start;
    cout << fixed << setprecision(6);
    cout << "\nNumber of Towers: " << n << endl;
    cout << "Coordinate Range: [0, " << rangeMax << "]" << endl;
    cout << "Minimum distance between towers: " << result << endl;
    cout << "Execution time: " << duration.count() << " seconds" << endl;

    return 0;
}
