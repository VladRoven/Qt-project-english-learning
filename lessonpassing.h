#ifndef LESSONPASSING_H
#define LESSONPASSING_H

#include <QMainWindow>
#include <QVariant>

namespace Ui {
class LessonPassing;
}

class LessonPassing : public QMainWindow
{
    Q_OBJECT

public:
    explicit LessonPassing(QWidget *parent = nullptr);
    ~LessonPassing();

    void setMap(QMap<QString, QVariant> map, QString name, QString dict_name, QString home_dir);

signals:
    void showMain();

private slots:
    void on_btn_to_menu_clicked();

    void on_btn_next_clicked();

    void errorWork();

    void toResult(QString res);

private:
    Ui::LessonPassing *ui;
    QMap<QString, QVariant> map;
    QStringList list_word;
    QStringList right_answ;
    QString user_name;
    QString dict_name;
    QString home_dir;
    int itr;
    int count_right;
    bool is_error_work;
};

#endif // LASSONPASSING_H
