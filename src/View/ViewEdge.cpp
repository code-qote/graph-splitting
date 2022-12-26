#include <iostream>
#include "ViewEdge.h"
#include "ViewVertex.h"

ViewEdge::ViewEdge(ViewVertex *v1, ViewVertex *v2) : vertex1(v1), vertex2(v2) {
    vertex1->AddEdge(this); vertex2->AddEdge(this);
    setAcceptedMouseButtons(Qt::NoButton);
    Adjust();
}

void ViewEdge::Adjust() {
    if (!vertex1 || !vertex2) return;

    QLineF line(mapFromItem(vertex1, 0, 0), mapFromItem(vertex2, 0, 0));
    qreal length = line.length();

    prepareGeometryChange();

    int c_offset = 8; // for accuracy
    QPointF offset((line.dx() * c_offset) / length, (line.dy() * c_offset) / length);
    point1 = line.p1() + offset;
    point2 = line.p2() + offset;
}

QRectF ViewEdge::boundingRect() const
{
    if (!vertex1 || !vertex2)
        return {};

    return QRectF(point1, QSizeF(point2.x() - point1.x(),
                                      point2.y() - point1.y())).normalized();
}

void ViewEdge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if (!vertex1 || !vertex2) return;
    if (state == InvisibleState) return;

    QLineF line(point1, point2);

    if (qFuzzyCompare(line.length(), 0)) return;
    mutex.lock();

    if (state == DefaultState)
        painter->setPen(QPen(QColor(DefaultColor), 3,Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    else
        painter->setPen(QPen(QColor(RemovedColor), 3,Qt::DotLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);

    if (coloring_state == Colored) {
        painter->setPen(QPen(QColor(coloring_color), 3,Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter->drawLine(line);
    }

    if (coloring_state == Coloring) {
        QLineF coloring_line(point1, point2);
        double delta = line.length() / max_level;
        coloring_line.setLength(delta * coloring_level);
        painter->setPen(QPen(QColor(coloring_color), 3,Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter->drawLine(coloring_line);
        if (coloring_level >= max_level) {
            coloring_level = 0;
            coloring_state = Colored;
        }
    }
    mutex.unlock();
}

void ViewEdge::IncrementColoringLevel() {
    mutex.lock();
    if (coloring_state == Coloring) coloring_level++;
    mutex.unlock();
    update();
}

bool ViewEdge::IsColoring() {
    mutex.lock();
    bool res = coloring_state == Coloring;
    mutex.unlock();
    return res;
}

bool ViewEdge::IsColored() {
    mutex.lock();
    bool res = coloring_state == Colored;
    mutex.unlock();
    return res;
}

void ViewEdge::SetNotColored() {
    mutex.lock();
    coloring_state = NotColored;
    mutex.unlock();
}

void ViewEdge::SetColoring() {
    mutex.lock();
    coloring_state = Coloring;
    mutex.unlock();
}

void ViewEdge::SwapVertexes() {
    std::swap(vertex1, vertex2);
}

void ViewEdge::SetColoringColor(int color_type) {
    switch (color_type) {
        case 0:
            coloring_color = DefaultColor;
            break;
        case 1:
            coloring_color = 0xB1AFFF;
            break;
        case 2:
            coloring_color = 0x3EC1D3;
            break;
        case 3:
            coloring_color = 0xFF9A00;
            break;
        case 4:
            coloring_color = 0xFF165D;
            break;
        default:
            coloring_color = DefaultColor;
            break;
    }
}
