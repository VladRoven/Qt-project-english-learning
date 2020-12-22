#include "results.h"
#include "ui_results.h"

#include <QDir>
#include <QJsonArray>
#include <QJsonDocument>
#include <QMessageBox>

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
    this->home_dir = home_dir;
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

void Results::on_btn_del_clicked()
{
    QModelIndex index = ui->table_result->currentIndex();

    if (index.row() >= 0)
    {
        QMessageBox *msg = new QMessageBox();
        msg->setIcon(QMessageBox::Information);
        msg->setWindowTitle("Подтверждение удаления");
        msg->setText("Вы действительно хотите удалить выбранную запись?");
        QPushButton *btn_ok = msg->addButton("Да", QMessageBox::AcceptRole);
        msg->addButton("Отмена", QMessageBox::RejectRole);
        msg->setAttribute(Qt::WA_QuitOnClose, false);
        msg->exec();

        if (msg->clickedButton() == btn_ok)
        {
            model->removeRow(index.row());
            ui->table_result->setModel(model);

            QFile json_file(home_dir + "/result.json");
            QDir::setCurrent(home_dir);

            if (!json_file.open(QIODevice::WriteOnly))
            {
                return;
            }

            QJsonArray data;
            for (int i = 0; i < model->rowCount(); i++)
            {
                QJsonArray row;

                for (int j = 0; j < model->columnCount(); j++)
                {
                    row.append(QJsonValue(model->item(i, j)->text()));
                }
                data.append(row);
            }

            QJsonDocument saveDoc(data);
            json_file.write(saveDoc.toJson());
            json_file.close();
        }
    }
    else
    {
        ui->status_line->showMessage("Выберите запись!");
    }
}
