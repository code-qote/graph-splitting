#include "GraphWidget.h"
#include "ViewVertex.h"

#include <iostream>

void GraphWidget::drawBackground(QPainter *painter, const QRectF &rect) {
    Q_UNUSED(rect);

    painter->fillRect(sceneRect(), QBrush(QColor(0xEEEEEE)));
}

GraphWidget::GraphWidget(QWidget *parent) : QGraphicsView(parent) {
    auto *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(0, 5, width - 2, height - 2);
    setScene(scene);
    setGeometry(0, 5, width, height);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
}

void GraphWidget::ItemMoved() {
    if (!movement_timer_id) movement_timer_id = startTimer(movement_timer_interval);
}

void GraphWidget::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    for (auto vertex : vertexes)
        vertex->CalculateForces();

    bool itemsMoved = false;
    for (auto vertex : vertexes) {
        if (vertex->AdvancePosition())
            itemsMoved = true;
    }

    if (!itemsMoved) {
        killTimer(movement_timer_id);
        movement_timer_id = 0;
    }
}

void GraphWidget::SetVertexes(std::vector<ViewVertex *> &vertexes) {
    this->vertexes = vertexes;
}

void GraphWidget::AddVertex(ViewVertex *vertex) {
    if (vertex) scene()->addItem(vertex);
}

void GraphWidget::AddEdge(ViewEdge *edge) {
    if (edge) scene()->addItem(edge);
}

bool GraphWidget::IsConnected(unsigned int id1, unsigned int id2) {
    if (id1 < vertexes.size() && id2 < vertexes.size())
        return vertexes[id1]->IsConnectedWith(vertexes[id2]);
    return false;
}

void GraphWidget::ColorVertex(unsigned int id, int color_type) {
    vertexes[id]->SetColorByType(color_type);
}

void GraphWidget::ColorVertexes(std::vector<int> &vertexes_types) {
    for(int i = 0; i < vertexes_types.size(); i++) vertexes[i]->SetColorByType(vertexes_types[i]);
}

std::vector<int> GraphWidget::GetVertexesColorsTypes() {
    std::vector<int> res(vertexes.size());
    for(int i = 0; i < vertexes.size(); i++) res[i] = vertexes[i]->GetColorType();
    return res;
}

void GraphWidget::SetToEdgeDefaultState(unsigned int id1, unsigned int id2) {
    if (id1 >= vertexes.size() && id2 >= vertexes.size()) return;

    auto edge = vertexes[id1]->GetEdge(vertexes[id2]);
    if (edge) edge->SetState(ViewEdge::DefaultState);
}

void GraphWidget::SetToEdgeInvisibleState(unsigned int id1, unsigned int id2) {
    if (id1 >= vertexes.size() && id2 >= vertexes.size()) return;

    auto edge = vertexes[id1]->GetEdge(vertexes[id2]);
    if (edge) edge->SetState(ViewEdge::InvisibleState);
}

void GraphWidget::SetToEdgeRemovedState(unsigned int id1, unsigned int id2) {
    if (id1 >= vertexes.size() && id2 >= vertexes.size()) return;

    auto edge = vertexes[id1]->GetEdge(vertexes[id2]);
    if (edge) edge->SetState(ViewEdge::RemovedState);
}

void GraphWidget::SetToEdgeColoringState(unsigned int id1, unsigned int id2) {
    if (id1 >= vertexes.size() && id2 >= vertexes.size()) return;

    auto edge = vertexes[id1]->GetEdge(vertexes[id2]);
    if (edge) edge->SetColoring();
}

void GraphWidget::SetToEdgeNotColoredState(unsigned int id1, unsigned int id2) {
    if (id1 >= vertexes.size() && id2 >= vertexes.size()) return;

    auto edge = vertexes[id1]->GetEdge(vertexes[id2]);
    if (edge) edge->SetNotColored();
}

void GraphWidget::IncrementEdgeColoringLevel(unsigned int id1, unsigned int id2) {
    if (id1 >= vertexes.size() && id2 >= vertexes.size()) return;

    auto edge = vertexes[id1]->GetEdge(vertexes[id2]);
    if (edge) edge->IncrementColoringLevel();
}

bool GraphWidget::IsEdgeColoring(unsigned int id1, unsigned int id2) {
    if (id1 >= vertexes.size() && id2 >= vertexes.size()) return false;

    auto edge = vertexes[id1]->GetEdge(vertexes[id2]);
    if (edge) return edge->IsColoring();
    return false;
}

void GraphWidget::ShowRemovedEdges() {
    for (auto item : scene()->items()) {
        auto* edge = qgraphicsitem_cast<ViewEdge*>(item);
        if (edge) {
            if (edge->GetState() == ViewEdge::InvisibleState)
                edge->SetState(ViewEdge::RemovedState);
        }
    }
}

void GraphWidget::HideRemovedEdges() {
    for (auto item : scene()->items()) {
        auto* edge = qgraphicsitem_cast<ViewEdge*>(item);
        if (edge) {
            if (edge->GetState() == ViewEdge::RemovedState)
                edge->SetState(ViewEdge::InvisibleState);
        }
    }
}

ViewEdge *GraphWidget::GetEdge(unsigned int id1, unsigned int id2) {
    if (id1 >= vertexes.size() && id2 >= vertexes.size()) return nullptr;

    auto edge = vertexes[id1]->GetEdge(vertexes[id2]);
    return edge;
}

void GraphWidget::SelectVertexes(const std::set<int>& selected_vertexes) {
    for (auto vertex : vertexes) {
        vertex->SetSelected(selected_vertexes.count((int) vertex->Id()) > 0);
        vertex->update();
    }
}
