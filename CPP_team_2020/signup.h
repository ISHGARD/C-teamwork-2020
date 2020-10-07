#ifndef SIGNUP_H
#define SIGNUP_H

#include <QWidget>

namespace Ui {
class signup;
}

class signup : public QWidget
{
    Q_OBJECT

public:
    explicit signup(QWidget *parent = 0);
    ~signup();

private slots:
    void on_pushButton_clicked();

private:
    Ui::signup *ui;
};

#endif // SIGNUP_H
