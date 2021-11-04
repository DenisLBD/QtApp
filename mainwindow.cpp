#include "mainwindow.h"
#include "logic.h"
#include "paint.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QFile>
#include <QTextStream>

ListWidget::ListWidget(QWidget *parent)
    : QWidget(parent)
{

  QVBoxLayout *vbox = new QVBoxLayout(this); //поменял местами this
  vbox->setSpacing(10);

  QHBoxLayout *hbox = new QHBoxLayout(); //

  QString sPoints = "Points:";
  QString sNumPoints = "0";

  text = "";

  lw = new QLabel(text, this);
  lw->setStyleSheet("QLabel {background-color: white}");

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

  // А здесь мы задаем сочетание горячих клавиш CTRL+S, которое будет выполнять действие Save
  save->setShortcut(tr("CTRL+S"));

  // В некоторых средах значки меню по умолчанию не отображаются, поэтому мы можем попробовать отключить атрибут Qt::AA_DontShowIconsInMenus
  qApp->setAttribute(Qt::AA_DontShowIconsInMenus, false);

  connect(save, &QAction::triggered, this, &ListWidget::saveFile);
  connect(open, &QAction::triggered, this, &ListWidget::openFile);


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
  vbox2->addStretch(20);
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

void ListWidget::saveFile()
{
    QTextStream out(stdout);
    QString filename = "C:\\Qt\\Apps\\QtApp\\save.txt";
    QString textToSave, frst, scnd;
    QFile file(filename);

    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream out(&file);

        for (auto iter = listOfCoordinates.begin(); iter != listOfCoordinates.end(); ++iter)
        {
            textToSave = frst.setNum(iter->first) + ',' + scnd.setNum(iter->second) + ' ';
            if (listOfCoordinates.size() % 10 == 0 && listOfCoordinates.size() > 0)
                textToSave += '\n';

            out << textToSave;
        }
    }
    else
        qWarning("Can't save file");

    file.close();
}

void ListWidget::openFile()
{
    QFile file("C:\\Qt\\Apps\\QtApp\\save.txt");

    if (!file.open(QIODevice::ReadOnly))
    {
        qWarning("Can't open file for reading");
        return;
    }

    text = "";

    QList<std::pair<int, int>> anotherList;

    QTextStream input(&file);

    while (!input.atEnd())
    {
        QString line = input.readLine();
        line = line.simplified();

        QString tmp = "";
        int i = 0;

        //проверка правильности записи координат в файле
        while (i < line.length())
        {
            while (line[i] != ' ')
            {
                tmp.push_back(line[i]);
                i++;
                if (line.length() == i)
                    break;
            }

            Coordinates *fileCoord = new Coordinates(tmp);

            if (fileCoord->CheckCoord())
            {
                tmp.push_front("(");
                tmp.push_back(") ");

                anotherList.push_back(fileCoord->GetCoord());

                if (anotherList.size() % 10 == 0 && anotherList.size() > 0)
                    text += '\n';

                text += tmp;
                tmp = "";
                i++;
                delete fileCoord;
            }
            else
            {
                qWarning("Incorrect coordinates in file");
                delete fileCoord;
                anotherList.clear();
                return;
            }
        }

        text += '\n';
    }

    listOfCoordinates.clear();
    listOfCoordinates = anotherList;
    anotherList.clear();

    int iNumPoints = listOfCoordinates.size();
    QString sNumPoints;
    sNumPoints.setNum(iNumPoints);

    numPoints->setText(sNumPoints);
    lw->setText(text);
    file.close();
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
          s_text.push_back(") ");

          if (listOfCoordinates.size() % 10 == 0 && listOfCoordinates.size() > 0)
              text += '\n';

          text += s_text;

          listOfCoordinates.push_back(xy->GetCoord());

          int iNumPoints = listOfCoordinates.size();
          QString sNumPoints;
          sNumPoints.setNum(iNumPoints);

          lw->setText(text);
          numPoints->setText(sNumPoints);
      }
      else
          qWarning("Can't add coordinate");

      delete xy;
    }
}

void ListWidget::clearItem()
{
    listOfCoordinates.clear();
    text = "";
    lw->setText("");
    numPoints->setText("0");
}

void ListWidget::showItems()
{
    if (listOfCoordinates.isEmpty())
        return;

    Coordinates *toRemove = new Coordinates("");
    toRemove->removeCoords(listOfCoordinates);
    delete toRemove;

    int iNumPoints = listOfCoordinates.size();
    QString sNumPoints;
    sNumPoints.setNum(iNumPoints);

    text = "";
    QString tmp = "", frst, scnd;

    for (auto iter = listOfCoordinates.begin(); iter != listOfCoordinates.end(); ++iter)
    {
        tmp = '(' + frst.setNum(iter->first) + ',' + scnd.setNum(iter->second) + ") ";

        if (listOfCoordinates.size() % 10 == 0 && listOfCoordinates.size() > 0)
            tmp += '\n';

        text += tmp;
        tmp = "";
    }

    lw->setText(text);
    numPoints->setText(sNumPoints);

    Frame* frame = new Frame(listOfCoordinates);

    frame->resize(400, 400);
    frame->setWindowTitle("Frame");
    frame->show();
}

