#ifndef __GRAPHSPLITTER_H
#define __GRAPHSPLITTER_H

#include "Graph.h"

class GraphSplitter {
public:
    static Graph GetAllLines(Graph* graph, std::vector<std::pair<int, int> > &levels);
    static Graph GetAllBinaryTrees(Graph* graph, std::vector<std::pair<int, int> > &levels);
    static Graph GetAllHyperCubes(Graph* graph, std::vector<std::pair<int, int> > &levels);
    static Graph GetAllGrids(Graph* graph, std::vector<std::pair<int, int> > &levels);
private:
    static Graph::Vertex::VertexesOrderedByDegree getRoots(Graph* graph);
    static Graph buildGraph(const Graph::Vertex::VertexesOrderedByDegree &roots, std::vector<std::pair<int, int> > &levels);
    static void pushBackIfNotExists(std::vector<std::pair<int, int> > &v, std::pair<int, int> elem);

    static std::set<Graph::Vertex*, Graph::Vertex::cmp> getCommonNeighbours(std::set<Graph::Vertex*, Graph::Vertex::cmp> &neighbours1,
                                                                            std::set<Graph::Vertex*, Graph::Vertex::cmp> &neighbours2);
    static void getCubeFromVertexIfExists(Graph::Vertex* vertex, Graph &res, std::vector<std::pair<int, int> > &levels);
    static void addNewCube(const std::vector<Graph::Vertex*>& vertexes, Graph &graph, std::vector<std::pair<int, int> > &levels);

    static void getGridFromVertexIfExists(Graph::Vertex* vertex, Graph &res, std::vector<std::pair<int, int> > &levels);
    static void addNewGrid(const std::vector<Graph::Vertex*>& vertexes, Graph &graph, std::vector<std::pair<int, int> > &levels);
};

#endif
