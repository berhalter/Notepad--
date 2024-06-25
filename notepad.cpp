#include "notepad.h"
#include "./ui_notepad.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFont>

Notepad::Notepad(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Notepad)
{
    ui->setupUi(this);
}

Notepad::~Notepad()
{
    delete ui;
}




void Notepad::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
}


void Notepad::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    if (fileName.isEmpty()) {
        return;
    }
    QFile file(fileName);
    currentFile = fileName;
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}


void Notepad::on_actionSave_triggered()
{
    QString fileName;
    if (currentFile.isEmpty()) {
        fileName = QFileDialog::getSaveFileName(this, "Save");
        if (fileName.isEmpty()) {
            return;
        }
        currentFile = fileName;
    } else {
        fileName = currentFile;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}


void Notepad::on_actionSave_as_triggered()
{
    QString fileName;
    fileName = QFileDialog::getSaveFileName(this, "Save as");
    if (fileName.isEmpty()) {
        return;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}



void Notepad::on_actionExit_triggered()
{
    QApplication::quit();
}


void Notepad::on_fontComboBox_currentFontChanged(const QFont &f)
{
    ui->textEdit->setFont(f);
}


void Notepad::on_pushBold_toggled(bool checked)
{
    if (checked) {
        ui->textEdit->setFontWeight(QFont::Bold);
    } else {
        ui->textEdit->setFontWeight(QFont::Normal);
    }
}


void Notepad::on_pushItalic_toggled(bool checked)
{
    ui->textEdit->setFontItalic(checked);
    //the button remains toggled when the cursor is moved to a non italic area. can check if cursor is moved and if current text is italic?
}


void Notepad::on_pushUnderline_toggled(bool checked)
{
    ui->textEdit->setFontUnderline(checked);
}


void Notepad::on_pushStrike_toggled(bool checked)
{
    //see comment in on_pushItalic_toggled()
    QFont font = ui->fontComboBox->currentFont();
    font.setStrikeOut(checked);
    ui->textEdit->setFont(font);
}


void Notepad::on_pushLeft_toggled(bool checked)
{
    if (checked) {
        ui->textEdit->setAlignment(Qt::AlignLeft);
    }
}


void Notepad::on_pushCenter_toggled(bool checked)
{
    if (checked) {
        ui->textEdit->setAlignment(Qt::AlignCenter);
    }
}


void Notepad::on_pushRight_toggled(bool checked)
{
    if (checked) {
        ui->textEdit->setAlignment(Qt::AlignRight);
    }
}


void Notepad::on_pushJustify_toggled(bool checked)
{
    if (checked) {
        ui->textEdit->setAlignment(Qt::AlignJustify);
    }
}


void Notepad::on_spinPtSize_valueChanged(int arg1)
{
    //see comment in on_pushItalic_toggled()
    ui->textEdit->setFontPointSize(arg1);
}

