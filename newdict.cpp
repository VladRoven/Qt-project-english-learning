#include "newdict.h"
#include "ui_newdict.h"
#include <QDebug>
#include <QDir>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QSortFilterProxyModel>

NewDict::NewDict(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewDict)
{
    ui->setupUi(this);
    new_word = new NewWord(this);
    edit_form = new WordEditForm(this);
}

NewDict::~NewDict()
{
    delete ui;
}

void NewDict::setParam(QFileInfo file_info)
{
    model_dict->clear();
    ui->status_line->clearMessage();
    this->file_info = file_info;
    model_dict->setHorizontalHeaderLabels({"Слово", "Перевод"});
    ui->table_dict->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->table_dict->setModel(model_dict);
}

void NewDict::setTableRec()
{
    QFile jsonFile(file_info.absoluteFilePath());

    if (!jsonFile.open(QIODevice::ReadOnly))
    {
        return;
    }

    QByteArray saveData = jsonFile.readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(saveData);
    QMap<QString, QVariant> map_dict = json_doc.toVariant().toMap();
    QStringList list = map_dict.keys();
    for (int i = 0; i < map_dict.count(); i++)
    {
        model_dict->insertRow(i, {new QStandardItem(list[i]), new QStandardItem(map_dict.find(list[i]).value().toString())});
    }

    ui->table_dict->setModel(model_dict);
    ui->status_line->showMessage("Всего слов: " + QString::number(map_dict.count()));
}

void NewDict::on_btn_to_menu_clicked()
{
    emit showMain();
    close();
}

void NewDict::on_btn_add_clicked()
{
    new_word->setWindowModality(Qt::ApplicationModal);
    new_word->setModel(model_dict);
    new_word->show();
    ui->status_line->clearMessage();
}

void NewDict::on_save_dict_triggered()
{
    QFile json_file(file_info.absoluteFilePath());
    QDir::setCurrent(file_info.path());

    if (!json_file.open(QIODevice::WriteOnly))
    {
        return;
    }

    QJsonObject json;
    for (int i = 0; i < model_dict->rowCount(); i++)
    {
        json[model_dict->item(i, 0)->text()] = model_dict->item(i, 1)->text();
    }

    QJsonDocument saveDoc(json);
    json_file.write(saveDoc.toJson());
    json_file.close();
    ui->status_line->showMessage("Файл \"" + file_info.baseName() + "\" сохранён!");
}

void NewDict::on_btn_del_clicked()
{
    QModelIndex index = ui->table_dict->currentIndex();
    auto model = ui->table_dict->model();

    if (index.row() >= 0)
    {
        QMessageBox *msg = new QMessageBox();
        msg->setIcon(QMessageBox::Information);
        msg->setWindowTitle("Подтверждение удаления");
        msg->setText("Вы действительно хотите удалить выбранное слово?");
        QPushButton *btn_ok = msg->addButton("Да", QMessageBox::AcceptRole);
        msg->addButton("Отмена", QMessageBox::RejectRole);
        msg->setAttribute(Qt::WA_QuitOnClose, false);
        msg->exec();

        if (msg->clickedButton() == btn_ok)
        {
            model->removeRow(index.row());
            ui->table_dict->setModel(model_dict);
            ui->status_line->showMessage("Всего слов: " + QString::number(model_dict->rowCount()));
        }
    }
    else
    {
        ui->status_line->showMessage("Выберите слово!");
    }
}

void NewDict::on_table_dict_doubleClicked(const QModelIndex &index)
{
    edit_form->setModel(ui->table_dict->model());
    edit_form->mapper->setCurrentModelIndex(index);
    edit_form->setWindowModality(Qt::ApplicationModal);
    edit_form->show();
}

void NewDict::on_search_textChanged(const QString &arg1)
{
    if (arg1.length())
    {
        QString str = arg1;
        str[ 0 ] = str[ 0 ].toUpper();
        for (int i = 1; i < str.length(); i++)
        {
            str[i] = str[i].toLower();
        }
        QSortFilterProxyModel *proxy_model = new QSortFilterProxyModel();
        proxy_model->setSourceModel(model_dict);
        ui->table_dict->setModel(proxy_model);
        proxy_model->setFilterKeyColumn(0);
        proxy_model->setFilterRegExp(str);
        ui->status_line->showMessage("Найдено записей: " + QString::number(proxy_model->rowCount()));
    }
    else
    {
        ui->table_dict->setModel(model_dict);
        ui->status_line->showMessage("Всего записей: " + QString::number(model_dict->rowCount()));
    }
}

void NewDict::on_search_trn_textChanged(const QString &arg1)
{
    if (arg1.length())
    {
        QString str = arg1;
        str[ 0 ] = str[ 0 ].toUpper();
        for (int i = 1; i < str.length(); i++)
        {
            str[i] = str[i].toLower();
        }
        QSortFilterProxyModel *proxy_model = new QSortFilterProxyModel();
        proxy_model->setSourceModel(model_dict);
        ui->table_dict->setModel(proxy_model);
        proxy_model->setFilterKeyColumn(1);
        proxy_model->setFilterRegExp(str);
        ui->status_line->showMessage("Найдено записей: " + QString::number(proxy_model->rowCount()));
    }
    else
    {
        ui->table_dict->setModel(model_dict);
        ui->status_line->showMessage("Всего записей: " + QString::number(model_dict->rowCount()));
    }
}
