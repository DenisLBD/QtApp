#include "figure.h"
#include "logic.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>

ListWidget::ListWidget(QWidget *parent)
    : QWidget(parent)
{



  QVBoxLayout *vbox = new QVBoxLayout(this); //поменял местами this
  vbox->setSpacing(10);

  QHBoxLayout *hbox = new QHBoxLayout(); //

  lw = new QListWidget(this);
  lw->addItem("The Omen");
  lw->addItem("The Exorcist");
  lw->addItem("Notes on a scandal");
  lw->addItem("Fargo");
  lw->addItem("Capote");

  QString sPoints = "Points:";
  QString sNumPoints = "0";

  points = new QLabel(sPoints, this);
  numPoints = new QLabel(sNumPoints, this);

  clear = new QPushButton("Clear", this);
  add = new QPushButton("Add", this);
  showGraph = new QPushButton("Show", this);

  // Работа с меню
  // Данные изображения мы будем использовать в качестве иконок в нашем меню
  QPixmap openpix("C:\\Qt\\Apps\\QtApp\\open.png");
  QPixmap savepix("C:\\Qt\\Apps\\QtApp\\save.png");

  // Здесь в качестве первых аргументов мы используем конструкторы класса QAction
  QAction *open = new QAction(openpix, "&Open", this);
  QAction *save = new QAction(savepix, "&Save", this);

  // А здесь мы задаем сочетание горячих клавиш CTRL+Q, которое будет выполнять действие Quit (Выход)
  save->setShortcut(tr("CTRL+S"));

  // В некоторых средах значки меню по умолчанию не отображаются, поэтому мы можем попробовать отключить атрибут Qt::AA_DontShowIconsInMenus
  qApp->setAttribute(Qt::AA_DontShowIconsInMenus, false);

  //connect(quit, &QAction::triggered, qApp, &QApplication::quit);

  QMenuBar* menuBar = new QMenuBar();
  QMenu *fileMenu = new QMenu("&File");
  menuBar->addMenu(fileMenu);
  fileMenu->addAction(open);
  fileMenu->addSeparator();
  fileMenu->addAction(save);

  this->layout()->setMenuBar(menuBar);
  // Конец работы с меню

  vbox->addWidget(lw);
  vbox->addSpacing(15);

  QVBoxLayout *vbox1 = new QVBoxLayout(this);

  vbox1->setSpacing(3);
  vbox1->addStretch(1);
  vbox1->addWidget(clear);
  vbox1->addWidget(add);

  QVBoxLayout *vbox2 = new QVBoxLayout(this);
  QHBoxLayout *hbox1 = new QHBoxLayout(this);

  hbox1->addWidget(points);
  hbox1->addWidget(numPoints);

  vbox2->setSpacing(3);
  vbox2->addStretch(1);
  vbox2->addLayout(hbox1);
  vbox2->addStretch(1);
  vbox2->addWidget(showGraph);

  hbox->addLayout(vbox1);
  hbox->addLayout(vbox2);
  vbox->addLayout(hbox);

  setLayout(vbox);

  connect(clear, &QPushButton::clicked, this, &ListWidget::clearItem);
  connect(add, &QPushButton::clicked, this, &ListWidget::addItem);
  connect(showGraph, &QPushButton::clicked, this, &ListWidget::showItems);


}

void ListWidget::clearItem() { //was add

  QString c_text = QInputDialog::getText(this, "Item", "Enter new item");
  QString s_text = c_text.simplified();

  if (!s_text.isEmpty()) {

    lw->addItem(s_text);
    int r = lw->count() - 1;
    lw->setCurrentRow(r);
  }
}

void ListWidget::addItem()
{

    QString c_text = QInputDialog::getText(this, "New point", "Enter new point");
    QString s_text = c_text.simplified();

    if (!s_text.isEmpty())
    {
      Coordinates* xy = new Coordinates(s_text);

      if (xy->CheckCoord())
      {
          s_text.push_front("(");
          s_text.push_back(")");

          lw->addItem(s_text);
          int r = lw->count() - 1;
          lw->setCurrentRow(r);
      }

    }
}

void ListWidget::removeItem() {

  int r = lw->currentRow();

  if (r != -1) {

    QListWidgetItem *item = lw->takeItem(r);
    delete item;
  }
}

void ListWidget::showItems(){ //was remove all

  if (lw->count() != 0)
  {
    lw->clear();
  }
}

