#include "lessonpassing.h"
#include "ui_lessonpassing.h"
#include <QDebug>
#include <QDir>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>

LessonPassing::LessonPassing(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LessonPassing)
{
    ui->setupUi(this);
}

LessonPassing::~LessonPassing()
{
    delete ui;
}

void LessonPassing::errorWork()
{
    is_error_work = true;
    ui->enter_word->clear();
    itr = 0;
    count_right = 0;
    std::random_shuffle(right_answ.begin(), right_answ.end());

    for (int i = 0; i < right_answ.length(); i++)
    {
        for (auto it = map.begin(); it != map.end();)
        {
            if (it.key().contains(right_answ[i]))
            {
                it = map.erase(it);
            } else
            {
                ++it;
            }
        }
    }

    list_word.clear();
    list_word = map.keys();
    right_answ.clear();

    ui->counter->setText(QString::number(itr + 1) + "/" + QString::number(map.count()));
    ui->current_word->setText("Слово: " + map.find(list_word[itr]).value().toString());
    ui->btn_next->setText((itr == map.count() - 1) ? "Закончить" : "Следующее");
    ui->status_line->clearMessage();
    ui->enter_word->setFocus();
}

void LessonPassing::setMap(QMap<QString, QVariant> map, QString name, QString dict_name, QString home_dir)
{
    ui->status_line->clearMessage();
    ui->enter_word->clear();
    itr = 0;
    count_right = 0;
    right_answ.clear();
    this->map = map;
    list_word = map.keys();
    user_name = name;
    is_error_work = false;
    this->home_dir = home_dir;
    this->dict_name = dict_name;
    std::random_shuffle(list_word.begin(), list_word.end());
    ui->counter->setText(QString::number(itr + 1) + "/" + QString::number(map.count()));
    ui->current_word->setText("Слово: " + map.find(list_word[itr]).value().toString());
    ui->btn_next->setText((itr == map.count() - 1) ? "Закончить" : "Следующее");
}

void LessonPassing::on_btn_to_menu_clicked()
{
    emit showMain();
    close();
}

void LessonPassing::on_btn_next_clicked()
{
    QRegExp word_en("([A-Za-z]+)");
    if (ui->enter_word->text().length() && word_en.exactMatch(ui->enter_word->text()))
    {
        QString str = ui->enter_word->text();
        str[ 0 ] = str[ 0 ].toUpper();
        for (int i = 1; i < str.length(); i++)
        {
            str[i] = str[i].toLower();
        }

        if (itr == map.count() - 1)
        {
            if (list_word[itr].contains(str))
            {
                ui->enter_word->clear();
                ++count_right;
                right_answ.append(list_word[itr]);
            }
            else
                ui->enter_word->clear();

            if (count_right == map.count())
            {
                QMessageBox *msg = new QMessageBox(this);
                msg->setIcon(QMessageBox::Information);
                msg->setWindowTitle("Уведомление");
                msg->setText("Вы успешно закончили урок!");
                msg->setInformativeText("Вы перевели все слова правильно!\nПродолжайте в том же духе!\nРезультаты занесены в таблицу (если это не работа над ошибками).");
                QPushButton *btn_ok = msg->addButton("Понял", QMessageBox::AcceptRole);
                msg->setAttribute(Qt::WA_QuitOnClose, false);
                msg->exec();

                if (is_error_work)
                {
                    if (msg->clickedButton() == btn_ok)
                    {
                        emit showMain();
                        close();
                    }
                }
                else
                    if (msg->clickedButton() == btn_ok)
                    {
                        toResult(QString::number((int)((double)count_right / map.count() * 100)));
                        emit showMain();
                        close();
                    }
            }
            else
            {
                QMessageBox *msg = new QMessageBox(this);
                msg->setIcon(QMessageBox::Information);
                msg->setWindowTitle("Уведомление");
                msg->setText("Вы закончили урок!");
                msg->setInformativeText("Ваш бал: " + QString::number((int)((double)count_right / map.count() * 100)) + ".\nСтрарайтесь улучшать свой результат!\nПредлагаем вам пройти работу над ошибками!\nВ случае отказа/согласия результат будет занесён в таблицу (если это не работа над ошибками).");
                msg->addButton("Работа над ошибками", QMessageBox::ApplyRole);
                QPushButton *btn_cancle = msg->addButton("Отмена", QMessageBox::RejectRole);
                msg->setAttribute(Qt::WA_QuitOnClose, false);
                msg->exec();

                if (is_error_work)
                {
                    if (msg->clickedButton() == btn_cancle)
                    {
                        emit showMain();
                        close();
                    }
                    else
                    {
                        errorWork();
                        show();
                    }
                }
                else
                {
                    if (msg->clickedButton() == btn_cancle)
                    {
                        toResult(QString::number((int)((double)count_right / map.count() * 100)));
                        emit showMain();
                        close();
                    }
                    else
                    {
                        toResult(QString::number((int)((double)count_right / map.count() * 100)));
                        errorWork();
                        show();
                    }
                }
            }
        }
        else
        {
            if (list_word[itr].contains(str))
            {
                ui->enter_word->clear();
                ++count_right;
                right_answ.append(list_word[itr]);
                ++itr;
                ui->counter->setText(QString::number(itr + 1) + "/" + QString::number(map.count()));
                ui->current_word->setText("Слово: " + map.find(list_word[itr]).value().toString());
                ui->enter_word->setFocus();
            }
            else
            {
                ui->enter_word->clear();
                ++itr;
                ui->counter->setText(QString::number(itr + 1) + "/" + QString::number(map.count()));
                ui->current_word->setText("Слово: " + map.find(list_word[itr]).value().toString());
                ui->enter_word->setFocus();
            }


            if (itr == map.count() - 1)
                ui->btn_next->setText("Закончить");
            ui->status_line->showMessage("Ответ засчитан!");
        }
    }
    else
        ui->status_line->showMessage("Введите корректно свой вариант перевода!");
}

void LessonPassing::toResult(QString res)
{
    QFile json_file(home_dir + "/result.json");
    QDir::setCurrent(QDir::currentPath());

    if (!json_file.open(QIODevice::ReadOnly))
    {
        return;
    }

    QByteArray saveData = json_file.readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(saveData);
    QJsonArray array = json_doc.array();
    json_file.close();

    if (!json_file.open(QIODevice::WriteOnly))
    {
        return;
    }

    QJsonArray temp;
    temp.append(user_name);
    temp.append(res);
    temp.append(dict_name);
    temp.append(QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm"));

    array.append(temp);

    QJsonDocument saveDoc(array);
    json_file.write(saveDoc.toJson());
    json_file.close();
    close();
}
