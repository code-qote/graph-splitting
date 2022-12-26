#ifndef __GRAPHWIDGET_H
#define __GRAPHWIDGET_H

#include <QGraphicsView>
#include <set>

class ViewVertex;
class ViewEdge;
class GraphWidget : public QGraphicsView {
    Q_OBJECT
public:
    explicit GraphWidget(QWidget *parent = nullptr);

    void ItemMoved();
    void SetVertexes(std::vector<ViewVertex*> &vertexes);
    void AddVertex(ViewVertex* vertex);
    void AddEdge(ViewEdge* edge);
    ViewEdge* GetEdge(unsigned int id1, unsigned int id2);
    void SetToEdgeDefaultState(unsigned int id1, unsigned int id2);
    void SetToEdgeInvisibleState(unsigned int id1, unsigned int id2);
    void SetToEdgeRemovedState(unsigned int id1, unsigned int id2);
    void SetToEdgeColoringState(unsigned int id1, unsigned int id2);
    void SetToEdgeNotColoredState(unsigned int id1, unsigned int id2);
    void IncrementEdgeColoringLevel(unsigned int id1, unsigned int id2);
    void SelectVertexes(const std::set<int>& selected_vertexes);
    bool IsEdgeColoring(unsigned int id1, unsigned int id2);
    std::vector<int> GetVertexesColorsTypes();

    bool Forced() const { return forced; }
    void SetForced(bool forced) { this->forced = forced; }

    void ShowRemovedEdges();
    void HideRemovedEdges();

    void ColorVertex(unsigned int id, int color_type);
    void ColorVertexes(std::vector<int> &vertexes_types);
    bool IsConnected(unsigned int id1, unsigned int id2);

    int GetWidth() const { return width; }
    int GetHeight() const { return height; }

protected:
    void timerEvent(QTimerEvent *event) override;
    void drawBackground(QPainter *painter, const QRectF &rect) override;

private:
    int movement_timer_id = 0;
    int movement_timer_interval = 10;
    int coloring_timer_id = 0;
    int coloring_timer_interval = 10;
    int width = 600, height = 725;
    bool forced = true;

    std::vector<ViewVertex*> vertexes;
};


#endif
