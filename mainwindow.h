#pragma once

#include <QWidget>
#include <QPushButton>
#include <QMenuBar>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>


class MainWindow : public QWidget {

  Q_OBJECT

  public:
    MainWindow(QWidget *parent = 0);

  private slots:
    void clearItem();
    void addItem();
    void showItems();
    void saveFile();
    void openFile();

  private:
    QVBoxLayout *vbox;
    QVBoxLayout *vbox1;
    QVBoxLayout *vbox2;
    QHBoxLayout *hbox;
    QHBoxLayout *hbox1;

    QAction *open;
    QAction *save;

    QMenuBar* menuBar;
    QMenu* fileMenu;

    QLabel *lw;
    QLabel *numPoints;
    QLabel *points;

    QPushButton *clear;
    QPushButton *add;
    QPushButton *showGraph;

    QString text;

    QList<std::pair<int, int>> listOfCoordinates;

};
