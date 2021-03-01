#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QFileDialog>

#include <QVector>
#include <math.h>

#include "huffman.hh"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0); //CONSTRUCTEUR DE NOTRE INTERFACE
    ~MainWindow(); //DESTRUCTEUR

private slots:
    void on_pushButton_Code_clicked(); //SLOT DU BOUTON CODE
    void on_pushButton_deCode_clicked(); //SLOT DU BOUTON DECODE
    void on_pushButton_Clear_clicked(); //SLOT DU BOUTON CLEAR

private:
    Ui::MainWindow *ui;
    void setDataOut(); 
    QString dataOutput; //FONCTION QUI RECOIT UN SLOT ET EXECUTE CE QUI EST DEMANDÉ
    huffman h;
    int et; // SOIT 0 SOIT  1 , UTILISÉ DANS setDataOut() POUR DIFFERENCIER LES SLOTS 
    void setSymbolsToTable(); //FONCTION QUI REMPLIE LE TABLEAU DES DONNES DU CRYPTAGE DE HUFFMAN
};

#endif // MAINWINDOW_H
