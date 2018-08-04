#include <kaspar/DGF.hpp>

namespace kaspar {
    namespace __detail {
        constexpr size_t N_ITER = 10;
        Eigen::VectorXd create_kernel_weights(std::function<double(Eigen::VectorXd const&)> const& K, Eigen::MatrixXd const& X, Eigen::VectorXd const& point, double h) {
            Eigen::VectorXd res(X.rows());
            for (size_t i = 0; i < X.rows(); ++i) {
                res[i] = K((point - X.row(i).transpose()) / h);
            }
            return res;
        }
        inline Eigen::VectorXd estimate_peak(std::function<double(Eigen::VectorXd const&)> const& K, Eigen::MatrixXd const& X, Eigen::VectorXd const& initial, double h) {
            Eigen::VectorXd point(initial);
            for (size_t j = 0; j < N_ITER; ++j) {
                Eigen::VectorXd w = create_kernel_weights(K, X, point, h);
                point = (w.transpose() * X).transpose() / w.sum();
            }
            return point;
        }

        void simple_dbscan(Eigen::MatrixXd const& Y, Eigen::VectorXi& out_indices, double h) {
            std::vector<Eigen::VectorXd> cluster_centers;
            for (size_t i = 0; i < Y.rows(); ++i) {
                bool found_cluster = false;
                for (size_t j = 0; j < cluster_centers.size(); ++j) {
                    if ((Y.row(i).transpose() - cluster_centers[j]).norm() < h) {
                        out_indices[i] = j;
                        found_cluster = true;
                        break;
                    }
                }
                if (!found_cluster) {
                    out_indices(i) = cluster_centers.size();
                    cluster_centers.push_back(Y.row(i));
                }
            }
        }
    } // __detail

    Eigen::VectorXi ObtainFeatureGroups(std::function<double(Eigen::VectorXd const&)> const& K, Eigen::MatrixXd const& X, double h) {
        Eigen::MatrixXd Y(X);
        for (size_t i = 0; i < X.rows(); ++i) {
            Y.row(i) = __detail::estimate_peak(K, X, Y.row(i), h);
        }
        Eigen::VectorXi out_indices(Y.rows());
        __detail::simple_dbscan(Y, out_indices, h);
        return out_indices;
    }
} // kaspar