#ifndef RESULTS_H
#define RESULTS_H

#include <QFileInfo>
#include <QMainWindow>
#include <QStandardItemModel>

namespace Ui {
class Results;
}

class Results : public QMainWindow
{
    Q_OBJECT

public:
    explicit Results(QWidget *parent = nullptr);
    ~Results();

    void setTabItem(QString home_dir);

signals:
    void showMain();

private slots:
    void on_btn_to_menu_clicked();

    void on_btn_del_clicked();

private:
    Ui::Results *ui;
    QStandardItemModel *model = new QStandardItemModel;
    QString home_dir;
};

#endif // RESULTS_H
