#ifndef POPUPWINDOW_H
#define POPUPWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QString>
#include <QGridLayout>
#include <string>
#include <iostream>
#include <QTimer>


class PopUpWindow : public QWidget
{
    Q_OBJECT
public:
    explicit PopUpWindow(QWidget *parent = nullptr, bool unitOrMass = true);
            //QPushButton *confirmationButton = nullptr);

    void setUnitOrMass(bool unitOrMass);
    //QPushButton* getConfirmationButton();
    void setIngredientButton(QPushButton * but);
    QPushButton* getIngredientButton();
    std::string getContentTextLine();
private:
    bool m_unitOrMass;//if true => unit otherwise mass in kg
    QLineEdit *m_fieldQuantity;
    QPushButton *m_confirmationButton;
    QPushButton *m_ingredientButton;

signals:

};

#endif // POPUPWINDOW_H
