#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>

#include <ipc/distance/distance_type.hpp>
#include <ipc/distance/edge_edge.hpp>

#include "../utils.hpp"

namespace py = pybind11;
using namespace ipc;

void define_edge_edge_distance_functions(py::module_& m)
{
    m.def(
        "edge_edge_distance",
        [](const Eigen::Vector3d& ea0, const Eigen::Vector3d& ea1,
           const Eigen::Vector3d& eb0, const Eigen::Vector3d& eb1,
           const EdgeEdgeDistanceType* dtype) {
            if (dtype == nullptr) {
                return edge_edge_distance(ea0, ea1, eb0, eb1);
            } else {
                return edge_edge_distance(ea0, ea1, eb0, eb1, *dtype);
            }
        },
        R"ipc_Qu8mg5v7(
        Compute the distance between a two lines segments in 3D.

        Parameters:
            ea0: first vertex of the first edge
            ea1: second vertex of the first edge
            eb0: first vertex of the second edge
            eb1: second vertex of the second edge
            dtype: (optional) edge-edge distance type to compute

        Returns:
            The distance between the two edges.

        Note:
            The distance is actually squared distance.
        )ipc_Qu8mg5v7",
        py::arg("ea0"), py::arg("ea1"), py::arg("eb0"), py::arg("eb1"),
        py::arg("dtype") = py::none());

    m.def(
        "edge_edge_distance_gradient",
        [](const Eigen::Vector3d& ea0, const Eigen::Vector3d& ea1,
           const Eigen::Vector3d& eb0, const Eigen::Vector3d& eb1,
           const EdgeEdgeDistanceType* dtype) {
            Vector<double, 12> grad;
            if (dtype == nullptr) {
                edge_edge_distance_gradient(ea0, ea1, eb0, eb1, grad);
            } else {
                edge_edge_distance_gradient(ea0, ea1, eb0, eb1, *dtype, grad);
            }
            return grad;
        },
        R"ipc_Qu8mg5v7(
        Compute the gradient of the distance between a two lines segments.

        Parameters:
            ea0: first vertex of the first edge
            ea1: second vertex of the first edge
            eb0: first vertex of the second edge
            eb1: second vertex of the second edge
            dtype: (optional) point edge distance type to compute

        Returns:
            The gradient of the distance wrt ea0, ea1, eb0, and eb1.

        Note:
            The distance is actually squared distance.
        )ipc_Qu8mg5v7",
        py::arg("ea0"), py::arg("ea1"), py::arg("eb0"), py::arg("eb1"),
        py::arg("dtype") = py::none());

    m.def(
        "edge_edge_distance_hessian",
        [](const Eigen::Vector3d& ea0, const Eigen::Vector3d& ea1,
           const Eigen::Vector3d& eb0, const Eigen::Vector3d& eb1,
           const EdgeEdgeDistanceType* dtype) {
            Eigen::Matrix<double, 12, 12> hess;
            if (dtype == nullptr) {
                edge_edge_distance_hessian(ea0, ea1, eb0, eb1, hess);
            } else {
                edge_edge_distance_hessian(ea0, ea1, eb0, eb1, *dtype, hess);
            }
            return hess;
        },
        R"ipc_Qu8mg5v7(
        Compute the hessian of the distance between a two lines segments.

        Parameters:
            ea0: first vertex of the first edge
            ea1: second vertex of the first edge
            eb0: first vertex of the second edge
            eb1: second vertex of the second edge
            dtype: (optional) point edge distance type to compute

        Returns:
            The hessian of the distance wrt ea0, ea1, eb0, and eb1.

        Note:
            The distance is actually squared distance.
        )ipc_Qu8mg5v7",
        py::arg("ea0"), py::arg("ea1"), py::arg("eb0"), py::arg("eb1"),
        py::arg("dtype") = py::none());
}
