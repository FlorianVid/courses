#ifndef WINDOW_H
#define WINDOW_H

//std library
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <sstream>
//Qt widgets
#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QScrollArea>
#include <QTabWidget>
#include <QMessageBox>
#include <QListWidget>
#include <QTableWidget>
#include <QMessageBox>
//Qt layout
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QGroupBox>
#include <QGridLayout>
#include <QComboBox>
//other
#include <popupwindow.h>
//other Qt
#include <QApplication>
#include <QTextStream>
#include <QFileDialog>
#include <QHeaderView>
#include <QDialog>
#include <QDebug>

class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = nullptr);

private:
    QString m_nameWindow;
    QFont m_font;
    bool m_unitOrMass;//if true => unit otherwise mass in kg
    QTableWidget *m_listeCourses;
    QTabWidget *m_tabWidget;
    std::map<std::tuple<QString, bool>, float> m_listeCoursesNombre;
    PopUpWindow *m_popUp;

    QFrame* createFrame(std::vector<QString> listeLegumes, QWidget* tabLegumes);
    void connectToQuantityButton(QList<QPushButton*> listButtons);
    std::vector<QString> readFile(std::string path);
    QGroupBox *createExclusiveGroup();
signals:

private slots:
    void ajoutAliment();
    void razListe();
    void saveToFile();
    void onToggled(bool checked);
    void removeItemFunction();
    void getQuantity();
};

#endif // WINDOW_H
