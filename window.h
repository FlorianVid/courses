#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QApplication>
#include <QLabel>
#include <QScrollArea>
#include <QTabWidget>
#include <map>
#include <tuple>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <vector>
#include <QFileDialog>
#include <fstream>
#include <iostream>
#include <string>
#include <QMessageBox>
#include <QTextStream>
#include <QGridLayout>
#include <sstream>
#include <QRadioButton>
#include <QGroupBox>
#include <QTableWidget>
#include <QHeaderView>
#include <QMessageBox>
#include <stdlib.h>     /* strtol */
#include <QListWidget>
#include <popupwindow.h>
#include <QComboBox>


class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = nullptr);

private:
    bool m_unitOrMass;//if true => unit otherwise mass in kg
    QTableWidget *m_listeCourses;
    QTabWidget *m_tabWidget;
    std::map<std::tuple<QString, bool>, float> m_listeCoursesNombre;
    PopUpWindow *m_popUp;


    QFrame* createFrame(std::vector<QString> listeLegumes, QWidget* tabLegumes, QFont font);
    void connectToQuantityButton(QList<QPushButton*> listButtons);
    std::vector<QString> readFile(std::string path);
    QGroupBox *createExclusiveGroup(QFont font);
signals:

public slots:
    void ajoutAliment();
    void razListe();
    void saveToFile();
    void onToggled(bool checked);
    void removeItemFunction();
    void getQuantity();

    void addIngredientDatabase(QLineEdit* echoLineEdit, QComboBox *echoComboBox);
};

#endif // WINDOW_H
