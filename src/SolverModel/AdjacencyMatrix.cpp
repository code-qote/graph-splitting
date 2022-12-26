#include <vector>
#include <string>
#include <stdexcept>

#include "AdjacencyMatrix.h"

AdjacencyMatrix::AdjacencyMatrix(unsigned int vertex_number, const std::vector<std::string>& raw_data) {
    this->vertex_number = vertex_number;
    matrix.resize(vertex_number, std::vector<bool>(vertex_number));

    for (int i = 0; i < vertex_number; i++) {
        std::vector<std::string> splitted_line = splitString(raw_data[i]);
        if (splitted_line.size() != vertex_number) {
            throw "number of vertex in line " + std::to_string(i + 1) + " is invalid";
        }

        for (int j = 0; j < vertex_number; j++) {
            if (splitted_line[j] == "0") matrix[i][j] = false;
            else if (splitted_line[j] == "1") matrix[i][j] = true;
            else {
                throw "invalid format at line " + std::to_string(i + 1) + " symbol " + std::to_string(j + 1);
            }
        }
    }
}

AdjacencyMatrix::AdjacencyMatrix(std::vector<std::vector<bool>> &data) {
    this->vertex_number = data.size();
    matrix.resize(vertex_number, std::vector<bool>(vertex_number));

    for (int i = 0; i < vertex_number; i++) {
        for (int j = 0; j < vertex_number; j++) {
            if (data[i][j]) matrix[i][j] = true;
        }
    }
}

AdjacencyMatrix::AdjacencyMatrix() {
    vertex_number = 0;
}

void AdjacencyMatrix::AddVertex(unsigned int id) {
    if (id >= vertex_number) {
        for (int i = 0; i < vertex_number; i++) matrix[i].resize(id + 1);
        matrix.resize(id + 1, std::vector<bool>(id + 1));
        vertex_number = id + 1;
    }
}

void AdjacencyMatrix::RemoveVertex(unsigned int id) {
    if (id < vertex_number) {
        for (int neighbour_id = 0; neighbour_id < vertex_number; neighbour_id++) {
            RemoveEdge(id, neighbour_id);
        }
    }
}

void AdjacencyMatrix::AddEdge(unsigned int id1, unsigned int id2) {
    if (id1 < vertex_number && id2 < vertex_number) {
        matrix[id1][id2] = true;
        matrix[id2][id1] = true;
    }
}

void AdjacencyMatrix::RemoveEdge(unsigned int id1, unsigned int id2) {
    if (id1 < vertex_number && id2 < vertex_number) {
        matrix[id1][id2] = false;
        matrix[id2][id1] = false;
    }
}

AdjacencyMatrix::~AdjacencyMatrix() {
    vertex_number = 0;
    matrix.clear();
}

std::vector<std::string> AdjacencyMatrix::splitString(std::string s) {
    std::vector<std::string> v;
    unsigned int last = 0;
    while(last < s.size() && s[last] == 32) last++;
    for (unsigned int i = last; i < s.size(); ++i) {
        if (s[last] == 32) {
            last = i;
            continue;
        }
        if (s[i] == 32) {
            v.push_back(s.substr(last, i - last));
            last = i + 1;
        }
    }

    if (last < s.size() && s[last] != 32)
        v.push_back(s.substr(last, s.size() - last));

    return v;
}

bool AdjacencyMatrix::IsConnected(unsigned int id1, unsigned int id2) {
    if (id1 < vertex_number && id2 < vertex_number)
        return matrix[id1][id2];
    return false;
}

std::vector<std::vector<bool> > AdjacencyMatrix::GetMatrix() {
    return matrix;
}
