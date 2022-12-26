#include "../GraphSplitter.h"
#include <iostream>

using Vertex = Graph::Vertex;

Graph GraphSplitter::GetAllGrids(Graph *graph, std::vector<std::pair<int, int> > &levels) {
    Graph res;
    auto vertexes = graph->GetVertexes();
    for (Vertex* vertex : vertexes) {
        getGridFromVertexIfExists(vertex, res, levels);
    }
    return res;
}

void GraphSplitter::getGridFromVertexIfExists(Vertex* vertex, Graph &res, std::vector<std::pair<int, int> > &levels) {
    auto neighbours = vertex->Neighbours();
    if (neighbours.size() < 2) return;

    for (Vertex* v1 : neighbours) { // перебираем первые 2 вершины
        for (Vertex* v2 : neighbours) {
            if (v1 != v2) {
                auto neighbours_v1 = v1->Neighbours();
                auto neighbour_v2 = v2->Neighbours();

                auto common_neighbours = getCommonNeighbours(neighbours_v1, neighbour_v2); // общие соседи
                if (!common_neighbours.empty()) {
                    Vertex* v3 = nullptr;
                    for (Vertex* v : common_neighbours) // выбираем общего соседа
                        if (v != vertex && v != v1 && v != v2) v3 = v;
                    if (!v3) continue;
                    if (v1 != v3 && v2 != v3 && v1 != vertex && v2 != vertex && v3 != vertex) { // если все уникальные
                        int cnt = res.HasVertex(vertex->Id()) + res.HasVertex(v1->Id()) + res.HasVertex(v2->Id()) +
                                  res.HasVertex(v3->Id());
                        if (cnt == 0 || cnt == 2 || (cnt == 3 && !res.HasVertex(vertex->Id()) && // проверка на правильную решетку
                                                     (res.IsConnected(v1->Id(), v2->Id()) + res.IsConnected(
                                                             v1->Id(),
                                                             v3->Id())
                                                      + res.IsConnected(v2->Id(), v3->Id())) == 2) &&
                                                            res.GetVertexById(v1->Id())->Degree() + 1 <= 3 &&
                                                            res.GetVertexById(v2->Id())->Degree() + 1 <= 3) {
                            addNewGrid({vertex, v1, v2, v3}, res, levels); // добавление
                        }
                    }
                }
            }
        }
    }
}

void GraphSplitter::addNewGrid(const std::vector<Vertex*>& vertexes, Graph &graph, std::vector<std::pair<int, int> > &levels) {
    if (vertexes.size() == 4) {
        for (Vertex* vertex : vertexes) {
//            std::cout << vertex->Id() + 1<< ' ';
            graph.AddVertex(vertex->Id());
        }
        std::cout << '\n';
        graph.AddEdge(vertexes[0]->Id(), vertexes[1]->Id());
        pushBackIfNotExists(levels, {vertexes[0]->Id(), vertexes[1]->Id()});

        graph.AddEdge(vertexes[0]->Id(), vertexes[2]->Id());
        pushBackIfNotExists(levels, {vertexes[0]->Id(), vertexes[2]->Id()});

        graph.AddEdge(vertexes[1]->Id(), vertexes[3]->Id());
        pushBackIfNotExists(levels, {vertexes[1]->Id(), vertexes[3]->Id()});

        graph.AddEdge(vertexes[2]->Id(), vertexes[3]->Id());
        pushBackIfNotExists(levels, {vertexes[2]->Id(), vertexes[3]->Id()});
    }
}
