#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileInfo>
#include <QMainWindow>
#include "newdict.h"
#include "lesson.h"
#include "results.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_new_dict_clicked();

    void showMain();

    void on_pushButton_clicked();

    void on_btn_lesson_clicked();

    void on_btn_result_clicked();

private:
    Ui::MainWindow *ui;
    NewDict *new_dict;
    QFileInfo file_info;
    Lesson *lesson;
    Results *results;
    QString home_dir;
};
#endif // MAINWINDOW_H
