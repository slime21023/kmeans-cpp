#ifndef KMEANS_HPP
#define KMEANS_HPP

#include <vector>

using namespace std;
typedef vector<double> Point;

class KMeans
{
private:
    int k, iters, dimensions;
    vector<int> clusters;
    vector<Point> points;

public:
    KMeans(int init_k, int init_iters, int init_dim, vector<Point> init_points);
    void fit();
    vector<int> clusters_ids();
};

#endif