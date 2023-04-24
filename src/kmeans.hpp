#ifndef KMEANS_HPP
#define KMEANS_HPP

#include <vector>

using namespace std;
typedef vector<double> Point;

class Cluster
{
private:
    int clusterId;
    Point centroid;
    vector<Point> points;

public:
    Cluster(int clusterId, Point centroid);
    void add_point(Point p);
    bool remove_point(Point p);
    void remove_all_points();
    int get_id();
    int get_size();
    Point get_centroid();
};


class KMeans
{
private:
    int k, iters, dimensions;
    vector<Cluster> clusters;

public:
    KMeans();

};

#endif