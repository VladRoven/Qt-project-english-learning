#ifndef NEWDICT_H
#define NEWDICT_H

#include "newword.h"
#include "wordeditform.h"

#include <QFileInfo>
#include <QMainWindow>
#include <QStandardItemModel>

namespace Ui {
class NewDict;
}

class NewDict : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewDict(QWidget *parent = nullptr);
    ~NewDict();

    void setParam(QFileInfo file_info);
    void setTableRec();

signals:
    void showMain();

private slots:
    void on_btn_to_menu_clicked();

    void on_btn_add_clicked();

    void on_save_dict_triggered();

    void on_btn_del_clicked();

    void on_table_dict_doubleClicked(const QModelIndex &index);

private:
    Ui::NewDict *ui;
    QFileInfo file_info;
    QStandardItemModel *model_dict = new QStandardItemModel;
    NewWord *new_word;
    WordEditForm *edit_form;
};

#endif // NEWDICT_H
