#include "window.h"

bool is_double(const std::string& s);
bool is_integer(const std::string& s);
bool is_vowel (wchar_t c);

Window::Window(QWidget *parent) : QWidget(parent)
{
    QString m_nameWindow = QString("Courses");
    this->setWindowTitle(m_nameWindow);
    // Set size of the window
    m_unitOrMass = true;
    m_unitOrMassTemp = true;

    setFixedSize(1500, 700);
    QFont m_font("Times", 15);

    //global layout
    QGridLayout *grid = new QGridLayout;

    QHBoxLayout *hbox = new QHBoxLayout;
    QLabel *entete = new QLabel(tr("Comment donner la quantité ?"),this);
    entete->setFont(m_font);

    //mode: either mass or units
    QGroupBox *radioButtonUnitMass= createExclusiveGroup();
    //grid->addWidget(radioButtonUnitMass, 0, 1);

    hbox->addWidget(entete);
    hbox->addWidget(radioButtonUnitMass);
    QGroupBox *groupBoxQuantity = new QGroupBox(this);
    groupBoxQuantity->setLayout(hbox);
    grid->addWidget(groupBoxQuantity, 0,0,1,2, Qt::AlignLeft);

    std::vector<QString> listeLegumes = readFile("C:/Users/fvida/Documents/codeQt/courses/data/legumes.txt");
    std::vector<QString> listeFruits = readFile("C:/Users/fvida/Documents/codeQt/courses/data/fruits.txt");
    std::vector<QString> listeViandes = readFile("C:/Users/fvida/Documents/codeQt/courses/data/viandes.txt");

    m_tabWidget = new QTabWidget(this);
    m_tabWidget->setFont(m_font);
    m_tabWidget->setGeometry(10, 100, 560, 450);

    QWidget *tabLegumes = new QWidget();
    QWidget *tabFruits = new QWidget();
    QWidget *tabViandes= new QWidget();

    //create frame for each tab
    QFrame* frameLegumes = createFrame(listeLegumes, tabLegumes);
    QFrame* frameFruits = createFrame(listeFruits, tabFruits);
    QFrame* frameViandes = createFrame(listeViandes, tabViandes);

    m_tabWidget->addTab(frameLegumes,"Légumes");
    m_tabWidget->addTab(frameFruits,"Fruits");
    m_tabWidget->addTab(frameViandes,"Viandes");

    grid->addWidget(m_tabWidget, 1, 0);

    m_listeCourses = new QTableWidget(10, 1, this);
    m_listeCourses->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_listeCourses->verticalHeader()->setVisible(false);
    m_listeCourses->horizontalHeader()->setVisible(false);
    m_listeCourses->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    m_listeCourses->setFont(m_font);

    QPushButton* saveListe = new QPushButton(this);
    saveListe->setText("Enregistrer la liste des courses");
    saveListe->setFont(m_font);
    //saveListe->setGeometry(600, 450, 350, 40);

    QPushButton* razListe = new QPushButton(this);
    razListe->setText("RAZ de la liste des courses");
    razListe->setFont(m_font);
    //razListe->setGeometry(600, 510, 350, 40);

    QPushButton* removeItem = new QPushButton(this);
    removeItem->setText("Enlever l'ingrédient");
    removeItem->setFont(m_font);
    //removeItem->setGeometry(600, 510, 350, 40);

    QPushButton* modifyItem = new QPushButton(this);
    modifyItem->setText("Modifier la quantité de l'aliment");
    modifyItem->setFont(m_font);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(m_listeCourses);
    vbox->addWidget(saveListe);
    vbox->addWidget(removeItem);
    vbox->addWidget(modifyItem);
    vbox->addWidget(razListe);

    QGroupBox *groupBox = new QGroupBox(this);
    groupBox->setLayout(vbox);
    grid->addWidget(groupBox, 1,1,2,1);

    setLayout(grid);

    QList<QPushButton*> buttonLegumes = frameLegumes->findChildren<QPushButton*>();
    QList<QPushButton*> buttonFruits = frameFruits->findChildren<QPushButton*>();
    QList<QPushButton*> buttonViandes = frameViandes->findChildren<QPushButton*>();

    connectToQuantityButton(buttonLegumes);
    connectToQuantityButton(buttonFruits);
    connectToQuantityButton(buttonViandes);

    connect(razListe, SIGNAL (clicked()), this, SLOT (razListe()));
    connect(saveListe, SIGNAL (clicked()), this, SLOT (saveToFile()));
    connect(removeItem, SIGNAL (clicked()), this, SLOT (removeItemFunction()));
    connect(modifyItem, SIGNAL (clicked()), this, SLOT (modifyItemFunction()));
}

void Window::ajoutAlimentAbsolu(double quantity)
{
    QInputDialog * popUp = (QInputDialog *) sender();

    QString foodName = popUp->textValue();

    this->m_listeCourses->clear();
    this->m_listeCourses->setRowCount(0);

    if(m_unitOrMass) {
        std::tuple<QString, bool> temp2 = {foodName, m_unitOrMass};
        m_listeCoursesNombre[temp2] = quantity;
    } else {
        std::tuple<QString, bool> temp2 = {foodName, m_unitOrMass};
        m_listeCoursesNombre[temp2] = quantity;
    }
    int row = 0;
    for (auto const &j : m_listeCoursesNombre) {
        QTableWidgetItem *itemList;
        std::tuple<QString, bool> temp2 = j.first;
        QString listItem = std::get<0>(temp2);
        bool boolItem = std::get<1>(temp2);
        std::istringstream record(listItem.toStdString());
        std::string fullWord;
        std::string word;
        record >> word;
        if(j.second <= 1 || word.back() == 's' || word.back() == 'z')
            fullWord = word;
        else {
            fullWord = word + "s";
        }
        while(record >> word) {
            fullWord = fullWord + " " + word;
        }
        if (boolItem)
            itemList = new QTableWidgetItem(QString::number(j.second) + " " + QString::fromStdString(fullWord));
        else
            itemList = new QTableWidgetItem(QString::number(j.second) + " kg " + QString::fromStdString(fullWord));

        this->m_listeCourses->insertRow(row);
        this->m_listeCourses->setItem(row,0,itemList);
    }
    m_unitOrMass = m_unitOrMassTemp;
}

void Window::ajoutAlimentRelatif(double quantity)
{
    QInputDialog * popUp = (QInputDialog *) sender();

    QString foodName = popUp->textValue();

    std::cout << quantity << " " << foodName.toStdString() << std::endl;

    this->m_listeCourses->clear();
    this->m_listeCourses->setRowCount(0);

    if(m_unitOrMass) {
        std::tuple<QString, bool> temp2 = {foodName, m_unitOrMass};
        for (int i = 0; i< quantity; ++i) {
            ++m_listeCoursesNombre[temp2];
        }
    } else {
        std::tuple<QString, bool> temp2 = {foodName, m_unitOrMass};
        m_listeCoursesNombre[temp2] = m_listeCoursesNombre[temp2] + quantity;//0.05;
    }
    int row = 0;
    for (auto const &j : m_listeCoursesNombre) {
        QTableWidgetItem *itemList;
        std::tuple<QString, bool> temp2 = j.first;
        QString listItem = std::get<0>(temp2);
        bool boolItem = std::get<1>(temp2);
        std::istringstream record(listItem.toStdString());
        std::string fullWord;
        std::string word;
        record >> word;
        if(j.second <= 1 || word.back() == 's' || word.back() == 'z')
            fullWord = word;
        else {
            fullWord = word + "s";
        }
        while(record >> word) {
            fullWord = fullWord + " " + word;
        }
        if (boolItem)
            itemList = new QTableWidgetItem(QString::number(j.second) + " " + QString::fromStdString(fullWord));
        else
            itemList = new QTableWidgetItem(QString::number(j.second) + " kg " + QString::fromStdString(fullWord));

        this->m_listeCourses->insertRow(row);
        this->m_listeCourses->setItem(row,0,itemList);
    }
    m_unitOrMass = m_unitOrMassTemp;
}

void Window::razListe()
{
    m_listeCoursesNombre.clear();
    //QString temp = "";
    this->m_listeCourses->clear();//->setText(temp);
}

QFrame* Window::createFrame(std::vector<QString> listeLegumes, QWidget* tabLegumes)
{
    int nbLegumes = listeLegumes.size();
    QPushButton* buttonLegumes[nbLegumes];
    for (int i = 0 ; i < nbLegumes ; i++) {
        buttonLegumes[i] = new QPushButton(listeLegumes.at(i), tabLegumes);
        buttonLegumes[i]->setFont(m_font);
    }

    QFrame *frameLegumes= new QFrame(this);
    //QVBoxLayout *layoutLegumes = new QVBoxLayout(tabLegumes);
    QGridLayout *layoutLegumes = new QGridLayout(tabLegumes);//3 items per row
    for (int i = 0 ; i < nbLegumes ; i++) {
        layoutLegumes->addWidget(buttonLegumes[i], i/3, i%3);
    }
    frameLegumes->setLayout(layoutLegumes);

    return frameLegumes;
}

std::vector<QString> Window::readFile(std::string path) const
{
    std::vector<QString> listeLegumes;
    std::ifstream dataFile(path);
    if(!dataFile)
        std::cerr << "No data ?" << std::endl;
    std::string line;
    while (getline(dataFile, line)) {
        listeLegumes.push_back(QString::fromStdString(line));
    }
    dataFile.close();
    return listeLegumes;
}

void Window::saveToFile()
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

            if (!std::get<1>(temp2))
                if(j.second > 1)
                    out << (QString::number(j.second) + " kg " + listItem + "s\n");
                else
                    out << (QString::number(j.second) + " kg " + listItem + "\n");
            else
            {
            if(j.second > 1)
                out << (QString::number(j.second) + " " + listItem + "s\n");
            else
                out << (QString::number(j.second) + " " + listItem + "\n");
            }
        }
    }
}

QGroupBox *Window::createExclusiveGroup()
{
    QGroupBox *groupBox = new QGroupBox(this);
    groupBox -> setFont(m_font);
    groupBox->setGeometry(10, 10, 350, 40);

    QRadioButton *radio2 = new QRadioButton(tr("Masse (kg)"));
    radio2->setFont(m_font);
    connect(radio2, &QRadioButton::toggled, this, &Window::onToggled);
    QRadioButton *radio1 = new QRadioButton(tr("Unité"));
    connect(radio1, &QRadioButton::toggled, this, &Window::onToggled);
    radio1->setFont(m_font);

    radio1->setChecked(true);

    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(radio1);
    hbox->addWidget(radio2);
    //hbox->addStretch(0);
    hbox->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    groupBox->setLayout(hbox);

    return groupBox;
}

void Window::onToggled(bool checked)
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

void Window::removeItemFunction(bool quietRemove)
{
    if (m_listeCourses->currentIndex().isValid()) {
        int curRow = m_listeCourses->currentRow();
        QTableWidgetItem *curItem = m_listeCourses->currentItem();
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
                    QMessageBox popUp = QMessageBox(QMessageBox::Information,m_nameWindow,"Ingrédient : " + lastWord + " enlevé de la liste");
                    popUp.setFont(m_font);
                    popUp.exec();
                } else {
                    m_listeCoursesNombre.erase(it);
                }
            }
        }
        m_listeCourses->removeRow(curRow);
    }
}

std::tuple<QString, bool, double> Window::findItemToModify() const
{
    if (m_listeCourses->currentIndex().isValid()) {
        QTableWidgetItem *curItem = m_listeCourses->currentItem();
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
                double nbFood = m_listeCoursesNombre.at(it);
                return (std::make_tuple(std::get<0>(it), std::get<1>(it), nbFood));
            }
        }
    }
    std::cerr << "Element to modify not found" << std::endl;
}

void Window::modifyItemFunction()
{
    if (m_listeCourses->currentIndex().isValid()) {

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
}

void Window::getQuantity(std::string chosenFood, double initValue)
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
    if (is_vowel(firstChar))
        addedFood = "Quantité sélectionnée d'" + chosenFood + stringUnitMass;
    else {
        addedFood = "Quantité sélectionnée de " + chosenFood + stringUnitMass;
    }
    const char* c_addedFood = addedFood.c_str();

    QInputDialog *popUp = new QInputDialog;
    popUp->setFont(m_font);
    popUp->setInputMode(QInputDialog::DoubleInput);

    if (initValue > 0) //no initial value
        connect(popUp, &QInputDialog::doubleValueSelected, this, &Window::ajoutAlimentAbsolu);
    else {
        connect(popUp, &QInputDialog::doubleValueSelected, this, &Window::ajoutAlimentRelatif);
    }


    bool ok;
    double quantity = popUp->getDouble(this, tr("Ajout d'aliment"),
                                         tr(c_addedFood), initValue,
                                         0,100,1,&ok,Qt::WindowFlags(),0.1);

    popUp->setTextValue(QString(tr(chosenFood.c_str())));
    emit popUp->doubleValueSelected(quantity);

}

void Window::connectToQuantityButton(QList<QPushButton*> listButtons)
{
    for (const auto &button : listButtons ) {
        connect(button, SIGNAL (clicked()), this, SLOT (getQuantity()));//getQuantity
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
