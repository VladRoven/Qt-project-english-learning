#include "results.h"
#include "ui_results.h"

#include <QDir>
#include <QJsonArray>
#include <QJsonDocument>

Results::Results(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Results)
{
    ui->setupUi(this);
}

Results::~Results()
{
    delete ui;
}

void Results::setTabItem(QString home_dir)
{
    model->clear();
    QFile jsonFile(home_dir + "/result.json");

    if (!jsonFile.open(QIODevice::ReadOnly))
    {
        return;
    }
    QByteArray saveData = jsonFile.readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(saveData);
    QStringList horizontalHeader;
    horizontalHeader.append({"Имя", "Бал", "Словарь", "Дата"});

    model->setHorizontalHeaderLabels(horizontalHeader);

    ui->table_result->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QJsonArray json_res = json_doc.array();

    QJsonArray temp_array;
    QList<QStandardItem *> temp_list;

    for (int i = 0; i < json_res.count(); i++)
    {
        temp_list.clear();
        temp_array = json_res[i].toArray();
        for (int j = 0; j < temp_array.count(); j++)
        {
             temp_list.append(new QStandardItem(temp_array[j].toString()));
        }
        model->insertRow(i, temp_list);
    }

    ui->table_result->setModel(model);
}

void Results::on_btn_to_menu_clicked()
{
    emit showMain();
    close();
}
