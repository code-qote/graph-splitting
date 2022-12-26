#ifndef __ITEMDELEGATE_H
#define __ITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QEvent>
#include <QKeyEvent>
#include <QTableWidget>
#include <QClipboard>
#include <QApplication>

#include <iostream>

class ItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ItemDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {
        this->parent = dynamic_cast<QTableWidget *>(parent);
    }

    bool eventFilter(QObject *object, QEvent *event) override
    {
        if (event->type() == QEvent::KeyPress) {
            auto* keyEvent = dynamic_cast<QKeyEvent*>(event);
            if (keyEvent->matches(QKeySequence::Paste)) {
                pasteFromClipboard();
            }
        }
        return false;
    }
private:
    QTableWidget* parent;

    void pasteFromClipboard() {
        QClipboard* clipboard = QApplication::clipboard();
        if (clipboard) {
            parent->clear();
            auto qlist = clipboard->text().split('\n').toVector();
            int i = 0;
            for (const auto &line: qlist) {
                auto splitted_line = line.split(" ").toVector();
                for (int j = 0; j < splitted_line.length(); j++) {
                    if (i >= parent->rowCount() || j >= parent->columnCount()) {
                        parent->insertColumn(parent->columnCount());
                        parent->insertRow(parent->rowCount());
                    }
                    if (!(splitted_line[j] == "1" || splitted_line[j] == "0")) {
                        parent->clear();
                        return;
                    }
                    auto cell = new QTableWidgetItem();
                    cell->setText(splitted_line[j]);
                    parent->setItem(i, j, cell);
                }
                i++;
            }
            while(parent->rowCount() > i) {
                parent->removeRow(parent->rowCount() - 1);
                parent->removeColumn(parent->columnCount() - 1);
            }
        }
    }
};

#endif
