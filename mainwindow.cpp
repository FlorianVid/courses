#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "databasemanager.h"
#include "courses.h"
#include "aliment.h"

bool is_double(const std::string& s);
bool is_integer(const std::string& s);
bool is_vowel (wchar_t c);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(this->size());

    m_unitOrMass = true;
    m_unitOrMassTemp = true;

    readFileAddVegetablesButtons();
    readFileAddFruitsButtons();
    readFileAddMeatButtons();

    ui->tableListeCourses->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableListeCourses->verticalHeader()->setVisible(false);
    ui->tableListeCourses->horizontalHeader()->setVisible(false);
    ui->tableListeCourses->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableListeCourses_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableListeCourses_2->verticalHeader()->setVisible(false);
    ui->tableListeCourses_2->horizontalHeader()->setVisible(false);
    ui->tableListeCourses_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->buttonUnit->setChecked(true);
    connect(ui->buttonMasse, &QRadioButton::toggled, this, &MainWindow::switchMassUnit);
    connect(ui->buttonUnit, &QRadioButton::toggled, this, &MainWindow::switchMassUnit);

    connect(ui->buttonRAZ, SIGNAL (clicked()), this, SLOT (razListe()));
    connect(ui->buttonSave, SIGNAL (clicked()), this, SLOT (saveToFile()));
    connect(ui->buttonRemove, SIGNAL (clicked()), this, SLOT (removeItemFunction()));
    connect(ui->buttonModify, SIGNAL (clicked()), this, SLOT (modifyItemFunction()));
    connect(ui->buttonValidate, SIGNAL (clicked()), this, SLOT (validateCourses()));

    unvalidateCourses();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readFileAddVegetablesButtons()
{
    std::string path = "C:/Users/fvida/Documents/codeQt/raggamuffin/data/legumes.txt";
    std::vector<QString> listeLegumes;
    std::vector<double> listeMassPerUnit;
    std::ifstream dataFile(path);
    if(!dataFile)
        std::cerr << "No data ?" << std::endl;

    std::string line;
    std::string delimiter = ",";//delimiter in the data files for food and mass per unit
    while (getline(dataFile, line)) {
        std::string name = line.substr(0, line.find(delimiter));
        // convert string to lower case
        std::for_each(name.begin(), name.end(), [](char & c){
            c = ::tolower(c);
        });
        listeLegumes.push_back(QString::fromStdString(name));

        std::string massPerUnitString = line.substr(line.find(delimiter) + 1, line.size());
        if(is_double(massPerUnitString)) {
            listeMassPerUnit.push_back(stod(massPerUnitString));
        } else {
            listeMassPerUnit.push_back(nan(""));
        }
    }
    dataFile.close();

    int nbLegumes = listeLegumes.size();
    QPushButton* buttonLegumes[nbLegumes];
    for (int i = 0 ; i < nbLegumes ; i++) {
        buttonLegumes[i] = new QPushButtonAliment(listeLegumes.at(i), ui->tabLegumes,"legume",listeMassPerUnit.at(i));
        buttonLegumes[i]->setObjectName(listeLegumes.at(i));
        //buttonLegumes[i]->setFont(m_basicFont);
    }

    QGridLayout *layoutLegumes = new QGridLayout(ui->tabLegumes);//3 items per row
    for (int i = 0 ; i < nbLegumes ; i++) {
        layoutLegumes->addWidget(buttonLegumes[i], i/3, i%3);
    }

    for (const auto &button : buttonLegumes ) {
        connect(button, SIGNAL (clicked()), this, SLOT (getQuantity()));//getQuantity
    }
}

void MainWindow::readFileAddFruitsButtons()
{
    std::string path = "C:/Users/fvida/Documents/codeQt/raggamuffin/data/fruits.txt";
    std::vector<QString> listeFruits;
    std::vector<double> listeMassPerUnit;
    std::ifstream dataFile(path);
    if(!dataFile)
        std::cerr << "No data ?" << std::endl;

    std::string line;
    std::string delimiter = ",";//delimiter in the data files for food and mass per unit
    while (getline(dataFile, line)) {
        std::string name = line.substr(0, line.find(delimiter));
        // convert string to lower case
        std::for_each(name.begin(), name.end(), [](char & c){
            c = ::tolower(c);
        });
        listeFruits.push_back(QString::fromStdString(name));

        std::string massPerUnitString = line.substr(line.find(delimiter) + 1, line.size());
        if(is_double(massPerUnitString)) {
            listeMassPerUnit.push_back(stod(massPerUnitString));
        } else {
            listeMassPerUnit.push_back(nan(""));
        }
    }
    dataFile.close();

    int nbFruits = listeFruits.size();
    QPushButton* buttonFruits[nbFruits];
    for (int i = 0 ; i < nbFruits ; i++) {
        buttonFruits[i] = new QPushButtonAliment(listeFruits.at(i), ui->tabFruits, "fruit",listeMassPerUnit.at(i));
        buttonFruits[i]->setObjectName(listeFruits.at(i));
    }

    QGridLayout *layoutFruits = new QGridLayout(ui->tabFruits);//3 items per row
    for (int i = 0 ; i < nbFruits ; i++) {
        layoutFruits->addWidget(buttonFruits[i], i/3, i%3);
    }

    for (const auto &button : buttonFruits ) {
        connect(button, SIGNAL (clicked()), this, SLOT (getQuantity()));//getQuantity
    }
}

void MainWindow::readFileAddMeatButtons()
{
    std::string path = "C:/Users/fvida/Documents/codeQt/raggamuffin/data/viandes.txt";
    std::vector<QString> listeViande;
    std::vector<double> listeMassPerUnit;
    std::ifstream dataFile(path);
    if(!dataFile)
        std::cerr << "No data ?" << std::endl;
    std::string line;
    std::string delimiter = ",";//delimiter in the data files for food and mass per unit
    while (getline(dataFile, line)) {
        std::string name = line.substr(0, line.find(delimiter));
        // convert string to lower case
        std::for_each(name.begin(), name.end(), [](char & c){
            c = ::tolower(c);
        });
        listeViande.push_back(QString::fromStdString(name));

        std::string massPerUnitString = line.substr(line.find(delimiter) + 1, line.size());
        if(is_double(massPerUnitString)) {
            listeMassPerUnit.push_back(stod(massPerUnitString));
        } else {
            listeMassPerUnit.push_back(nan(""));
        }
    }
    dataFile.close();

    int nbViande = listeViande.size();
    QPushButton* buttonViande[nbViande];
    for (int i = 0 ; i < nbViande ; i++) {
        buttonViande[i] = new QPushButtonAliment(listeViande.at(i), ui->tabViandes,"viande",listeMassPerUnit.at(i));
        buttonViande[i]->setObjectName(listeViande.at(i));
    }

    QGridLayout *layoutLegumes = new QGridLayout(ui->tabViandes);//3 items per row
    for (int i = 0 ; i < nbViande ; i++) {
        layoutLegumes->addWidget(buttonViande[i], i/3, i%3);
    }

    for (const auto &button : buttonViande ) {
        connect(button, SIGNAL (clicked()), this, SLOT (getQuantity()));//getQuantity
    }
}

void MainWindow::getQuantity(std::string chosenFood, double initValue)
{
    QPushButton * pushedButton = (QPushButton *) sender();

    const char* stringUnitMass;
    if (m_unitOrMass)
        stringUnitMass = " en unité";
    else {
        stringUnitMass = " en masse (kg)";
    }

    if(chosenFood == "")
        chosenFood = pushedButton->text().toStdString();
    wchar_t firstChar = chosenFood[0];
    firstChar = ::tolower(firstChar);
    chosenFood[0] = firstChar;
    std::string addedFood;

    if (initValue > 0) {//no initial value
        if (is_vowel(firstChar))
            addedFood = "Quantité mise à jour d'" + chosenFood + stringUnitMass;
        else {
            addedFood = "Quantité mise à jour de " + chosenFood + stringUnitMass;
        }
    } else {
        if (is_vowel(firstChar))
            addedFood = "Quantité sélectionnée d'" + chosenFood + stringUnitMass;
        else {
            addedFood = "Quantité sélectionnée de " + chosenFood + stringUnitMass;
        }
    }
    const char* c_addedFood = addedFood.c_str();

    QInputDialog *popUp = new QInputDialog;
    popUp->setInputMode(QInputDialog::DoubleInput);

    connect(popUp, &QInputDialog::doubleValueSelected, this, &MainWindow::ajoutAliment);

    bool ok;
    double quantity = popUp->getDouble(this, tr("Ajout d'aliment"),
                                         tr(c_addedFood), initValue,
                                         0,100,1,&ok,Qt::WindowFlags(),0.1);

    popUp->setTextValue(QString(tr(chosenFood.c_str())));

    unvalidateCourses();

    emit popUp->doubleValueSelected(quantity);

}

void MainWindow::ajoutAliment(double quantity)
{
    QInputDialog * popUp = (QInputDialog *) sender();

    QString foodName = popUp->textValue();

    ui->tableListeCourses->clear();
    ui->tableListeCourses->setRowCount(0);
    ui->tableListeCourses->setColumnCount(1);

    std::tuple<QString, bool> temp2 = {foodName, m_unitOrMass};

    QPushButtonAliment* correspButton = ui->tabFruits->findChild<QPushButtonAliment*>(foodName);
    if(correspButton == nullptr) {
        correspButton = ui->tabLegumes->findChild<QPushButtonAliment*>(foodName);
        if(correspButton == nullptr) {
            correspButton = ui->tabViandes->findChild<QPushButtonAliment*>(foodName);
            if(correspButton == nullptr) {
                std::cerr << "QPushButtonAliment correspondant à l'aliment ajouté pas trouvé" << std::endl;
            }
        }
    }

    if(m_unitOrMass) { //need to convert quantity to mass
        m_listeCoursesNombre[temp2] = Aliment(foodName, quantity*correspButton->getMassPerUnit(), correspButton->getCategory(),quantity) ;// + m_listeCoursesNombre[temp2].getQuantity()
    } else {
        m_listeCoursesNombre[temp2] = Aliment(foodName, quantity, correspButton->getCategory()) ;// + m_listeCoursesNombre[temp2].getQuantity()
    }

    for(auto const& a : m_listeCoursesNombre) {
        qDebug() << a.second.getCategory();
    }

    updateListeCourses(ui->tableListeCourses);
    m_unitOrMass = m_unitOrMassTemp;
}

void MainWindow::switchMassUnit(bool checked)
{
    if(checked){
        //btn is Checked
        QRadioButton *btn = static_cast<QRadioButton *>(sender());
        if(btn->text() == "Masse (kg)") {
            m_unitOrMass = false;
            m_unitOrMassTemp = false;
        } else {
            m_unitOrMass = true;
            m_unitOrMassTemp = true;
        }
    }
}

void MainWindow::razListe()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, tr("RAZ"), tr("Ok pour RAZ la liste ?") ,
                                    QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        m_listeCoursesNombre.clear();
        ui->tableListeCourses->clear();//->setText(temp);
    }
    unvalidateCourses();
}

void MainWindow::saveToFile()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Enregistrer la liste de courses"),
                                                    "",
                                                    tr("fichier texte (*.txt);;All Files (*)"));
    //open file
    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::information(this, tr("Unable to open file"),
                file.errorString());
            return;
        }

        QTextStream out(&file);// bug d'affichage dans le txt avec QDataStream

        for (auto const &j : m_listeCoursesNombre) {
            std::tuple<QString, bool> temp2 = j.first;
            QString listItem = std::get<0>(temp2);

            if (!std::get<1>(temp2)) {
                if(j.second.getMass() > 1)
                    out << (QString::number(j.second.getMass()) + " kg " + listItem + "s\n");
                else
                    out << (QString::number(j.second.getMass()) + " kg " + listItem + "\n");
            } else {
            if(j.second.getNbUnit() > 1)
                out << (QString::number(j.second.getNbUnit()) + " " + listItem + "s\n");
            else
                out << (QString::number(j.second.getNbUnit()) + " " + listItem + "\n");
            }
        }
    }
}

void MainWindow::removeItemFunction(bool quietRemove)
{
    if (ui->tableListeCourses->currentIndex().isValid()) {
        int curRow = ui->tableListeCourses->currentRow();
        QTableWidgetItem *curItem = ui->tableListeCourses->currentItem();
        QStringList listWords = curItem->text().split(" ");
        QString lastWord = listWords.last();

        std::vector<std::tuple<QString, bool>> listKeys;
        for(auto const & it : m_listeCoursesNombre) {
            listKeys.push_back(it.first);
        }
        for (auto const & it : listKeys) {
            if((lastWord == std::get<0>(it)) ||
               (lastWord==(std::get<0>(it) + QString("s")))||
               (lastWord == (std::get<0>(it) + QString("z")))) {
                if (quietRemove == false) {
                    QMessageBox popUp = QMessageBox(QMessageBox::Information,this->windowTitle(),
                                                    "Ingrédient : " + lastWord + " enlevé de la liste");
                    //popUp.setFont(m_basicFont);
                    popUp.exec();
                }
                m_listeCoursesNombre.erase(it);
                break;
            }
        }
        ui->tableListeCourses->removeRow(curRow);
    }
    unvalidateCourses();
}

std::tuple<QString, bool, double> MainWindow::findItemToModify() const
{
    if (ui->tableListeCourses->currentIndex().isValid()) {
        QTableWidgetItem *curItem = ui->tableListeCourses->currentItem();
        QStringList listWords = curItem->text().split(" ");
        QString lastWord = listWords.last();

        std::vector<std::tuple<QString, bool>> listKeys;
        for(auto const & it : m_listeCoursesNombre) {
            listKeys.push_back(it.first);
        }
        for (auto const & it : listKeys) {
            if((lastWord == std::get<0>(it)) ||
               (lastWord==(std::get<0>(it) + QString("s")))||
               (lastWord == (std::get<0>(it) + QString("z")))) {
                double nbFood = 0;
                if(std::get<1>(it)) {
                    nbFood = m_listeCoursesNombre.at(it).getNbUnit();
                } else {
                    nbFood = m_listeCoursesNombre.at(it).getMass();
                }

                return (std::make_tuple(std::get<0>(it), std::get<1>(it), nbFood));
            }
        }
    }
    std::cerr << "Element to modify not found" << std::endl;
}

void MainWindow::modifyItemFunction()
{
    if (ui->tableListeCourses->currentIndex().isValid()) {

        std::tuple<QString, bool, double> data2modify = findItemToModify();

        std::string qstion = "";
        if (std::get<1>(data2modify) == true)
            qstion = "Voulez-vous rester en unité ?";
        else {
            qstion = "Voulez-vous rester en kg ?";
        }

        QMessageBox::StandardButton reply = QMessageBox::question(this, tr("Modifier la quantité de l'aliment"), tr(qstion.c_str()) ,
                                        QMessageBox::Yes|QMessageBox::No);

        if (reply == QMessageBox::No) {
            m_unitOrMass = !std::get<1>(data2modify);
            removeItemFunction(true);
        } else {
            m_unitOrMass = std::get<1>(data2modify);
        }

        double initValue = std::get<2>(data2modify);

        getQuantity(std::get<0>(data2modify).toStdString(), initValue);
    }
    unvalidateCourses();
}

void MainWindow::validateCourses()
{
    std::vector<Aliment> listeAliments;
    double totProt = 0;
    if (m_listeCoursesNombre.size() > 0) {
        ui->tabMain->setTabEnabled(1,true);
        ui->tabMain->setTabEnabled(2,true);

        bool ok;
        Courses crs;
        QString text = QInputDialog::getText(this, this->windowTitle(),
                                             tr("Identifiant pour les courses :"), QLineEdit::Normal,
                                             "id courses", &ok);
        if (ok && !text.isEmpty())
            crs = Courses(text);

        ui->tableListeCourses_2->setRowCount(0);
        ui->tableListeCourses_2->setColumnCount(1);
        updateListeCourses(ui->tableListeCourses_2);

        //db management
        DatabaseManager& dbMng = DatabaseManager::instance();
        dbMng.m_coursesDao.addCourses(crs);

        for(auto& alim : m_listeCoursesNombre) {
            dbMng.m_alimentDao.addAlimentInCourses(alim.second,crs.getId());
            listeAliments.push_back(alim.second);

            totProt += alim.second.getNut().protein;

        }
        ui->labelNameCourses->setText(text);
        ui->labelTotProt->setText(QString::number(totProt) + tr(" g de protéines"));

    } else {
        QMessageBox popUp = QMessageBox(QMessageBox::Information,this->windowTitle(),
                                        "Ajoutez des aliments à la liste de courses.");
        popUp.exec();
    }
}

void MainWindow::unvalidateCourses() const
{
    ui->tabMain->setTabEnabled(1,false);
    ui->tabMain->setTabEnabled(2,false);
}

void MainWindow:: updateListeCourses(QTableWidget* tab) const
{
    int row = 0;
    for (auto const &j : m_listeCoursesNombre) {
        if (j.second.getMass() < 0.001)
            continue;
        QTableWidgetItem *itemList;
        std::tuple<QString, bool> temp2 = j.first;
        QString listItem = std::get<0>(temp2);
        bool boolItem = std::get<1>(temp2);
        std::istringstream record(listItem.toStdString());
        std::string fullWord;
        std::string word;
        record >> word;
        if( (j.second.getNbUnit() <= 1 && j.second.getMass() <= 1) || word.back() == 's' || word.back() == 'z')
            fullWord = word;
        else {
            fullWord = word + "s";
        }
        while(record >> word) {
            fullWord = fullWord + " " + word;
        }
        if (boolItem)
            itemList = new QTableWidgetItem(QString::number(j.second.getNbUnit()) + " " + QString::fromStdString(fullWord));
        else
            itemList = new QTableWidgetItem(QString::number(j.second.getMass()) + " kg " + QString::fromStdString(fullWord));

        tab->insertRow(row);
        tab->setItem(row,0,itemList);
    }
}


bool is_double(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](unsigned char c) { return !( (std::isdigit(c)) | (c == '.')); }) == s.end();
}

bool is_integer(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](unsigned char c) { return !( (std::isdigit(c)) ); }) == s.end();
}

bool is_vowel (wchar_t c)
{
    wchar_t vowel[] = {'a','e',L'é',L'è','u','i','o','y',L'à','h'};
    wchar_t* end = vowel + sizeof(vowel) / sizeof(vowel[0]);
    wchar_t* position = std::find(vowel, end, c);

    return (position != end);
}
