#ifndef SELECTPASSWORDDIALOG_H
#define SELECTPASSWORDDIALOG_H

#include <vector>
#include <map>
#include <QString>
#include <QDialog>
#include "globals.h"

using std::vector;
using std::map;

namespace Ui {
class SelectPasswordDialog;
}

class SelectPasswordDialog : public QDialog {
    Q_OBJECT

public:
    explicit SelectPasswordDialog(PasswordType pwdType, const map<int, vector<QString>*>& pwdCollection, QWidget *parent = nullptr);
    ~SelectPasswordDialog();
    QString password;
    int strength;

private slots:
    void on_pwdButton1_clicked();
    void on_pwdButton2_clicked();
    void on_pwdButton3_clicked();
    void on_pwdButton4_clicked();
    void on_pwdButton5_clicked();
    void on_pwdButton6_clicked();
    void on_pwdButton7_clicked();
    void on_pwdButton8_clicked();
    void on_pwdButton9_clicked();
    void on_pwdButton10_clicked();

private:
    Ui::SelectPasswordDialog *ui;
    map<int, vector<QString>*> pwdCollection;
    int getStrength(QString pwd);
};

#endif // SELECTPASSWORDDIALOG_H
