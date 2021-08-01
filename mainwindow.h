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
//other Qt
#include <QApplication>
#include <QTextStream>
#include <QFileDialog>
#include <QHeaderView>
#include <QInputDialog>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    bool m_unitOrMass;//if true => unit otherwise mass in kg
    bool m_unitOrMassTemp;//if true => unit otherwise mass in kg
    std::map<std::tuple<QString, bool>, double> m_listeCoursesNombre;
    Ui::MainWindow *ui;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void updateListeCourses(QTableWidget* tab) const;

private slots:
    void readFileAddVegetablesButtons();
    void readFileAddFruitsButtons();
    void readFileAddMeatButtons();
    void getQuantity(std::string chosenFood = "", double initValue = 0);
    void ajoutAlimentAbsolu(double quantity);
    void ajoutAlimentRelatif(double quantity);
    void switchMassUnit(bool checked);
    void razListe();
    void saveToFile();
    void removeItemFunction(bool quietRemove = false);
    std::tuple<QString, bool, double> findItemToModify() const;
    void modifyItemFunction();
    void validateCourses();
    void unvalidateCourses() const;



};
#endif // MAINWINDOW_H
