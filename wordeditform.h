#ifndef WORDEDITFORM_H
#define WORDEDITFORM_H

#include <QDataWidgetMapper>
#include <QMainWindow>
#include <QStandardItemModel>

namespace Ui {
class WordEditForm;
}

class WordEditForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit WordEditForm(QWidget *parent = nullptr);
    ~WordEditForm();

    void setModel(QAbstractItemModel *model);
    QDataWidgetMapper *mapper;

private slots:
    void on_btn_edit_clicked();

    void on_pushButton_clicked();

private:
    Ui::WordEditForm *ui;
};

#endif // WORDEDITFORM_H
