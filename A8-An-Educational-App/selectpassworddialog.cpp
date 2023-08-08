/*
 * A8-An-Educational-App
 * A cryptography tower defense game
 * CS3505 - 4/27/2023
 * Authors: Samuel Powell, Spencer Robinson, Alex Cao, Jaran Holt, Camden Yates
 *
 * */
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>
#include <QString>
#include "selectpassworddialog.h"
#include "ui_selectpassworddialog.h"
#include "globals.h"

using std::shuffle;
using std::vector;
using std::time;
using std::count;

SelectPasswordDialog::SelectPasswordDialog(PasswordType pwdType, const map<int, vector<QString>*>& pwdCollection, QWidget *parent)
    : QDialog(parent), ui(new Ui::SelectPasswordDialog) {
    ui->setupUi(this);
    this->pwdCollection = pwdCollection;

    if (pwdType == Master) {
        this->setWindowTitle("Select Master Password");
        this->ui->titleLabel->setText("Choose Your Master Password");
    } else if (pwdType == Tower) {
        this->setWindowTitle("Select Password Password");
        this->ui->titleLabel->setText("Choose Your Tower Password");
    }

    vector<QString> pwdList;
    for (int i = 0; i < 4; i++)
        for (QString pwd : *pwdCollection.at(i))
            pwdList.push_back(pwd);
    shuffle(pwdList.begin(), pwdList.end(), std::default_random_engine(time(0)));

    ui->pwdButton1->setText(pwdList[0]);
    ui->pwdButton1->setProperty("strength", getStrength(pwdList[0]));
    ui->pwdButton2->setText(pwdList[1]);
    ui->pwdButton2->setProperty("strength", getStrength(pwdList[1]));
    ui->pwdButton3->setText(pwdList[2]);
    ui->pwdButton3->setProperty("strength", getStrength(pwdList[2]));
    ui->pwdButton4->setText(pwdList[3]);
    ui->pwdButton4->setProperty("strength", getStrength(pwdList[3]));
    ui->pwdButton5->setText(pwdList[4]);
    ui->pwdButton5->setProperty("strength", getStrength(pwdList[4]));
    ui->pwdButton6->setText(pwdList[5]);
    ui->pwdButton6->setProperty("strength", getStrength(pwdList[5]));
    ui->pwdButton7->setText(pwdList[6]);
    ui->pwdButton7->setProperty("strength", getStrength(pwdList[6]));
    ui->pwdButton8->setText(pwdList[7]);
    ui->pwdButton8->setProperty("strength", getStrength(pwdList[7]));
    ui->pwdButton9->setText(pwdList[8]);
    ui->pwdButton9->setProperty("strength", getStrength(pwdList[8]));
    ui->pwdButton10->setText(pwdList[9]);
    ui->pwdButton10->setProperty("strength", getStrength(pwdList[9]));

    ui->pwdButton1->setStyleSheet( QString("QPushButton {background-color: rgb(100,100,250);} QPushButton:pressed {background-color: rgb(150,150,255);}"));
    ui->pwdButton2->setStyleSheet( QString("QPushButton {background-color: rgb(100,100,250);} QPushButton:pressed {background-color: rgb(150,150,255);}"));
    ui->pwdButton3->setStyleSheet( QString("QPushButton {background-color: rgb(100,100,250);} QPushButton:pressed {background-color: rgb(150,150,255);}"));
    ui->pwdButton4->setStyleSheet( QString("QPushButton {background-color: rgb(100,100,250);} QPushButton:pressed {background-color: rgb(150,150,255);}"));
    ui->pwdButton5->setStyleSheet( QString("QPushButton {background-color: rgb(100,100,250);} QPushButton:pressed {background-color: rgb(150,150,255);}"));
    ui->pwdButton6->setStyleSheet( QString("QPushButton {background-color: rgb(100,100,250);} QPushButton:pressed {background-color: rgb(150,150,255);}"));
    ui->pwdButton7->setStyleSheet( QString("QPushButton {background-color: rgb(100,100,250);} QPushButton:pressed {background-color: rgb(150,150,255);}"));
    ui->pwdButton8->setStyleSheet( QString("QPushButton {background-color: rgb(100,100,250);} QPushButton:pressed {background-color: rgb(150,150,255);}"));
    ui->pwdButton9->setStyleSheet( QString("QPushButton {background-color: rgb(100,100,250);} QPushButton:pressed {background-color: rgb(150,150,255);}"));
    ui->pwdButton10->setStyleSheet( QString("QPushButton {background-color: rgb(100,100,250);} QPushButton:pressed {background-color: rgb(150,150,255);}"));
}

SelectPasswordDialog::~SelectPasswordDialog() {
    delete ui;
}

int SelectPasswordDialog::getStrength(QString pwd) {
    for (int strength = 0; strength < 4; strength++)
        if (count(pwdCollection.at(strength)->begin(), pwdCollection.at(strength)->end(), pwd))
            return strength;
    return 0;
}

void SelectPasswordDialog::on_pwdButton1_clicked() {
    password = ui->pwdButton1->text();
    strength = ui->pwdButton1->property("strength").toInt();
    this->close();
}

void SelectPasswordDialog::on_pwdButton2_clicked() {
    password = ui->pwdButton2->text();
    strength = ui->pwdButton2->property("strength").toInt();
    this->close();
}

void SelectPasswordDialog::on_pwdButton3_clicked() {
    password = ui->pwdButton3->text();
    strength = ui->pwdButton3->property("strength").toInt();
    this->close();
}

void SelectPasswordDialog::on_pwdButton4_clicked() {
    password = ui->pwdButton4->text();
    strength = ui->pwdButton4->property("strength").toInt();
    this->close();
}

void SelectPasswordDialog::on_pwdButton5_clicked() {
    password = ui->pwdButton5->text();
    strength = ui->pwdButton5->property("strength").toInt();
    this->close();
}

void SelectPasswordDialog::on_pwdButton6_clicked() {
    password = ui->pwdButton6->text();
    strength = ui->pwdButton6->property("strength").toInt();
    this->close();
}

void SelectPasswordDialog::on_pwdButton7_clicked() {
    password = ui->pwdButton7->text();
    strength = ui->pwdButton7->property("strength").toInt();
    this->close();
}

void SelectPasswordDialog::on_pwdButton8_clicked() {
    password = ui->pwdButton8->text();
    strength = ui->pwdButton8->property("strength").toInt();
    this->close();
}

void SelectPasswordDialog::on_pwdButton9_clicked() {
    password = ui->pwdButton9->text();
    strength = ui->pwdButton9->property("strength").toInt();
    this->close();
}

void SelectPasswordDialog::on_pwdButton10_clicked() {
    password = ui->pwdButton10->text();
    strength = ui->pwdButton10->property("strength").toInt();
    this->close();
}
