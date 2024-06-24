#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Notepad;
}
QT_END_NAMESPACE

class Notepad : public QMainWindow
{
    Q_OBJECT

public:
    Notepad(QWidget *parent = nullptr);
    ~Notepad();

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_as_triggered();

    void on_actionExit_triggered();

    void on_fontComboBox_currentFontChanged(const QFont &f);



    void on_pushBold_toggled(bool checked);

    void on_pushItalic_toggled(bool checked);

    void on_pushUnderline_toggled(bool checked);

    void on_pushStrike_toggled(bool checked);

private:
    Ui::Notepad *ui;
    QString currentFile;
};
#endif // NOTEPAD_H
