#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    new_dict = new NewDict(this);
    lesson = new Lesson(this);
    results = new Results(this);

    home_dir = QDir::currentPath();

    connect(new_dict, &NewDict::showMain, this, &MainWindow::showMain);
    connect(lesson, &Lesson::showMain, this, &MainWindow::showMain);
    connect(results, &Results::showMain, this, &MainWindow::showMain);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_new_dict_clicked()
{
    QString saveFileName = QFileDialog::getSaveFileName(this,
                                                            tr("Сохранить файл как"),
                                                            QString(),
                                                            tr("JSON (*.json)"));
    file_info = saveFileName;
    QDir::setCurrent(file_info.path());
    QFile json_file(saveFileName);

    if (!json_file.open(QIODevice::WriteOnly))
    {
        return;
    }
    json_file.close();

    if (file_info.absoluteFilePath() != "")
    {
        hide();
        new_dict->setParam(file_info);
        new_dict->show();
    }
    else
        ui->status_line->showMessage("Ошибка!");
}

void MainWindow::showMain()
{
    show();
}

void MainWindow::on_pushButton_clicked()
{
    QString openFileName = QFileDialog::getOpenFileName(this, tr("Открыть файл"), QString(), tr("JSON (*.json)"));
    file_info = openFileName;

    if (file_info.absoluteFilePath() != "")
    {
        hide();
        new_dict->setParam(file_info);
        new_dict->setTableRec();
        new_dict->show();
    }
    else
        ui->status_line->showMessage("Ошибка!");
}

void MainWindow::on_btn_lesson_clicked()
{
    hide();
    lesson->setHomeDir(home_dir);
    lesson->show();
}

void MainWindow::on_btn_result_clicked()
{
    hide();
    results->setTabItem(home_dir);
    results->show();
}
