#include <queue>
#include "../GraphSplitter.h"

using Vertex = Graph::Vertex;

struct cmp {
    bool operator() (const Vertex* v1, const Vertex* v2) const{
        if (v1->Degree() < v2->Degree() && v1->Id() != v2->Id()) return true;
        if (v1->Degree() > v2->Degree() && v1->Id() != v2->Id()) return false;
        return v1->Id() < v2->Id();
    }
};

bool dfs(Vertex* vertex, Graph &res, std::set<Vertex*> &used, std::vector<std::pair<int, int> > &levels) {
    if (used.count(vertex) > 0) return false;
    used.insert(vertex);

    for(Vertex* neighbour : vertex->Neighbours()) {
        if (used.count(neighbour) == 0) {
            res.AddVertex(neighbour->Id());
            res.AddEdge(vertex->Id(), neighbour->Id());
            levels.push_back({vertex->Id(), neighbour->Id()});

            dfs(neighbour, res, used, levels);
            return true;
        }
    }
    return false;
}

Graph GraphSplitter::GetAllLines(Graph *graph, std::vector<std::pair<int, int> > &levels) {
    std::set<Vertex*> used;
    Graph res;

    std::set<Vertex*, cmp> vertexes;
    for (auto vertex : graph->GetVertexes()) vertexes.insert(vertex);
    for (Vertex* vertex : vertexes) {
        if (used.count(vertex) == 0) {
            res.AddVertex(vertex->Id());
            if (!dfs(vertex, res, used, levels)) {
                res.RemoveVertex(vertex->Id());
                used.erase(vertex);
            }
        }
    }

    for (Vertex* vertex : vertexes) {
        for (Vertex* neighbour : vertex->Neighbours()) {
            if (vertex->Degree() <= 1 && neighbour->Degree() <= 1) {
                res.AddVertex(vertex->Id());
                res.AddVertex(neighbour->Id());
                res.AddEdge(vertex->Id(), neighbour->Id());
                levels.push_back({vertex->Id(), neighbour->Id()});
            }
        }
    }

    return res;
}
