#ifndef __SOLVER_H
#define __SOLVER_H

#include <vector>
#include <string>

#include "Graph.h"
#include "GraphSplitter.h"
#include "../IObserver.h"
#include "../IObservable.h"

enum VertexType{
    Default = 0,
    HyperCube = 1,
    Grid = 2,
    BinaryTree = 3,
    Line = 4
};

class SolverModel : public IObservable {
public:
    SolverModel() = default;

    void SetGraphByAdjacencyMatrix(std::vector<std::vector<bool> >& adjacency_matrix);
    void SplitGraph(unsigned int config);

    void AddListener(IObserver* listener);
    void RemoveListener(IObserver* listener) override;

    ~SolverModel() { delete graph; }
private:
    Graph *graph{};
    GraphSplitter graph_splitter;

    std::set<IObserver*> listeners;

    static Graph ExecuteSplittingAlgorithm(Graph* graph_to_split, std::vector<std::pair<int, int> > &levels, Graph(*splitting_algorithm) (Graph* graph, std::vector<std::pair<int, int> > &levels));
    void notifyGraphSetted();
    void notifyGraphSplitted(Graph &splitted_graph,
                             Graph &origin_graph,
                             std::vector<VertexType> &vertexes_types,
                             std::vector<std::pair<int, int> > &levels);
    void notifyErrorOccurred(const std::string& error);
};

#endif
