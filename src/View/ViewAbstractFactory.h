#ifndef __VIEWABSTRACTFACTORY_H
#define __VIEWABSTRACTFACTORY_H

#include <QGraphicsItem>
#include <utility>
#include "ViewVertex.h"
#include "ViewEdge.h"
#include <QTableWidget>
#include <QHeaderView>
#include <iostream>

class ViewAbstractFactory {
public:
    struct AbstractProductConfig {
        virtual ~AbstractProductConfig() = default;
    };

    virtual QGraphicsItem* CreateProduct(AbstractProductConfig &config) = 0;
    virtual ~ViewAbstractFactory() = default;
};

class WidgetAbstractFactory {
public:
    struct AbstractProductConfig {
        virtual ~AbstractProductConfig() = default;
    };

    virtual QWidget* CreateProduct(AbstractProductConfig &config) = 0;
    virtual ~WidgetAbstractFactory() = default;
};

class ViewVertexFactory : public ViewAbstractFactory {
public:
    struct ViewVertexConfig : AbstractProductConfig {
        ViewVertexConfig(GraphWidget *graph, int i) {
            this->graph = graph;
            id = i;
        }

        GraphWidget *graph{};
        unsigned int id{};
    };

    QGraphicsItem* CreateProduct(AbstractProductConfig &config) override {
        auto casted_config = dynamic_cast<ViewVertexConfig*>(&config);
        return new ViewVertex(casted_config->graph, casted_config->id);
    }
};

class ViewEdgeFactory : public ViewAbstractFactory {
public:
    struct ViewEdgeConfig : AbstractProductConfig {
        ViewEdgeConfig(ViewVertex *v1, ViewVertex *v2) {
            this->v1 = v1; this->v2 = v2;
        }

        ViewVertex* v1;
        ViewVertex* v2;
    };

    QGraphicsItem* CreateProduct(AbstractProductConfig &config) override {
        auto casted_config = dynamic_cast<ViewEdgeConfig*>(&config);
        return new ViewEdge(casted_config->v1, casted_config->v2);
    }
};

class ViewMatrix : public QTableWidget {
    Q_OBJECT
public:
    explicit ViewMatrix(QWidget *parent = nullptr) {
        setEditTriggers(NoEditTriggers);
        horizontalHeader()->setVisible(false);
        verticalHeader()->setVisible(false);
        horizontalHeader()->setDefaultSectionSize(30);
        verticalHeader()->setDefaultSectionSize(30);
    };
    void SetMatrix(const std::vector<std::vector<bool> >& matrix) {
        _matrix = matrix;
        normalized_matrix = normalize(_matrix);
        if (matrix.size() != matrix[0].size()) return;
        for (int i = 0; i < normalized_matrix.size(); i++) {
            if (i == rowCount()) insertRow(i);
            for (int j = 0; j < normalized_matrix.size(); j++) {
                if (j == columnCount()) insertColumn(j);
                auto item = new QTableWidgetItem();
                item->setText(normalized_matrix[i][j] ? "1" : "0");
                setItem(i, j, item);
            }
        }
    }

    std::vector<std::vector<bool> > GetMatrix() { return _matrix; }
private:
    std::vector<std::vector<bool> > _matrix;
    std::vector<std::vector<bool> > normalized_matrix;

    static std::vector<std::vector<bool> > normalize(std::vector<std::vector<bool> > matrix) {
        std::map<int, int> match;

        int j = 0;
        for (int i=0; i < matrix.size(); i++) {
            if (std::any_of(matrix[i].begin(), matrix[i].end(), [](bool x) { return x; })) {
                match[i] = j++;
            }
        }

        std::vector<std::vector<bool> > res(j, std::vector<bool>(j));
        for (auto p : match) {
            for (int i = 0; i < matrix[p.first].size(); i++) {
                if (matrix[p.first][i]) {
                    res[p.second][match[i]] = true;
                    res[match[i]][p.second] = true;
                }
            }
        }
        return res;
    }
};

class ViewMatrixFactory : public WidgetAbstractFactory {
public:
    struct ViewMatrixConfig : AbstractProductConfig {
        explicit ViewMatrixConfig(std::vector<std::vector<bool> > matrix) {
            this->matrix = std::move(matrix);
        }
        std::vector<std::vector<bool> > matrix;
    };

    QWidget* CreateProduct(AbstractProductConfig &config) override {
        auto matrix = new ViewMatrix();
        matrix->SetMatrix(dynamic_cast<ViewMatrixConfig*>(&config)->matrix);
        return matrix;
    }
};

#endif
