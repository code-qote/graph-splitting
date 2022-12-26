#ifndef __ADJACENCY_MATRIX_H
#define __ADJACENCY_MATRIX_H

#include <vector>
#include <string>

class AdjacencyMatrix {
public:
    AdjacencyMatrix(unsigned int vertex_number, const std::vector<std::string>& raw_data);
    explicit AdjacencyMatrix(std::vector<std::vector<bool> > &data);
    AdjacencyMatrix();
    ~AdjacencyMatrix();
    unsigned int VertexNumber() const { return vertex_number; };
    bool IsConnected(unsigned int id1, unsigned int id2);
    void AddVertex(unsigned int id);
    void RemoveVertex(unsigned int id);
    void AddEdge(unsigned int id1, unsigned int id2);
    void RemoveEdge(unsigned int id1, unsigned int id2);
    std::vector<std::vector<bool> > GetMatrix();

private:
    unsigned int vertex_number;
    std::vector<std::vector<bool> > matrix;
    static std::vector<std::string> splitString(std::string s);
};

#endif