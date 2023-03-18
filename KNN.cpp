#include "KNN.h"
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "Distances.h"


/**
 * constructor.
 * @param classifiedK vector of classified vectors, where rhe last parameter is the classification.
 */
KNN::KNN(std::vector<std::vector<double> > classifiedK) {
    classified = classifiedK;
}

/**
 *function get 2 vectors and name of distance to use and return the distance using the distances.h file.
 * @param v1 first vector.
 * @param v2 second vector.
 * @param distanceType name of distance.
 * @return the calculated distance.
 */
double KNN::distance(std::vector<double> v1, std::vector<double> v2, std::string distanceType) {
    double distance;
    Distances d(v1, v2);
    if (distanceType == "AUC") {
        distance = d.euclideanDistance();
    }
    if (distanceType == "MAN") {
        distance = d.manhattanDistance();
    }
    if (distanceType == "CHB") {
        distance = d.chebyshevDistance();
    }
    if (distanceType == "CAN") {
        distance = d.canberraDistance();
    }
    if (distanceType == "MIN") {
        distance = d.minkowskiDistance(3);
    }
    return distance;
}

/**
 * the function get input vector, tun over the classified vectors and return the classification of the vector.
 * @param input vector to classify.
 * @param k number of k neighbors.
 * @param disType type of distance.
 * @param numType number of possible classifications.
 * @return classification of the vector.
 */
int KNN::runNeighbors(std::vector<double> input, int kNum, std::string disType, int numType) {
    k = kNum;
    distanceType = disType;
    int i = 0;
    int x = input.size();
    int y = numType;
    std::vector<std::vector<double> > kNearest;
    std::vector<double> subVector;
    //running over the classified vector.
    for (i = 0; i < static_cast<int>(classified.size()); i++) {
        subVector = {classified[i].begin(), classified[i].end() - 1}; //sub vector without the classification.
        double dis = distance(subVector, input, distanceType);// finding distance.
        if (dis == -1) {//the distance function return -1 if tha function attempt to divide by 0.
            continue;
        }
        kNearest = kNearestUpdate1({dis, classified[i][x]}, kNearest);
    }
    std::vector<int> count(y, 0);
    for (int j = 0; j < k; j++) {
        //count how many neighbors of each classification there are in the k nearest neighbors vector.
        int a = int(kNearest[j][1]);
        count[a] += 1;
    }
    int maxIndex = 0;
    for (int j = 0; j < y; j++) {
        //finds the maximum classification. if there are classification equal in the number of neighbors, it returns
        // the one that come first in the vector.
        if (count[j] > count[maxIndex]) {
            maxIndex = j;
        }
    }
    return maxIndex;
}

/**
 * function get vector of vectors and vector x, insert the new vector and sort x.
 * @param x vector to insert to y.
 * @param y vector of vectors.
 * @return y with x, after removing the vector with 0 in the first element or the biggest first element.
 */
std::vector<std::vector<double> > KNN::kNearestUpdate1(std::vector<double> x, std::vector<std::vector<double> > y) {
    y.push_back(x);
    std::sort(y.begin(), y.end(),
              [](const std::vector<double> &a, const std::vector<double> &b) {
                  return a[0] < b[0];
              });
    if (static_cast<int>(y.size()) > k) {
        y.pop_back();
    }
    return y;
}

/**
 *function running the runNeighbors function
 * @param input line to classify
 * @param kNum K value
 * @param disType type of distance
 * @param numTyp enumber of possible classifications.
 * @return classification
 */
int KNN::classify(std::vector<double> input, int kNum, std::string disType, int numType) {
    return runNeighbors(input, kNum, disType, numType);
}

