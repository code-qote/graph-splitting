#include <iostream>

#include "SolverModel.h"

using Vertex = Graph::Vertex;

void markVertexes(std::vector<VertexType> &vertexes_types, Graph& graph, VertexType type) {
    auto vertexes = graph.GetVertexes();
    for (auto vertex : vertexes) {
        vertexes_types[vertex->Id()] = type;
    }
}

void SolverModel::SplitGraph(unsigned int config) {
    /* config is unsigned int describing what algorithms should be used.
     * The first bit - Cube split
     * The second bit - Grid split
     * The third bit - Binary Tree split
     * The fourth bit - Line split */

    if (graph == nullptr) return;

    auto *origin_graph = new Graph();
    *origin_graph = *graph;
    Graph cubes;
    Graph grids;
    Graph binary_trees;
    Graph lines;
    std::vector<VertexType> vertexes_types(origin_graph->GetVertexes().size(), Default);
    std::vector<std::pair<int, int> > levels;

    if (config > 15) return;

    if (1 & config) {
        cubes = ExecuteSplittingAlgorithm(origin_graph, levels, GraphSplitter::GetAllHyperCubes);
        markVertexes(vertexes_types, cubes, HyperCube);
    }
    if (2 & config) {
        grids = ExecuteSplittingAlgorithm(origin_graph, levels, GraphSplitter::GetAllGrids);
        markVertexes(vertexes_types, grids, Grid);
    }
    if (4 & config) {
        binary_trees = ExecuteSplittingAlgorithm(origin_graph, levels, GraphSplitter::GetAllBinaryTrees);
        markVertexes(vertexes_types, binary_trees, BinaryTree);
    }
    if (8 & config) {
        lines = ExecuteSplittingAlgorithm(origin_graph, levels, GraphSplitter::GetAllLines);
        markVertexes(vertexes_types, lines, Line);
    }

    Graph res = cubes | grids | binary_trees | lines;

    notifyGraphSplitted(res, *origin_graph, vertexes_types, levels);
}

Graph SolverModel::ExecuteSplittingAlgorithm(Graph* graph_to_split, std::vector<std::pair<int, int> >& levels, Graph (*splitting_algorithm)(Graph* graph, std::vector<std::pair<int, int> > &levels)) {
    Graph res = splitting_algorithm(graph_to_split, levels);
    auto vertexes = res.GetVertexes();
    for (Vertex* vertex : vertexes) {
        graph_to_split->RemoveVertex(vertex->Id());
    }
    return res;
}

void SolverModel::SetGraphByAdjacencyMatrix(std::vector<std::vector<bool> > &adjacency_matrix) {
    AdjacencyMatrix matrix = AdjacencyMatrix(adjacency_matrix);
    delete graph;
    graph = new Graph(matrix);
    notifyGraphSetted();
}

void SolverModel::notifyGraphSetted() {
    for (auto listener : listeners) {
        listener->GraphSetted(graph->GetMatrix());
    }
}

void SolverModel::notifyGraphSplitted(Graph &splitted_graph,
                                      Graph &origin_graph,
                                      std::vector<VertexType> &vertexes_types,
                                      std::vector<std::pair<int, int> > &levels) {
    Graph result = (splitted_graph | origin_graph);

    std::vector<Graph*> components = result.GetAllComponents();
    std::vector<std::vector<std::vector<bool> > > matrices(components.size());
    int i = 0;
    for (Graph* g : components) matrices[i++] = g->GetMatrix();

    for (auto component : components) delete component;

    for (auto listener : listeners) {
        listener->GraphSplitted(result.GetMatrix(), matrices, reinterpret_cast<std::vector<int> &>(vertexes_types), levels);
    }
}

void SolverModel::notifyErrorOccurred(const std::string& error) {
    for (auto listener : listeners) {
        listener->ErrorOccurred(error);
    }
}

void SolverModel::AddListener(IObserver *listener) {
    listeners.insert(listener);
}

void SolverModel::RemoveListener(IObserver *listener) {
    if (listeners.count(listener) > 0)
        listeners.erase(listener);
}
