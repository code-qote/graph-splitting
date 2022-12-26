#include "../GraphSplitter.h"

#include <iostream>

using Vertex = Graph::Vertex;

Graph GraphSplitter::GetAllBinaryTrees(Graph* graph, std::vector<std::pair<int, int> > &levels) {
    return buildGraph(getRoots(graph), levels);
}

Vertex::VertexesOrderedByDegree GraphSplitter::getRoots(Graph* graph) {
    Vertex::VertexesOrderedByDegree roots;

    Vertex::VertexesOrderedByDegree  vertexes = graph->GetVertexes();
    for (Vertex* vertex: vertexes) {
        int countOfNotRootsNeighbours = 0;
        for (Vertex* neighbour : vertex->Neighbours()) {
            countOfNotRootsNeighbours += (roots.count(neighbour) == 0);
        }
        if (countOfNotRootsNeighbours >= 2) {
            roots.insert(vertex);
        }
    }
    return roots;
}

bool hasCycle(int u, int prev, Graph &res, std::map<int, int> &color) {
    color[u] = 1;
    for (auto neighbour : res.GetVertexById(u)->Neighbours()) {
        if (neighbour->Id() != prev) {
            if (color[neighbour->Id()] == 0) {
                if (hasCycle(neighbour->Id(), u, res, color)) return true;
            }
            else if (color[neighbour->Id()] == 1) return true;
        }
    }
    color[u] = 2;
    return false;
}

Graph GraphSplitter::buildGraph(const Vertex::VertexesOrderedByDegree& roots, std::vector<std::pair<int, int> > &levels) {
    Graph res;
    std::map<unsigned int, int> neighbours_count;
    std::set<unsigned int> wasAddedAsNeighbour;
    for (Vertex* root : roots) {
        res.AddVertex(root->Id());
        int countOfNeighbours = 0;
        for (Vertex* neighbour : root->Neighbours()) {
            if (countOfNeighbours >= 2) break;
            if (roots.count(neighbour) != 0 && !res.IsConnected(root->Id(), neighbour->Id())
                && neighbours_count[neighbour->Id()] + 1 <= 2 && wasAddedAsNeighbour.count(neighbour->Id()) == 0) {
                countOfNeighbours++;
                res.AddVertex(neighbour->Id());
                res.AddEdge(root->Id(), neighbour->Id());
                levels.push_back({root->Id(), neighbour->Id()});
                neighbours_count[root->Id()]++;
                neighbours_count[neighbour->Id()]++;
                wasAddedAsNeighbour.insert(neighbour->Id());
            }
        }

        for (Vertex* neighbour : root->Neighbours()) {
            if (countOfNeighbours >= 2) break;
            if (roots.count(neighbour) == 0 && !res.IsConnected(root->Id(), neighbour->Id())
                && neighbours_count[neighbour->Id()] + 1 <= 2 && wasAddedAsNeighbour.count(neighbour->Id()) == 0) {
                countOfNeighbours++;
                res.AddVertex(neighbour->Id());
                res.AddEdge(root->Id(), neighbour->Id());
                levels.push_back({root->Id(), neighbour->Id()});
                neighbours_count[root->Id()]++;
                neighbours_count[neighbour->Id()]++;
                wasAddedAsNeighbour.insert(neighbour->Id());
            }
        }
    }
    for (auto root : roots) {
        if (res.GetVertexById(root->Id())->Neighbours().empty()) {
            res.RemoveVertex(root->Id());
        }
        else if (res.GetVertexById(root->Id())->Degree() <= 2) {
            for (auto vertex : root->Neighbours()) {
                std::map<int, int> color;
                bool was = res.HasVertex(vertex->Id());
                bool was_connected = res.IsConnected(root->Id(), vertex->Id());
                res.AddVertex(vertex->Id());
                res.AddEdge(root->Id(), vertex->Id());
                levels.push_back({root->Id(), vertex->Id()});
                if (!was_connected &&
                        res.GetVertexById(vertex->Id())->Degree() + 1 <= 3 && !hasCycle(root->Id(), -1, res, color)) {
                    break;
                } else {
                    if (!was_connected) {
                        res.RemoveEdge(root->Id(), vertex->Id());
                        levels.erase(std::remove(levels.begin(),
                                                  levels.end(),
                                                 std::make_pair((int) root->Id(),
                                                                       (int) vertex->Id())),
                                     levels.end());
                    }
                    if (!was) res.RemoveVertex(vertex->Id());
                }
            }
        }
    }
    return res;
}
