#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardItem>
#include <QStandardItemModel>
#include <QGraphicsTextItem>
#include <sstream>

//CONSTRUCTEUR DE NOTRE INTERFACE
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(820+400,590);
    ui->LineEdit_InputData->setPlaceholderText("   Veuillez saisir le texte à coder/deccoder ici");
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"lettre"<<"pourcentage"<<"code Huffman");
    ui->tableWidget->setColumnWidth(0,200);
    ui->tableWidget->setColumnWidth(1,200);
    ui->tableWidget->setColumnWidth(2,385);
}

//DESTRUCTEUR
MainWindow::~MainWindow()
{
    delete ui;
}

//SLOT DU BOUTON CODE
void MainWindow::on_pushButton_Code_clicked()
{
    if(ui->LineEdit_InputData->text().isEmpty()) {
        ui->LineEdit_InputData->setText("ceci est un test");
    }
    et=0;
    setDataOut();
    setSymbolsToTable();

}

//SLOT DU BOUTON DECODE
void MainWindow::on_pushButton_deCode_clicked()
{
    if(ui->LineEdit_InputData->text().isEmpty()) {
        ui->textEdit_OutputData->setText("il n'existe aucun arbre permettant de décrypter un code huffman");
    }
    else
    {
        et=1;
        setDataOut();
    }
}

//SLOT DU BOUTON CLEAR
void MainWindow::on_pushButton_Clear_clicked()
{
    ui->tableWidget->clear();
    while (ui->tableWidget->rowCount()!= 0)
        ui->tableWidget->removeRow(0);
    ui->LineEdit_InputData->clear();
    ui->textEdit_OutputData->clear();
    ui->textEdit->clear();
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"lettre"<<"pourcentage"<<"code Huffman");

    dataOutput.clear();

}

//FONCTION QUI REMPLIE LE TABLEAU DES DONNES DU CRYPTAGE DE HUFFMAN 
void MainWindow::setSymbolsToTable() {

    ui->tableWidget->clear();

    ui->tableWidget->clear();
    while (ui->tableWidget->rowCount()!= 0)
        ui->tableWidget->removeRow(0);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"lettre"<<"pourcentage"<<"code Huffman");
    ui->tableWidget->setRowCount(h.dico.size());

    for (uint8_t i = 0; i < h.dico.size(); ++i){
       QTableWidgetItem * item;
       
       if (h.dico.at(i).le_car != ' ')
            item = new QTableWidgetItem(QString(h.dico.at(i).le_car));
       else
           item = new QTableWidgetItem("Space");
       ui->tableWidget->setItem(i, 0, item);
       
       item = new QTableWidgetItem(QString::number(h.alphabet[h.dico.at(i).le_car - 32]));
       ui->tableWidget->setItem(i, 1, item);
              
        std::stringstream ss;

        for (size_t j = 0; j < h.dico.at(i).le_code.size(); j++)
        {
            ss << h.dico.at(i).le_code.at(j);
        }
        
       item = new QTableWidgetItem(QString::fromStdString(ss.str()));
       ui->tableWidget->setItem(i, 2, item);
    }
}

//FONCTION QUI RECOIT UN SLOT ET EXECUTE CE QUI EST DEMANDÉ
void MainWindow::setDataOut() {
   QString dataInput = ui->LineEdit_InputData->text();
   dataOutput.clear();

    if (et == 0)
    {
            for (size_t i = 0; i < 94; i++) 
            {
                h.alphabet[i] = 0;
            }

            if (h.arbres.size() != 0)
                delete h.arbres.at(0);

            h.arbres.clear();
            h.dechets.clear();
            h.dico.clear();
            h.nbreCar = 0;
            h.etat = 0;

            if (h.lecture_traitements_C(dataInput.toStdString()))
            {
                h.initialiser_vecteurs_arbres();
                h.fusionner_arbres();
                h.vider();
                h.getArbres().at(0)->affiche();
                //std::cout << h.getArbres().at(0)->affichage.str();
            
                dataOutput = QString::fromStdString(h.genere_code());
                ui->textEdit_OutputData->setText(dataOutput);

                //dataOutput = QString::fromStdString(h.genere_code());
                ui->textEdit->setText(QString::fromStdString(h.getArbres().at(0)->affichage.str()));


            }
            else
            {
                dataOutput = QString::fromStdString("ERREUR : caractere non valide");
                ui->textEdit_OutputData->setText(dataOutput);
            }
    }
    else if (et == 1)
    {
                if (h.etat == -1)
                {
                    dataOutput = "ERREUR : il n'existe aucun arbre permettant de décrypter un code huffman";
                    ui->textEdit_OutputData->setText(dataOutput);
                }
                else
                {
                    h.etat = 1;
                    std::string de = h.lecture_traitements_DE(dataInput.toStdString());
                    dataOutput = QString::fromStdString(de);
                    ui->textEdit_OutputData->setText(dataOutput);
                }
                     
    }
}