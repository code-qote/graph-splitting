#ifndef __IOBSERVER_H
#define __IOBSERVER_H

#include <vector>
#include <string>

class IObserver {
public:
    virtual void GraphSetted(std::vector<std::vector<bool> > adjacency_matrix) = 0;
    virtual void GraphSplitted(std::vector<std::vector<bool> > adjacency_matrix_to_draw,
                               std::vector<std::vector<std::vector<bool> > > adjacency_matrices_to_print,
                               std::vector<int> &vertexes_types,
                               std::vector<std::pair<int, int> > &levels) = 0;
    virtual void ErrorOccurred(std::string error) = 0;
};

#endif
