#ifndef __VIEWEDGE_H
#define __VIEWEDGE_H

#include <QGraphicsItem>
#include <QMutex>

class ViewVertex;
class ViewEdge : public QGraphicsItem {
public:
    enum ViewEdgeState {
        DefaultState = 0,
        RemovedState = 1,
        InvisibleState = 2
    };

    enum ViewEdgeColoringState {
        NotColored = 0,
        Coloring = 1,
        Colored = 2
    };

    enum ViewEdgeColor {
        DefaultColor = 0x393E46,
        RemovedColor = 0xA2ACBD
    };

    ViewEdgeState GetState() { return state; }
    void SetState(ViewEdgeState state) {
        this->state = state;
        update();
    }

    ViewEdge(ViewVertex* v1, ViewVertex* v2);
    void Adjust();

    ViewVertex* GetVertex1() { return vertex1; }
    ViewVertex* GetVertex2() { return vertex2; }

    void SetColoring();
    void SetColoringColor(int color_type);
    void SwapVertexes();
    void SetNotColored();
    void IncrementColoringLevel();
    bool IsColoring();
    bool IsColored();
protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
private:
    const int max_level = 50;
    ViewEdgeState state = DefaultState;
    ViewEdgeColoringState coloring_state = NotColored;
    int coloring_level = 1;
    int coloring_color = 0xFFD400;
    QMutex mutex;

    ViewVertex* vertex1;
    ViewVertex* vertex2;

    QPointF point1;
    QPointF point2;
};


#endif
