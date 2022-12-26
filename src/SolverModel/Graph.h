#ifndef __GRAPH_H
#define __GRAPH_H

#include <iostream>

#include "AdjacencyMatrix.h"
#include <map>
#include <set>

class Graph {
public:
    class Vertex {
    public:
        struct cmp {
            bool operator() (const Vertex* v1, const Vertex* v2) const {
                if (v1->neighbours.size() > v2->neighbours.size() && v1->id != v2->id) return true;
                if (v1->neighbours.size() < v2->neighbours.size() && v1->id != v2->id) return false;
                return v1->id < v2->id;
            };
        };

        using VertexesOrderedByDegree = std::set<Vertex *, cmp>;

        explicit Vertex(const unsigned int id) {
            this->id = id;
        }

        unsigned int Id() const { return id; }

        void AddNeighbour(Vertex *node) {
            neighbours.insert(node);
        }

        void RemoveNeighbour(Vertex *node) {
            if (neighbours.find(node) != neighbours.end()) {
                neighbours.erase(node);
            }
        }

        unsigned int Degree() const {
            return neighbours.size();
        }

        VertexesOrderedByDegree Neighbours() {
            VertexesOrderedByDegree res;
            for (auto neighbour : neighbours) res.insert(neighbour);
            return res;
        }

        ~Vertex() {
            neighbours.clear();
        }
    private:
        unsigned int id;

        std::set<Vertex *> neighbours;
    };

    explicit Graph(AdjacencyMatrix &adjacency_matrix);
    explicit Graph();

    void AddVertex(unsigned int id);
    void RemoveVertex(unsigned int id);
    void AddEdge(unsigned int id1, unsigned int id2);
    void RemoveEdge(unsigned int id1, unsigned int id2);
    bool HasVertex(unsigned int id);
    std::set<Vertex*, Vertex::cmp> GetVertexes() const;
    Vertex* GetVertexById(unsigned int id);
    bool IsConnected(unsigned int id1, unsigned int id2);
    std::vector<std::vector<bool> > GetMatrix();
    std::vector<Graph*> GetAllComponents();

    friend Graph operator|(const Graph &left, const Graph &right);
    void operator=(const Graph &other);

    ~Graph();

private:
    std::map<unsigned int, Vertex*> vertexes;
    unsigned int vertex_number;
    AdjacencyMatrix adjacency_matrix;

    static void fillWithNewVertexes(unsigned int vertex_number, std::map<unsigned int, Graph::Vertex *> &vertexes);
    void addEdgesFromAdjacencyMatrix(unsigned int vertex_number, AdjacencyMatrix &adjacency_matrix);
};
#endif