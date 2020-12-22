#include "wordeditform.h"
#include "ui_wordeditform.h"

#include <QMessageBox>

WordEditForm::WordEditForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WordEditForm)
{
    ui->setupUi(this);
    mapper = new QDataWidgetMapper(this);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
}

WordEditForm::~WordEditForm()
{
    delete ui;
}

void WordEditForm::setModel(QAbstractItemModel *model)
{
    mapper->setModel(model);
    mapper->addMapping(ui->word_en, 0);
    mapper->addMapping(ui->word_ru, 1);
}

void WordEditForm::on_btn_edit_clicked()
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
        mapper->submit();
        close();
    }
}

void WordEditForm::on_pushButton_clicked()
{
    close();
}
