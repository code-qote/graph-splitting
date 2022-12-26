#include "ViewVertex.h"
#include <iostream>

#include <QStyleOptionGraphicsItem>
#include <QVector2D>
#include <QLabel>

ViewVertex::ViewVertex(GraphWidget *GraphView, unsigned int id) : graph(GraphView), id(id) {
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(2); // to make vertex always be above edges
}

QPainterPath ViewVertex::shape() const {
    QPainterPath path;
    path.addEllipse(-width / 2, -height / 2, width, height);
    return path;
}

void ViewVertex::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if (isSelected) {
        painter->setPen(QPen(QColor(0x6AB547), 2));
        painter->drawEllipse((int) -width / 2, (int) -height / 2, (int) width, (int) height);
    }

    painter->setBrush(QBrush(QColor(color)));
    painter->drawEllipse((int) -width / 2, (int) -height / 2, (int) width, (int) height);

    auto sceneRect = scene()->sceneRect();
    QString number = QString::number(id + 1);
    QRectF text_rect((qreal) (-4 * number.size()), -7, sceneRect.width(), sceneRect.height());
    painter->setPen(QColor(TextColor));
    painter->drawText(text_rect, number);
    painter->setPen(QPen(QColor(0x404E7C), 2));
    QRectF degree_text_rect( 15, -15, width, height);
    painter->drawText(degree_text_rect, QString::fromStdString(std::to_string(degree())));
}

QRectF ViewVertex::boundingRect() const {
    qreal adjust = 2;
    return {-width / 2 - adjust, -height / 2 - adjust, 2 * width + 3 + adjust, 2 * height + 3 + adjust};
}

void ViewVertex::CalculateForces() {
    if (!scene() || scene()->mouseGrabberItem() == this || !graph->Forced()) {
        new_pos = pos();
        return;
    }
    QVector2D velocity = calculatePushingForces() + calculatePullingForces() + calculateForceFromCenter();
    if (abs(velocity.x()) < 0.1 && abs(velocity.y()) < 0.1) velocity = {0, 0};
    setNewPos(velocity);
}

void ViewVertex::setNewPos(const QVector2D &velocity) {
    QRectF sceneRect = scene()->sceneRect();
    new_pos = pos() + QPointF(velocity.x(), velocity.y());
    new_pos.setX(std::min(std::max(new_pos.x(), sceneRect.left() + width / 2), sceneRect.right() - height / 2));
    new_pos.setY(std::min(std::max(new_pos.y(), sceneRect.top() + width / 2), sceneRect.bottom() - height / 2));
}

QVector2D ViewVertex::calculatePushingForces() {
    QVector2D velocity;
    const QList<QGraphicsItem *> items = scene()->items();
    for (auto item : items) {
        auto* vertex = qgraphicsitem_cast<ViewVertex*>(item);
        if (!vertex) continue;

        double c_push = 30;

        QPointF vec = mapToItem(vertex, 0, 0);
        double length = vec.x() * vec.x() + vec.y() * vec.y();
        if (length > 0) {
            velocity.setX(velocity.x() + (c_push * vec.x()) / length);
            velocity.setY(velocity.y() + (c_push * vec.y()) / length);
        }
    }
    return velocity;
}

QVector2D ViewVertex::calculatePullingForces() {
    QVector2D velocity;
    qreal best_l = edges.size() + 1;
    for(auto edge : edges) {
        ViewVertex* vertex;
        if (edge->GetVertex1() == this)
            vertex = edge->GetVertex2();
        else
            vertex = edge->GetVertex1();

        double c_pull = 10;
        if (edge->GetState() == ViewEdge::DefaultState) {
            QPointF vec = mapToItem(vertex, 0, 0);
            velocity.setX(velocity.x() - vec.x() / (best_l * c_pull));
            velocity.setY(velocity.y() - vec.y() / (best_l * c_pull));
        }
    }
    return velocity;
}

QVector2D ViewVertex::calculateForceFromCenter() {
    QVector2D velocity;
    qreal best_l = edges.size() + 1;
    double c_pull = 60;
    QPointF vec = {graph->GetWidth() / 2 - pos().x(), graph->GetHeight() / 2 - pos().y()};
    velocity.setX(velocity.x() + vec.x() / (best_l * c_pull));
    velocity.setY(velocity.y() + vec.y() / (best_l * c_pull));
    return velocity;
}

bool ViewVertex::AdvancePosition()
{
    if (new_pos == pos())
        return false;

    setPos(new_pos);
    return true;
}

void ViewVertex::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    update();
    QGraphicsItem::mousePressEvent(event);
}

void ViewVertex::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

void ViewVertex::AddEdge(ViewEdge *edge) {
    edges.push_back(edge);
    edge->Adjust();
}

QVariant ViewVertex::itemChange(GraphicsItemChange change, const QVariant &value) {
    if (change == ItemPositionHasChanged) {
        for (ViewEdge* edge : edges) {
            edge->Adjust();
        }
        graph->ItemMoved();
    }
    return QGraphicsItem::itemChange(change, value);
}

void ViewVertex::RemoveEdge(ViewEdge *edge) {
    if (edge) edges.erase(std::remove(edges.begin(), edges.end(), edge), edges.end());
}

bool ViewVertex::IsConnectedWith(ViewVertex *vertex) {
    for (auto edge : edges)
        if (edge->GetVertex1() == vertex || edge->GetVertex2() == vertex) return true;
    return false;
}

void ViewVertex::RemoveEdge(ViewVertex* vertex) {
    for (auto edge : edges) {
        if (edge->GetVertex1() == vertex || edge->GetVertex2() == vertex) {
            edges.erase(std::remove(edges.begin(), edges.end(), edge), edges.end());
            return;
        }
    }
}

ViewEdge *ViewVertex::GetEdge(ViewVertex *vertex) {
    for (auto edge : edges) {
        if (edge->GetVertex1() == vertex || edge->GetVertex2() == vertex) {
            return edge;
        }
    }
    return nullptr;
}

void ViewVertex::SetColorByType(int type) {
    switch (type) {
        case 0:
            color = QColor(DefaultColor);
            break;
        case 1:
            color = QColor(HyperCubeColor);
            break;
        case 2:
            color = QColor(GridColor);
            break;
        case 3:
            color = QColor(BinaryTreeColor);
            break;
        case 4:
            color = QColor(LineColor);
            break;
        case 5:
            color = QColor(ColoringColor);
            break;
        default:
            color = QColor(DefaultColor);
            break;
    }
    update();
}

int ViewVertex::degree() {
    int cnt = 0;
    for (auto edge : edges) {
        if (edge->GetState() == ViewEdge::DefaultState) cnt++;
    }
    return cnt;
}
