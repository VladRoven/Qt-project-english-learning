#include "newword.h"
#include "ui_newword.h"

#include <QMessageBox>

NewWord::NewWord(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewWord)
{
    ui->setupUi(this);
    mapper = new QDataWidgetMapper(this);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
}

NewWord::~NewWord()
{
    delete ui;
}

void NewWord::setModel(QStandardItemModel *model)
{
    mapper->clearMapping();
    mapper->setModel(model);
}

void NewWord::on_btn_add_clicked()
{
    QString error = "";
    QRegExp word_ru("([А-Я][а-яё]+)");
    QRegExp word_en("([A-Z][a-z]+)");
    if (!word_en.exactMatch(ui->word_en->text()))
        error += "Корректно введите перевод!\n";

    if (!word_ru.exactMatch(ui->word_ru->text()))
        error += "Корректно введите русское слово!\n";

    if (error.length())
    {
        QMessageBox *msg = new QMessageBox();
        msg->setIcon(QMessageBox::Warning);
        msg->setWindowTitle("Ошибка");
        msg->setInformativeText(error);
        msg->addButton("Понял", QMessageBox::ApplyRole);
        msg->setAttribute(Qt::WA_QuitOnClose, false);
        msg->exec();
    }
    else
    {
        mapper->model()->insertRow(mapper->model()->rowCount());
        mapper->setCurrentModelIndex(mapper->model()->index(mapper->model()->rowCount() - 1, 0));

        mapper->addMapping(ui->word_en, 0);
        mapper->addMapping(ui->word_ru, 1);

        mapper->submit();

        close();

        ui->word_en->clear();
        ui->word_ru->clear();
    }
}

void NewWord::on_pushButton_clicked()
{
    ui->word_en->clear();
    ui->word_ru->clear();
    close();
}
