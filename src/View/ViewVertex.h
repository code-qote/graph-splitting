#ifndef __GRAPHVERTEX_H
#define __GRAPHVERTEX_H

#include "ViewEdge.h"
#include <QGraphicsItem>
#include <QPainter>

#include "GraphWidget.h"

class ViewVertex : public QGraphicsItem {
public:
    ViewVertex(GraphWidget* GraphView, unsigned int id);
    void AddEdge(ViewEdge* edge);
    void RemoveEdge(ViewVertex* vertex);
    void RemoveEdge(ViewEdge* edge);
    ViewEdge* GetEdge(ViewVertex* vertex);
    void CalculateForces();
    bool AdvancePosition();
    void SetColorByType(int type);
    unsigned int Id() const { return id; }
    int GetColorType() {
        if (color == DefaultColor) return 0;
        if (color == HyperCubeColor) return 1;
        if (color == GridColor) return 2;
        if (color == BinaryTreeColor) return 3;
        if (color == LineColor) return 4;
        if (color == ColoringColor) return 5;
        return 0;
    }

    bool IsConnectedWith(ViewVertex* vertex);

    enum { Type = UserType + 1 };
    int type() const override { return Type; }

    enum ViewVertexColor {
        DefaultColor = 0xF6F7D7,
        HyperCubeColor = 0xB1AFFF,
        GridColor = 0x3EC1D3,
        BinaryTreeColor = 0xFF9A00,
        LineColor = 0xFF165D,
        TextColor = 0x222831,
        ColoringColor = 0xFFD400
    };

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    bool IsSelected() { return isSelected; }
    void SetSelected(bool state) { isSelected = state; }
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
private:
    const qreal width = 20, height = 20;
    GraphWidget* graph;
    std::vector<ViewEdge*> edges;
    QPointF new_pos;
    unsigned int id;
    bool isSelected = false;
    QColor color = QColor(DefaultColor);

    QVector2D calculatePushingForces();
    QVector2D calculatePullingForces();
    QVector2D calculateForceFromCenter();
    int degree();

    void setNewPos(const QVector2D &velocity);
};


#endif
