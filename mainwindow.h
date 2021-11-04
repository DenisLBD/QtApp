#pragma once

#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include <QLabel>
#include <QList>


class ListWidget : public QWidget {

  Q_OBJECT

  public:
    ListWidget(QWidget *parent = 0);

  private slots:
    void clearItem();
    void addItem();
    void showItems();
    void saveFile();
    void openFile();

  private:
    QLabel *lw;
    QLabel *numPoints;
    QLabel *points;
    QPushButton *clear;
    QPushButton *add;
    QPushButton *showGraph;
    QString text;
    QList<std::pair<int, int>> listOfCoordinates;

};
