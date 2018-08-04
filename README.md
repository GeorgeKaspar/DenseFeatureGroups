# DenseFeatureGroups
C++ implementation of the article http://citeseerx.ist.psu.edu/viewdoc/summary?doi=10.1.1.155.896

# Usage  
```
mkdir build
cd build
cmake ..
make
./kaspar
```
You will see [0, 0, 0], [0, 1, 2]  
# Purposes
1) You can provide your own smoothing kernels
2) Use function [ObtainFeatureGroups](https://github.com/GeorgeKaspar/DenseFeatureGroups/blob/master/include/kaspar/DGF.hpp#L12)
    1) kernel to use (K : Eigen::VectorXd -> double)
    2) data matrix, each row is a unique feature of all data points (Eigen::MatrixXd) 
    3) h - bandwidth for the algorithm 
3) Link your code with generated library libDGF