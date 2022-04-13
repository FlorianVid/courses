#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//std library
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <sstream>
#include <cmath>
#include <memory>
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
//Qt charts
#include <QBarSet>
#include <QBarSeries>
#include <QChart>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QChartView>
//other Qt
#include <QApplication>
#include <QTextStream>
#include <QFileDialog>
#include <QHeaderView>
#include <QInputDialog>
#include <QDebug>
//other not Qt
#include "aliment.h"
#include "qpushbuttonaliment.h"
#include "courses.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    bool m_unitOrMass;//if true => unit otherwise mass in kg
    bool m_unitOrMassTemp;//if true => unit otherwise mass in kg used when an ingredient is added with different unit/mass
    std::map<std::tuple<QString, bool>, Aliment> m_listeCoursesNombre;//name, unit or mass?, Aliment
    Ui::MainWindow *ui;
    Courses m_crs;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void updateListeCourses(QTableWidget* tab) const;
    void updateBarChart() const;

private slots:
    void readFileAddVegetablesButtons();
    void readFileAddFruitsButtons();
    void readFileAddMeatButtons();
    int getQuantity(std::string chosenFood = "", double initValue = 0);
    void ajoutAliment(double quantity);
    void switchMassUnit(bool checked);
    void razListe();
    void saveToFile();
    void removeItemFunction(bool quietRemove = false);
    std::tuple<QString, bool, double> findItemToModify() const;
    void modifyItemFunction();
    void validateCourses(bool nouvellesCourses = true);
    void unvalidateCourses() const;
    void validateNutri() const;




};
#endif // MAINWINDOW_H
