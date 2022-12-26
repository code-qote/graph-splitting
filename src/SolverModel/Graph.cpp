#include "Graph.h"


Graph::Graph(AdjacencyMatrix &adjacency_matrix) {
    this->adjacency_matrix = adjacency_matrix;
    vertex_number = this->adjacency_matrix.VertexNumber();
    fillWithNewVertexes(vertex_number, vertexes);
    addEdgesFromAdjacencyMatrix(vertex_number, adjacency_matrix);
}

Graph::Graph() {
    this->adjacency_matrix = AdjacencyMatrix();
    vertex_number = 0;
}

void Graph::fillWithNewVertexes(unsigned int vertex_number, std::map<unsigned int, Graph::Vertex*> &vertexes) {
    for (int i = 0; i < vertex_number; i++) {
        vertexes[i] = new Graph::Vertex(i);
    }
}

void Graph::addEdgesFromAdjacencyMatrix(unsigned int vertex_number, AdjacencyMatrix &adjacency_matrix) {
    for (int i = 0; i < vertex_number; i++) {
        for (int j = 0; j < vertex_number; j++) {
            if (adjacency_matrix.IsConnected(i, j)) {
                AddEdge(i, j);
            }
        }
    }
}

Graph::Vertex::VertexesOrderedByDegree Graph::GetVertexes() const {
    Graph::Vertex::VertexesOrderedByDegree res;
    for (auto p : vertexes) res.insert(p.second);
    return res;
}

Graph::Vertex* Graph::GetVertexById(unsigned int id) {
    if (vertexes.count(id) == 0) return nullptr;
    return vertexes[id];
}

void Graph::AddVertex(unsigned int id) {
    if (vertexes.count(id) == 0) {
        vertexes[id] = new Vertex(id);
        adjacency_matrix.AddVertex(id);
        vertex_number++;
    }
}

void Graph::RemoveVertex(unsigned int id) {
    if (vertexes.count(id) != 0) {
        auto neighbours = vertexes[id]->Neighbours();
        for (Vertex* neighbour : neighbours) {
            RemoveEdge(id, neighbour->Id());
        }
        delete vertexes[id];
        vertexes.erase(id);
        adjacency_matrix.RemoveVertex(id);
    }
}

void Graph::AddEdge(const unsigned int id1, const unsigned int id2) {
    vertexes[id1]->AddNeighbour(vertexes[id2]);
    vertexes[id2]->AddNeighbour(vertexes[id1]);
    adjacency_matrix.AddEdge(id1, id2);
}

void Graph::RemoveEdge(unsigned int id1, unsigned int id2) {
    if (vertexes.count(id1) != 0 && vertexes.count(id2) != 0) {
        vertexes[id1]->RemoveNeighbour(vertexes[id2]);
        vertexes[id2]->RemoveNeighbour(vertexes[id1]);
        adjacency_matrix.RemoveEdge(id1, id2);
    }
}

bool Graph::IsConnected(unsigned int id1, unsigned int id2) {
    return adjacency_matrix.IsConnected(id1, id2);
}

void insertGraphToGraph(Graph &destination, const Graph &source) {
    std::set<Graph::Vertex*, Graph::Vertex::cmp> vertexes = source.GetVertexes();
    for (auto vertex : vertexes) {
        destination.AddVertex(vertex->Id());
        for (Graph::Vertex* neighbour : vertex->Neighbours()) {
            destination.AddVertex(neighbour->Id());
            destination.AddEdge(vertex->Id(), neighbour->Id());
        }
    }
}

Graph operator|(const Graph &left, const Graph &right) {
    Graph res;
    insertGraphToGraph(res, left);
    insertGraphToGraph(res, right);
    return res;
}

void Graph::operator=(const Graph &other) {
    for (auto p : vertexes) {
        delete p.second;
    }
    vertexes.clear();
    adjacency_matrix = AdjacencyMatrix();
    auto other_vertexes = other.GetVertexes();
    for (Vertex* vertex : other_vertexes) {
        AddVertex(vertex->Id());
        for (Vertex* neighbour : vertex->Neighbours()) {
            AddVertex(neighbour->Id());
            AddEdge(vertex->Id(), neighbour->Id());
        }
    }
}

std::vector<std::vector<bool> > Graph::GetMatrix() {
    return adjacency_matrix.GetMatrix();
}

bool Graph::HasVertex(unsigned int id) {
    return std::any_of(vertexes.begin(), vertexes.end(),
                       [id](std::pair<unsigned int, Vertex*> p) { return p.first == id; });
}

bool dfs(Graph::Vertex* u, Graph::Vertex* prev, Graph* graph, std::map<Graph::Vertex*, bool> &used) {
    if (used[u]) return false;
    used[u] = true;

    bool f = false;
    for (auto v : u->Neighbours()) {
        if (v != prev && !used[v]) {
            graph->AddVertex(v->Id());
            graph->AddEdge(u->Id(), v->Id());
            f = true;
            dfs(v, u, graph, used);
        }
    }
    return f;
}

std::vector<Graph*> Graph::GetAllComponents() {
    std::map<Graph::Vertex*, bool> used;
    std::vector<Graph*> res;
    for (auto p : vertexes) {
        Graph::Vertex* vertex = p.second;
        if (!used[vertex]) {
            auto component = new Graph();
            component->AddVertex(vertex->Id());
            if (dfs(vertex, nullptr, component, used)) {
                for (auto p : component->vertexes) {
                    vertex = p.second;
                    auto neighbours = GetVertexById(vertex->Id())->Neighbours();
                    for (auto neighbour : neighbours) {
                        if (component->HasVertex(neighbour->Id()))
                            component->AddEdge(vertex->Id(), neighbour->Id());
                    }
                }

                res.push_back(component);
            }
            else delete component;
        }
    }
    return res;
}

Graph::~Graph() {
    for (auto vertex : vertexes) {
        delete vertex.second;
    }
    vertexes.clear();
}
