#include <iostream>
#include <eigen3/Eigen/Core>
#include <functional>
#include <vector>

namespace kaspar {
    namespace __detail {
        Eigen::VectorXd create_kernel_weights(std::function<double(Eigen::VectorXd const&)> const& K, Eigen::MatrixXd const& X, Eigen::VectorXd const& point, double h);
        Eigen::VectorXd estimate_peak(std::function<double(Eigen::VectorXd const&)> const& K, Eigen::MatrixXd const& X, Eigen::VectorXd const& point, double h);
        void simple_dbscan(Eigen::MatrixXd const& Y, Eigen::VectorXi& out_indices, double h);
    } // __detail
    Eigen::VectorXi ObtainFeatureGroups(std::function<double(Eigen::VectorXd const&)> const& K, Eigen::MatrixXd const& X, double h=1.0);
} // kaspar