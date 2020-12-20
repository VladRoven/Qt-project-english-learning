#include "lesson.h"
#include "ui_lesson.h"

#include <QFileDialog>
#include <QJsonDocument>

Lesson::Lesson(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Lesson)
{
    ui->setupUi(this);
    lesson = new LessonPassing(this);

    connect(lesson, &LessonPassing::showMain, this, &Lesson::showWin);
}

Lesson::~Lesson()
{
    delete ui;
}

void Lesson::showWin()
{
    show();
}

void Lesson::setHomeDir(QString home_dir)
{
    this->home_dir = home_dir;
}

void Lesson::on_btn_to_menu_clicked()
{
    ui->current_dict->setText("");
    ui->count_word->setText("Количество слов: 0");
    ui->user_name->clear();
    QString str("");
    file_info = str;
    emit showMain();
    close();
}

void Lesson::on_btn_select_dict_clicked()
{
    QString openFileName = QFileDialog::getOpenFileName(this, tr("Открыть файл"), QString(), tr("JSON (*.json)"));
    file_info = openFileName;

    if (file_info.absoluteFilePath() != "")
    {
        ui->status_line->clearMessage();
        ui->current_dict->setText("Текущий словарь: " + file_info.baseName());

        QFile jsonFile(file_info.absoluteFilePath());
        if (!jsonFile.open(QIODevice::ReadOnly))
        {
            return;
        }

        QByteArray data = jsonFile.readAll();
        QJsonDocument json_doc = QJsonDocument::fromJson(data);
        map_dict = json_doc.toVariant().toMap();

        ui->count_word->setText("Количество слов: " + QString::number(map_dict.count()));
    }
    else
        ui->status_line->showMessage("Ошибка!");
}

void Lesson::on_btn_start_clicked()
{
    QRegExp word_ru("([А-Я][а-яё]+)");
    if (ui->user_name->text().length() && word_ru.exactMatch(ui->user_name->text()))
    {
        if (file_info.absoluteFilePath() != "")
        {
            if (map_dict.count())
            {
                hide();
                lesson->setMap(map_dict, ui->user_name->text(), file_info.baseName(), home_dir);
                lesson->show();
            }
            else
                ui->status_line->showMessage("Словарь пуст!");
        }
        else
            ui->status_line->showMessage("Выберите словарь!");
    }
    else
        ui->status_line->showMessage("Введите корректно имя!");
}
