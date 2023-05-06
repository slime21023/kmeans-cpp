#include <vector>
#include <cmath>
#include <random>
#include "./kmeans.hpp"

using namespace std;

// Compute the Euclidean distance between two data points
double euclidean_distance(const Point& a, const Point& b) {
    double d = 0.0;
    for (int i = 0; i < a.size(); i++) {
        d += (a[i] - b[i]) * (a[i] - b[i]);
    }
    return sqrt(d);
}

// Compute the index of the closest centroid to a data point
int closest_centroid(const vector<Point>& centroids, const vector<double>& point) {
    int index = 0;
    double min_distance = euclidean_distance(point, centroids[0]);
    for (int i = 1; i < centroids.size(); i++) {
        double d = euclidean_distance(point, centroids[i]);
        if (d < min_distance) {
            index = i;
            min_distance = d;
        }
    }
    return index;
}


// Update the centroids based on the current assignments
vector<Point> update_centroids(const vector<Point>& data, const vector<int>& assignments, int K) {
    vector<Point> centroids(K, vector<double>(data[0].size()));
    vector<int> counts(K, 0);
    for (int i = 0; i < data.size(); i++) {
        int cluster = assignments[i];
        counts[cluster]++;
        for (int j = 0; j < data[i].size(); j++) {
            centroids[cluster][j] += data[i][j];
        }
    }
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < centroids[i].size(); j++) {
            centroids[i][j] /= counts[i];
        }
    }
    return centroids;
}

KMeans::KMeans(int init_k, int init_iters, int init_dim, vector<Point> init_points)
{
    k = init_k;
    iters = init_iters;
    dimensions = init_dim;
    Point empty = Point(init_k, 0);
    points = vector<Point>(init_points.size(), empty);

    for (int i = 0; i < init_points.size(); i++)
    {
        for (int j = 0; j < k; j++)
        {
            points[i][j] = init_points[i][j];
        }
    }
};


void KMeans::fit()
{
    vector<Point> centroids(k, vector<double>(dimensions));

    for(int i = 0; i < k; i++)
    {
        int index = (i + rand()) % points.size();
        centroids[i] = points[index];
    }

    vector<int> assignments(points.size());
    for(int it = 0; it < iters; it++)
    {
        for(int i = 0; i < points.size(); i++)
        {
            assignments[i] = closest_centroid(centroids, points[i]);
        }

        vector<Point> new_centroids = update_centroids(points, assignments, k);

        bool converged = true;
        for(int i = 0; i < k; i++)
        {
            if (euclidean_distance(new_centroids[i], centroids[i]) > 1e-6) {
                converged = false;
                break;
            }
        }

        if (converged) {
            break;
        }

        centroids = new_centroids;
    }
    clusters = assignments;
}

vector<int> KMeans::clusters_ids()
{
    return clusters;
}