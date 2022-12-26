#include "mainwindow.h"
#include "ViewVertex.h"
#include "GraphWidget.h"
#include "itemdelegate.h"

#include <iostream>
#include <fstream>
#include <random>

#include <QMessageBox>
#include <QFileDialog>
#include <QTimer>

typedef std::mt19937 rng_type;


MainWindow::MainWindow(QMainWindow *window) {
    this->ui_window = new Ui_MainWindow();
    this->ui_window->setupUi(window);
    window_layout = window->layout();

    model = new SolverModel();
    model->AddListener(this);
    view_vertex_factory = new ViewVertexFactory();
    view_edge_factory = new ViewEdgeFactory();
    view_matrix_factory = new ViewMatrixFactory();
    ui_window->AdjacencyMatrixTableWidget->setItemDelegate(new ItemDelegate(ui_window->AdjacencyMatrixTableWidget));
    connectSignals();
}

void MainWindow::connectSignals() const {
    QObject::connect(ui_window->EnterGraphButton, &QPushButton::released, this, &MainWindow::EnterGraphButtonReleased);
    QObject::connect(ui_window->HyperCubeCheckBox, &QCheckBox::stateChanged, this, &MainWindow::SplitGraphButtonReleased);
    QObject::connect(ui_window->GridCheckBox, &QCheckBox::stateChanged, this, &MainWindow::SplitGraphButtonReleased);
    QObject::connect(ui_window->BinaryTreeCheckBox, &QCheckBox::stateChanged, this, &MainWindow::SplitGraphButtonReleased);
    QObject::connect(ui_window->LineCheckBox, &QCheckBox::stateChanged, this, &MainWindow::SplitGraphButtonReleased);
    QObject::connect(ui_window->ShowRemovedEdgesCheckBox, &QCheckBox::stateChanged, this, &MainWindow::ShowRemovedEdgesCheckBoxStateChanged);
    QObject::connect(ui_window->ForcedCheckBox, &QCheckBox::stateChanged, this, &MainWindow::ForcedCheckBoxStateChanged);
    QObject::connect(ui_window->actionLoad_Adjacency_Matrix, &QAction::triggered, this, &MainWindow::OpenFile);
    QObject::connect(ui_window->actionSave_Adjacency_Matrix, &QAction::triggered, this, &MainWindow::SaveFile);
    QObject::connect(ui_window->AddVertexButton, &QPushButton::released, this, &MainWindow::AddVertexButtonReleased);
    QObject::connect(ui_window->RemoveVertexButton, &QPushButton::released, this, &MainWindow::RemoveVertexButtonReleased);
    QObject::connect(ui_window->AdjacencyMatrixTableWidget, &QTableWidget::cellChanged, this, &MainWindow::AdjacencyMatrixChanged);
    QObject::connect(ui_window->ClearTableButton, &QPushButton::released, this, &MainWindow::TableWidgetCleared);
    QObject::connect(ui_window->AdjacencyMatrixCopyButton, &QPushButton::released, this, &MainWindow::CopyToClipboardFromAdjacencyMatrix);
    QObject::connect(ui_window->SplittedMatrixCopyButton, &QPushButton::released, this, &MainWindow::CopyToClipboardSplittedAdjacencyMatrix);
    QObject::connect(ui_window->LeftButton, &QPushButton::released, this, &MainWindow::LeftButtonReleased);
    QObject::connect(ui_window->RightButton, &QPushButton::released, this, &MainWindow::RightButtonReleased);
}

void clearStackedWidget(QStackedWidget* stacked_widget) {
    for(int i = stacked_widget->count(); i >= 0; i--)
    {
        QWidget* widget = stacked_widget->widget(i);
        stacked_widget->removeWidget(widget);
    }
}

void MainWindow::GraphSplitted(std::vector<std::vector<bool> > adjacency_matrix_to_draw,
                               std::vector<std::vector<std::vector<bool> > > adjacency_matrices_to_print,
                               std::vector<int> &vertexes_types,
                               std::vector<std::pair<int, int> > &levels) {
    if (!graph_widget) return;
    if (!view_matrix_factory) return;

    std::vector<int> current_vertexes_colors_types = graph_widget->GetVertexesColorsTypes();

    if (current_vertexes_colors_types == vertexes_types) return;

    disableInteractiveWidgets();

    for (int id = 0; id < vertexes_types.size(); id++) {
        if (current_vertexes_colors_types[id] != vertexes_types[id]) {
            graph_widget->ColorVertex(id, 0);
        }
    }

    for (int i = 0; i < adjacency_matrix_to_draw.size(); i++) {
        for (int j = i + 1; j < adjacency_matrix_to_draw.size(); j++) {
            if (adjacency_matrix_to_draw[i][j])
                graph_widget->SetToEdgeDefaultState(i, j);
        }
    }

    if (!levels.empty()) {
        for (auto p: levels) {
            auto v1 = graph_widget->GetEdge(p.first, p.second)->GetVertex1();
            auto v2 = graph_widget->GetEdge(p.first, p.second)->GetVertex2();
            if (v1->Id() == p.second &&
                    v2->Id() == p.first) graph_widget->GetEdge(p.first, p.second)->SwapVertexes();

            if (!ui_window->ColoringAnimationCheckBox->isChecked()) continue;
            if (graph_widget->GetEdge(v1->Id(), v2->Id())->IsColored()) continue;
            if (!(vertexes_types[v1->Id()] != current_vertexes_colors_types[v1->Id()] &&
                  vertexes_types[v2->Id()] != current_vertexes_colors_types[v2->Id()] ||
                    vertexes_types[v1->Id()] == vertexes_types[v2->Id()] &&
                  current_vertexes_colors_types[v1->Id()] != current_vertexes_colors_types[v2->Id()])) continue;

            graph_widget->ColorVertex(p.first, vertexes_types[p.first]);
            graph_widget->ItemMoved();

            graph_widget->GetEdge(p.first, p.second)->SetColoringColor(vertexes_types[p.first]);
            graph_widget->SetToEdgeColoringState(p.first, p.second);
            while (graph_widget->IsEdgeColoring(p.first, p.second)) {
                QEventLoop loop;
                QTimer::singleShot(1, &loop, SLOT(quit()));
                loop.exec();
                graph_widget->IncrementEdgeColoringLevel(p.first, p.second);
            }
            graph_widget->ColorVertex(p.second, vertexes_types[p.first]);
        }

        for (auto p: levels) graph_widget->SetToEdgeNotColoredState(p.first, p.second);
    }

    for (int i = 0; i < adjacency_matrix_to_draw.size(); i++) {
        for (int j = i + 1; j < adjacency_matrix_to_draw.size(); j++) {
            if (!adjacency_matrix_to_draw[i][j] && graph_widget->IsConnected(i, j)) {
                if (ui_window->ShowRemovedEdgesCheckBox->isChecked())
                    graph_widget->SetToEdgeRemovedState(i, j);
                else
                    graph_widget->SetToEdgeInvisibleState(i, j);
            }
        }
    }

    clearStackedWidget(ui_window->stackedWidget);

    for (const auto& m : adjacency_matrices_to_print) {
        ViewMatrixFactory::ViewMatrixConfig config(m);
        auto matrix = view_matrix_factory->CreateProduct(config);
        ui_window->stackedWidget->addWidget(matrix);
        ui_window->RightButton->setEnabled(true);
    }

    enableInteractiveWidgets();
    ui_window->LeftButton->setEnabled(false);

    if (adjacency_matrices_to_print.size() == 1) ui_window->RightButton->setEnabled(false);

    if (!ui_window->HyperCubeCheckBox->isChecked() &&
        !ui_window->BinaryTreeCheckBox->isChecked() &&
        !ui_window->GridCheckBox->isChecked() &&
        !ui_window->LineCheckBox->isChecked()) {
        clearStackedWidget(ui_window->stackedWidget);
        ui_window->SplittedMatrixCopyButton->setEnabled(false);
    }

    graph_widget->ColorVertexes(vertexes_types);
    showSelectedVertexes();
    graph_widget->ItemMoved();
}

void MainWindow::GraphSetted(std::vector<std::vector<bool>> adjacency_matrix) {
    delete graph_widget;
    graph_widget = new GraphWidget();

    if (!view_vertex_factory || !view_edge_factory) return;

    clearStackedWidget(ui_window->stackedWidget);

    std::vector<ViewVertex*> vertexes(adjacency_matrix.size());
    for(int i = 0; i < adjacency_matrix.size(); i++)  {
        ViewVertexFactory::ViewVertexConfig config = {graph_widget, i};
        vertexes[i] = qgraphicsitem_cast<ViewVertex*>(view_vertex_factory->CreateProduct(config));
        graph_widget->scene()->addItem(vertexes[i]);
    }
    for (int i = 0; i < adjacency_matrix.size(); i++) {
        for (int j = i + 1; j < adjacency_matrix.size(); j++) {
            if (adjacency_matrix[i][j]) {
                ViewEdgeFactory::ViewEdgeConfig config = {vertexes[i], vertexes[j]};
                auto* edge = qgraphicsitem_cast<ViewEdge*>(view_edge_factory->CreateProduct(config));
                graph_widget->scene()->addItem(edge);
            }
        }
    }
    rng_type rng;
    rng_type::result_type const seedval = clock();
    rng.seed(seedval);
    std::uniform_int_distribution<rng_type::result_type> rnd_width(10, graph_widget->rect().width() - 100);
    std::uniform_int_distribution<rng_type::result_type> rnd_height(10, graph_widget->rect().height() - 100);
    for (auto vertex : vertexes) {
        int x = rnd_width(rng);
        int y = rnd_height(rng);
        vertex->setPos(x, y);
    }

    graph_widget->SetVertexes(vertexes);
    window_layout->addWidget(graph_widget);
    enablePatternsChoice();
}

void MainWindow::enablePatternsChoice() const {
    ui_window->groupBox->setEnabled(true);
    ui_window->actionHyper_Cube->setEnabled(true);
    ui_window->actionGrid->setEnabled(true);
    ui_window->actionBinary_Tree->setEnabled(true);
    ui_window->actionLine->setEnabled(true);
    ui_window->HyperCubeCheckBox->setEnabled(true);
    ui_window->HyperCubeCheckBox->setCheckState(Qt::Unchecked);
    ui_window->GridCheckBox->setCheckState(Qt::Unchecked);
    ui_window->BinaryTreeCheckBox->setCheckState(Qt::Unchecked);
    ui_window->LineCheckBox->setCheckState(Qt::Unchecked);
}

void MainWindow::ErrorOccurred(std::string error) {
    QMessageBox::critical(nullptr, "Error", QString::fromStdString(error));
}

void MainWindow::EnterGraphButtonReleased() {
    ui_window->ForcedCheckBox->setCheckState(Qt::Checked);
    if (ui_window->AdjacencyMatrixTableWidget->rowCount() == 0 ||
        ui_window->AdjacencyMatrixTableWidget->columnCount() == 0)
        return;
    std::vector<std::vector<bool> > adjacency_matrix(ui_window->AdjacencyMatrixTableWidget->rowCount(),
                                                     std::vector<bool>(ui_window->AdjacencyMatrixTableWidget->columnCount()));
    for (int i = 0; i < ui_window->AdjacencyMatrixTableWidget->rowCount(); i++) {
        for (int j = 0; j < ui_window->AdjacencyMatrixTableWidget->columnCount(); j++) {
            auto item = ui_window->AdjacencyMatrixTableWidget->item(i, j);
            if (!item) {
                ErrorOccurred("Not filled adjacency matrix");
                return;
            }
            auto text = item->text().trimmed().toStdString();
            if (text.empty()) {
                ErrorOccurred("Not filled adjacency matrix");
                return;
            }
            adjacency_matrix[i][j] = text == "1";
        }
    }
    ui_window->AddVertexButton->setEnabled(true);
    ui_window->RemoveVertexButton->setEnabled(true);
    ui_window->AdjacencyMatrixCopyButton->setEnabled(true);
    ui_window->ClearTableButton->setEnabled(true);
    model->SetGraphByAdjacencyMatrix(adjacency_matrix);
}

void MainWindow::SplitGraphButtonReleased() {
    ui_window->ForcedCheckBox->setCheckState(Qt::Checked);
    unsigned int config = getConfigNumber();
    model->SplitGraph(config);
}

unsigned int MainWindow::getConfigNumber() const {
    unsigned int configNumber = 0;
    if (ui_window->HyperCubeCheckBox->isChecked()) configNumber |= 1;
    if (ui_window->GridCheckBox->isChecked()) configNumber |= 2;
    if (ui_window->BinaryTreeCheckBox->isChecked()) configNumber |= 4;
    if (ui_window->LineCheckBox->isChecked()) configNumber |= 8;

    return configNumber;
}

void MainWindow::ShowRemovedEdgesCheckBoxStateChanged() {
    if (ui_window->ShowRemovedEdgesCheckBox->isChecked()) showRemovedEdges();
    else hideRemovedEdges();
}

void MainWindow::showRemovedEdges() {
    if (graph_widget) graph_widget->ShowRemovedEdges();
}

void MainWindow::hideRemovedEdges() {
    if (graph_widget) graph_widget->HideRemovedEdges();
}

void MainWindow::ForcedCheckBoxStateChanged() {
    if (graph_widget) {
        graph_widget->SetForced(ui_window->ForcedCheckBox->isChecked());
        graph_widget->ItemMoved();
    }
}

void MainWindow::OpenFile() {
    QString filename = QFileDialog::getOpenFileName(Q_NULLPTR, "Open File", QDir::currentPath(), "Text files (*.txt)");
    if (filename.isNull()) return;
    TableWidgetCleared();
    std::ifstream in;
    in.open(filename.toStdString());
    std::string line;
    int i = 0;
    while(std::getline(in, line)) {
        if (i >= ui_window->AdjacencyMatrixTableWidget->rowCount())
            ui_window->AdjacencyMatrixTableWidget->insertRow(ui_window->AdjacencyMatrixTableWidget->rowCount());
        int j = 0;
        for (const auto& s : QString::fromStdString(line).split(" ")) {
            if (j >= ui_window->AdjacencyMatrixTableWidget->columnCount())
                ui_window->AdjacencyMatrixTableWidget->insertColumn(ui_window->AdjacencyMatrixTableWidget->columnCount());
            if (s != "1" && s != "0") {
                TableWidgetCleared();
                return;
            }
            auto item = new QTableWidgetItem();
            item->setText(s);
            ui_window->AdjacencyMatrixTableWidget->setItem(i, j, item);
            j++;
        }
        i++;
    }
    in.close();
    EnterGraphButtonReleased();
}

void MainWindow::SaveFile() {
    if (ui_window->stackedWidget->count() == 0) {
        ErrorOccurred("Adjacency matrix is empty");
        return;
    }

    auto* table = dynamic_cast<ViewMatrix*>(ui_window->stackedWidget->currentWidget());

    QString filename = QFileDialog::getSaveFileName(Q_NULLPTR, "Save File", QDir::currentPath(), "Text Files (*.txt)");
    if (filename.isNull()) return;
    std::ofstream out;
    out.open(filename.toStdString());

    std::string res;
    for (int i = 0; i < table->rowCount(); i++) {
        for (int j = 0; j < table->columnCount(); j++) {
            res += table->item(i, j)->text().toStdString();
            if (j < table->columnCount() - 1) res += " ";
        }
        if (i < table->rowCount() - 1) res += '\n';
    }
    out << res;
    out.close();
}

void MainWindow::disableInteractiveWidgets() const {
    ui_window->EnterGraphButton->setEnabled(false);
    ui_window->groupBox->setEnabled(false);
    ui_window->AdjacencyMatrixTableWidget->setEnabled(false);
    ui_window->stackedWidget->setEnabled(false);
    ui_window->ColoringAnimationCheckBox->setEnabled(false);
    ui_window->SplittedMatrixCopyButton->setEnabled(false);
    ui_window->AdjacencyMatrixCopyButton->setEnabled(false);
    ui_window->AddVertexButton->setEnabled(false);
    ui_window->RemoveVertexButton->setEnabled(false);
    ui_window->LeftButton->setEnabled(false);
    ui_window->RightButton->setEnabled(false);
    ui_window->ClearTableButton->setEnabled(false);
}

void MainWindow::enableInteractiveWidgets() const {
    ui_window->EnterGraphButton->setEnabled(true);
    ui_window->groupBox->setEnabled(true);
    ui_window->AdjacencyMatrixTableWidget->setEnabled(true);
    ui_window->stackedWidget->setEnabled(true);
    ui_window->ColoringAnimationCheckBox->setEnabled(true);
    ui_window->SplittedMatrixCopyButton->setEnabled(true);
    ui_window->AdjacencyMatrixCopyButton->setEnabled(true);
    ui_window->AddVertexButton->setEnabled(true);
    ui_window->RemoveVertexButton->setEnabled(true);
    ui_window->LeftButton->setEnabled(true);
    ui_window->RightButton->setEnabled(true);
    ui_window->ClearTableButton->setEnabled(true);
}

void MainWindow::AddVertexButtonReleased() const {
    ui_window->AdjacencyMatrixTableWidget->insertColumn(ui_window->AdjacencyMatrixTableWidget->columnCount());
    ui_window->AdjacencyMatrixTableWidget->insertRow(ui_window->AdjacencyMatrixTableWidget->rowCount());
}

void MainWindow::RemoveVertexButtonReleased() const {
    ui_window->AdjacencyMatrixTableWidget->removeColumn(ui_window->AdjacencyMatrixTableWidget->columnCount() - 1);
    ui_window->AdjacencyMatrixTableWidget->removeRow(ui_window->AdjacencyMatrixTableWidget->rowCount() - 1);
}

void MainWindow::AdjacencyMatrixChanged(int i, int j) {
    if (!(ui_window->AdjacencyMatrixTableWidget->item(i, j)->text() == "0" ||
        ui_window->AdjacencyMatrixTableWidget->item(i, j)->text() == "1" ||
        ui_window->AdjacencyMatrixTableWidget->item(i, j)->text() == "") ||
        (i == j && ui_window->AdjacencyMatrixTableWidget->item(i, j)->text() == "1")) {
        std::string error = "Invalid format at row: " + std::to_string(i) + ", column: " + std::to_string(j);
        ui_window->AdjacencyMatrixTableWidget->item(i, j)->setText("");
        ErrorOccurred(error);
    }
}

void MainWindow::TableWidgetCleared() const {
    ui_window->AdjacencyMatrixTableWidget->clear();
    while (ui_window->AdjacencyMatrixTableWidget->columnCount() > 4) ui_window->AdjacencyMatrixTableWidget->removeColumn(0);
    while (ui_window->AdjacencyMatrixTableWidget->rowCount() > 4) ui_window->AdjacencyMatrixTableWidget->removeRow(0);
    window_layout->removeWidget(graph_widget);
    clearStackedWidget(ui_window->stackedWidget);
    disableInteractiveWidgets();
    ui_window->AdjacencyMatrixTableWidget->setEnabled(true);
    ui_window->stackedWidget->setEnabled(true);
    ui_window->EnterGraphButton->setEnabled(true);
    ui_window->ColoringAnimationCheckBox->setEnabled(true);
}

void MainWindow::CopyToClipboardFromAdjacencyMatrix() const {
    QClipboard* clipboard = QApplication::clipboard();
    clipboard->clear();
    clipboard->setText(getMatrixFromQTableWidget(ui_window->AdjacencyMatrixTableWidget));
}

void MainWindow::CopyToClipboardSplittedAdjacencyMatrix() const {
    auto table = dynamic_cast<ViewMatrix*>(ui_window->stackedWidget->currentWidget());
    QClipboard* clipboard = QApplication::clipboard();
    clipboard->clear();
    clipboard->setText(getMatrixFromQTableWidget(table));
}

QString MainWindow::getMatrixFromQTableWidget(QTableWidget* table) {
    QString res;
    int rows = table->rowCount(), columns = table->columnCount();
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            res += table->item(i, j)->text();
            if (j < columns - 1) res += " ";
        }
        if (i < rows - 1)
            res += '\n';
    }
    return res;
}

void MainWindow::LeftButtonReleased() {
    int index = ui_window->stackedWidget->currentIndex() - 1;
    int count = ui_window->stackedWidget->count();
    if (index >= 0)
        ui_window->stackedWidget->setCurrentIndex(index);
    if (index == 0)
        ui_window->LeftButton->setEnabled(false);
    if (index < count - 1) ui_window->RightButton->setEnabled(true);
    showSelectedVertexes();
}

void MainWindow::RightButtonReleased() {
    int index = ui_window->stackedWidget->currentIndex() + 1;
    int count = ui_window->stackedWidget->count();
    if (index< count)
        ui_window->stackedWidget->setCurrentIndex(index);
    if (index == count - 1)
        ui_window->RightButton->setEnabled(false);
    if (index > 0) ui_window->LeftButton->setEnabled(true);
    showSelectedVertexes();
}

void MainWindow::showSelectedVertexes() const {
    if (!graph_widget) return;
    if (ui_window->stackedWidget->count() == 0) {
        graph_widget->SelectVertexes({});
        return;
    }
    auto matrix = dynamic_cast<ViewMatrix*>(ui_window->stackedWidget->currentWidget())->GetMatrix();
    std::set<int> s;
    for (int i=0; i < matrix.size(); i++) {
        if (std::any_of(matrix[i].begin(), matrix[i].end(), [](bool x) { return x; })) {
            s.insert(i);
        }
    }
    graph_widget->SelectVertexes(s);
}
