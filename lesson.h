#ifndef LESSON_H
#define LESSON_H

#include <QFileInfo>
#include <QMainWindow>
#include <QVariant>
#include "lessonpassing.h"

namespace Ui {
class Lesson;
}

class Lesson : public QMainWindow
{
    Q_OBJECT

public:
    explicit Lesson(QWidget *parent = nullptr);
    ~Lesson();

    void showWin();
    void setHomeDir(QString home_dir);

signals:
    void showMain();

private slots:
    void on_btn_to_menu_clicked();

    void on_btn_select_dict_clicked();

    void on_btn_start_clicked();

private:
    Ui::Lesson *ui;
    QFileInfo file_info;
    QMap<QString, QVariant> map_dict;
    LessonPassing *lesson;
    QString home_dir;
};

#endif // LESSON_H
