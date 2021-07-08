#pragma once

#include <Eigen/Core>

#include <ipc/broad_phase/collision_candidate.hpp>

namespace ipc {

enum class BroadPhaseMethod {
    BRUTE_FORCE,
    HASH_GRID,
    SPATIAL_HASH,
};

/// @brief Construct a set of discrete collision detection candidates.
///
/// @note V can either be the surface vertices or the entire mesh vertices.
/// The edges and face should be only for the surface elements.
///
/// @param[in] V0 Vertex positions at start as rows of a matrix.
/// @param[in] V1 Vertex positions at end as rows of a matrix.
/// @param[in] E Edges as rows of indicies into V.
/// @param[in] F Triangular faces as rows of indicies into V.
/// @param[out] canidates The constructed candidate set as output.
/// @param[in] inflation_radius Amount to inflate the bounding boxes.
/// @param[in] method Broad phase method to use.
/// @param[in] ignore_codimensional_vertices Ignores vertices not connected to
///                                          edges.
/// @param[in] can_collide A function that takes two vertex IDs
///                        (row numbers in F) and returns true if the vertices
///                        (and faces or edges containting the edges) can
///                        collide. By default all primitives can collide with
///                        all other primitives.
void construct_collision_candidates(
    const Eigen::MatrixXd& V,
    const Eigen::MatrixXi& E,
    const Eigen::MatrixXi& F,
    Candidates& candidates,
    double inflation_radius = 0,
    const BroadPhaseMethod& method = BroadPhaseMethod::HASH_GRID,
    bool ignore_codimensional_vertices = false,
    const std::function<bool(size_t, size_t)>& can_collide =
        [](size_t, size_t) { return true; });

/// @brief Construct a set of continous collision detection candidates.
///
/// @note Assumes the trajectory is linear.
/// @note V can either be the surface vertices or the entire mesh vertices.
/// The edges and face should be only for the surface elements.
///
/// @param[in] V0 Vertex positions at start as rows of a matrix.
/// @param[in] V1 Vertex positions at end as rows of a matrix.
/// @param[in] E Edges as rows of indicies into V.
/// @param[in] F Triangular faces as rows of indicies into V.
/// @param[out] canidates The constructed candidate set as output.
/// @param[in] inflation_radius Amount to inflate the bounding boxes.
/// @param[in] method Broad phase method to use.
/// @param[in] ignore_codimensional_vertices Ignores vertices not connected to
///                                          edges.
/// @param[in] can_collide A function that takes two vertex IDs
///                        (row numbers in F) and returns true if the vertices
///                        (and faces or edges containting the edges) can
///                        collide. By default all primitives can collide with
///                        all other primitives.
void construct_collision_candidates(
    const Eigen::MatrixXd& V0,
    const Eigen::MatrixXd& V1,
    const Eigen::MatrixXi& E,
    const Eigen::MatrixXi& F,
    Candidates& candidates,
    double inflation_radius = 0,
    const BroadPhaseMethod& method = BroadPhaseMethod::HASH_GRID,
    bool ignore_codimensional_vertices = false,
    const std::function<bool(size_t, size_t)>& can_collide =
        [](size_t, size_t) { return true; });

} // namespace ipc
