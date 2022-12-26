#include "../GraphSplitter.h"

using Vertex = Graph::Vertex;

Graph GraphSplitter::GetAllHyperCubes(Graph *graph, std::vector<std::pair<int, int> > &levels) {
    Graph res;
    auto vertexes = graph->GetVertexes();
    for (Vertex* vertex : vertexes) {
        getCubeFromVertexIfExists(vertex, res, levels);
    }
    return res;
}

std::set<Vertex*, Vertex::cmp> GraphSplitter::getCommonNeighbours(std::set<Vertex*, Vertex::cmp> &v1Neighbours, std::set<Vertex *, Vertex::cmp> &v2Neighbours) {
    std::set<Vertex*, Vertex::cmp> commonNeighbours;
    std::set_intersection(v1Neighbours.begin(), v1Neighbours.end(),
                          v2Neighbours.begin(), v2Neighbours.end(),
                          std::inserter(commonNeighbours, commonNeighbours.begin()), Vertex::cmp{});
    return commonNeighbours;
}

void GraphSplitter::getCubeFromVertexIfExists(Vertex* vertex, Graph &res, std::vector<std::pair<int, int> > &levels) {
    auto neighbours = vertex->Neighbours();
    if (neighbours.size() < 3) return;

    for (Vertex* v1 : neighbours) {
        for (Vertex* v2 : neighbours) {
            for (Vertex* v3 : neighbours) {
                if (v1 != v2 && v1 != v3 && v2 != v3 && v1 != vertex && v2 != vertex && v3 != vertex) {
                    auto NeighboursV1 = v1->Neighbours();
                    auto NeighboursV2 = v2->Neighbours();
                    auto NeighboursV3 = v3->Neighbours();
                    auto commonNeighboursV1V2 = getCommonNeighbours(NeighboursV1,
                                                                                 NeighboursV2);

                    auto commonNeighboursV1V3 = getCommonNeighbours(NeighboursV1,
                                                                                 NeighboursV3);

                    auto commonNeighboursV2V3 = getCommonNeighbours(NeighboursV2,
                                                                                 NeighboursV3);

                    if (commonNeighboursV1V2.empty() || commonNeighboursV1V3.empty() || commonNeighboursV2V3.empty())
                        continue;

                    for (Vertex* v4 : commonNeighboursV1V2) {
                        for (Vertex* v5 : commonNeighboursV1V3) {
                            for (Vertex* v6 : commonNeighboursV2V3) {
                                if (v4 != vertex && v5 != vertex && v6 != vertex) {
                                    auto NeighboursV4 = v4->Neighbours();
                                    auto NeighboursV5 = v5->Neighbours();
                                    auto NeighboursV6 = v6->Neighbours();

                                    auto commonNeighboursV5V6 = getCommonNeighbours(NeighboursV5,
                                                                 NeighboursV6);
                                    auto commonNeighboursV4V5V6 = getCommonNeighbours(
                                            NeighboursV4,
                                            commonNeighboursV5V6);
                                    

                                    if (!commonNeighboursV4V5V6.empty()) {
                                        Vertex* v7 = nullptr;
                                        for (Vertex* v : commonNeighboursV4V5V6) {
                                            if (v != vertex &&
                                                    v != v1 &&
                                                    v != v2 &&
                                                    v != v3 &&
                                                    v != v4 &&
                                                    v != v5 &&
                                                    v != v6)
                                                v7 = v;
                                        }
                                        if (!v7) continue;
                                        addNewCube({vertex, v1, v2, v3, v4, v5, v6, v7}, res, levels);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void GraphSplitter::pushBackIfNotExists(std::vector<std::pair<int, int> > &v, std::pair<int, int> elem) {
    for (auto i : v)
        if (i == elem || std::make_pair(i.second, i.first) == elem) return;
    v.push_back(elem);
}

void GraphSplitter::addNewCube(const std::vector<Vertex*>& vertexes, Graph &graph, std::vector<std::pair<int, int> > &levels) {
    if (vertexes.size() == 8) {
        for (Vertex* vertex : vertexes) graph.AddVertex(vertex->Id());
        graph.AddEdge(vertexes[0]->Id(), vertexes[1]->Id());
        pushBackIfNotExists(levels, {vertexes[0]->Id(), vertexes[1]->Id()});

        graph.AddEdge(vertexes[0]->Id(), vertexes[2]->Id());
        pushBackIfNotExists(levels, {vertexes[0]->Id(), vertexes[2]->Id()});

        graph.AddEdge(vertexes[0]->Id(), vertexes[3]->Id());
        pushBackIfNotExists(levels, {vertexes[0]->Id(), vertexes[3]->Id()});

        graph.AddEdge(vertexes[1]->Id(), vertexes[4]->Id());
        pushBackIfNotExists(levels, {vertexes[1]->Id(), vertexes[4]->Id()});

        graph.AddEdge(vertexes[1]->Id(), vertexes[5]->Id());
        pushBackIfNotExists(levels, {vertexes[1]->Id(), vertexes[5]->Id()});

        graph.AddEdge(vertexes[2]->Id(), vertexes[4]->Id());
        pushBackIfNotExists(levels, {vertexes[2]->Id(), vertexes[4]->Id()});

        graph.AddEdge(vertexes[2]->Id(), vertexes[6]->Id());
        pushBackIfNotExists(levels, {vertexes[2]->Id(), vertexes[6]->Id()});

        graph.AddEdge(vertexes[3]->Id(), vertexes[5]->Id());
        pushBackIfNotExists(levels, {vertexes[3]->Id(), vertexes[5]->Id()});

        graph.AddEdge(vertexes[3]->Id(), vertexes[6]->Id());
        pushBackIfNotExists(levels, {vertexes[3]->Id(), vertexes[6]->Id()});

        graph.AddEdge(vertexes[4]->Id(), vertexes[7]->Id());
        pushBackIfNotExists(levels, {vertexes[4]->Id(), vertexes[7]->Id()});

        graph.AddEdge(vertexes[5]->Id(), vertexes[7]->Id());
        pushBackIfNotExists(levels, {vertexes[5]->Id(), vertexes[7]->Id()});

        graph.AddEdge(vertexes[6]->Id(), vertexes[7]->Id());
        pushBackIfNotExists(levels, {vertexes[6]->Id(), vertexes[7]->Id()});
    }
}

