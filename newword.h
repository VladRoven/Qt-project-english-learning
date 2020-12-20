#ifndef NEWWORD_H
#define NEWWORD_H

#include <QDataWidgetMapper>
#include <QMainWindow>
#include <QStandardItemModel>

namespace Ui {
class NewWord;
}

class NewWord : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewWord(QWidget *parent = nullptr);
    ~NewWord();

    void setModel(QStandardItemModel *model);
private slots:
    void on_btn_add_clicked();

    void on_pushButton_clicked();

private:
    Ui::NewWord *ui;
    QDataWidgetMapper *mapper;
};

#endif // NEWWORD_H
