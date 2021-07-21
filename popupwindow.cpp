#include "popupwindow.h"

PopUpWindow::PopUpWindow(QWidget *parent, bool unitOrMass) :
    QWidget(parent), m_unitOrMass(unitOrMass)
{
    setFixedSize(600, 100);
    QFont font("Times", 15);

    QGridLayout *grid = new QGridLayout;

    std::string unitorMassStr;

    if (unitOrMass)
    {
        unitorMassStr = "en unité";
    }
    else
    {
        unitorMassStr = "masse (kg)";
    }

    m_fieldQuantity = new QLineEdit(QString::fromStdString("Quantité sélectionnée : " + unitorMassStr),this);
    m_fieldQuantity->setFont(font);
    grid->addWidget(m_fieldQuantity, 0, 0);

    QPushButton* m_confirmationButton = new QPushButton("Confirmer",this);
    m_confirmationButton->setObjectName("ConfirmationButton");
    m_confirmationButton->setGeometry(200,50,200,70);
    m_confirmationButton->setFont(font);

    grid->addWidget(m_confirmationButton, 0, 1);

    setLayout(grid);
}

void PopUpWindow::setUnitOrMass(bool unitOrMass)
{
    m_unitOrMass = unitOrMass;
//    std::cout << unitOrMass << std::endl;

    std::string unitorMassStr;
    if (unitOrMass)
    {
        unitorMassStr = "en unité";
    }
    else
    {
        unitorMassStr = "masse (kg)";
    }
    //std::cout << unitorMassStr << std::endl;
    m_fieldQuantity->setText(QString::fromStdString("Quantité sélectionnée : " + unitorMassStr));
    //m_fieldQuantity->selectAll();
    QTimer::singleShot(1, [this](){
        m_fieldQuantity->selectAll();
        m_fieldQuantity->setFocus();
    });
}

void PopUpWindow::setIngredientButton(QPushButton * but)
{
    m_ingredientButton = but;
    //m_confirmationButton->setText(m_ingredientButton->text());
}

QPushButton* PopUpWindow::getIngredientButton()
{
    return m_ingredientButton;
}

std::string PopUpWindow::getContentTextLine()
{
    return m_fieldQuantity->text().toLocal8Bit().constData();
}
