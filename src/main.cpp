#include <iostream>
#include <cmath>
#include <kaspar/DGF.hpp>

double kernel(Eigen::VectorXd const& x) {
    return std::exp(x.norm() / 2) / 2 * M_PIl;
}


int main(void) {
    Eigen::MatrixXd X(3, 2);
    Eigen::VectorXd point(2);
    X << 1, 2, 3, 4, 5, 6;
    std::cout << kaspar::ObtainFeatureGroups(kernel, X, 0.5) << std::endl;
    std::cout << kaspar::ObtainFeatureGroups(kernel, X, 2.0) << std::endl;
    return 0;
}