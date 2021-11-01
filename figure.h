#pragma once

#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include <QLabel>


class ListWidget : public QWidget {

  Q_OBJECT

  public:
    ListWidget(QWidget *parent = 0);

  private slots:
    void clearItem();
    void addItem();
    void removeItem();
    void showItems();

  private:
    QListWidget *lw;
    QLabel *numPoints;
    QLabel *points;
    QPushButton *clear;
    QPushButton *add;
    QPushButton *showGraph;
};
