#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>

#include "../IObserver.h"
#include "ui_mainwindow.h"
#include "../SolverModel/SolverModel.h"
#include "GraphWidget.h"
#include "ViewAbstractFactory.h"

class MainWindow : public QObject, public IObserver // Singleton
{
public:
    Ui_MainWindow* ui_window;

    static MainWindow& GetInstance(QMainWindow* window) {
        static MainWindow instance(window);
        return instance;
    }

    void GraphSetted(std::vector<std::vector<bool> > adjacency_matrix) override;
    void GraphSplitted(std::vector<std::vector<bool> > adjacency_matrix_to_draw,
                       std::vector<std::vector<std::vector<bool> > >  adjacency_matrices_to_print,
                       std::vector<int> &vertexes_types,
                       std::vector<std::pair<int, int> > &levels) override;
    void ErrorOccurred(std::string error) override;

    ~MainWindow() override {
        delete ui_window; delete model;
    }
public slots:
    void EnterGraphButtonReleased();
    void SplitGraphButtonReleased();
    void ShowRemovedEdgesCheckBoxStateChanged();
    void ForcedCheckBoxStateChanged();
    void OpenFile();
    void SaveFile();
    void AddVertexButtonReleased() const;
    void RemoveVertexButtonReleased() const;
    void TableWidgetCleared() const;
    void AdjacencyMatrixChanged(int i, int j);
    void CopyToClipboardFromAdjacencyMatrix() const;
    void CopyToClipboardSplittedAdjacencyMatrix() const;
    void LeftButtonReleased();
    void RightButtonReleased();

private:
    SolverModel* model;
    GraphWidget* graph_widget{};
    QLayout* window_layout;
    ViewVertexFactory* view_vertex_factory{};
    ViewEdgeFactory* view_edge_factory{};
    ViewMatrixFactory* view_matrix_factory{};

    explicit MainWindow(QMainWindow* window);
    void connectSignals() const;
    void showRemovedEdges();
    void hideRemovedEdges();
    void enablePatternsChoice() const;
    void disableInteractiveWidgets() const;
    void enableInteractiveWidgets() const;
    static QString getMatrixFromQTableWidget(QTableWidget* table);
    unsigned int getConfigNumber() const;
    void showSelectedVertexes() const;
};
#endif
