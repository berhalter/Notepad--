#include "notepad.h"
#include "./ui_notepad.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFont>
#include <QtMath>

Notepad::Notepad(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Notepad)
{
    ui->setupUi(this);

    connect(ui->pushNew, SIGNAL(clicked()), this, SLOT(on_actionNew_triggered()));
    connect(ui->pushOpen, SIGNAL(clicked()), this, SLOT(on_actionOpen_triggered()));
    connect(ui->pushSave, SIGNAL(clicked()), this, SLOT(on_actionSave_triggered()));
    connect(ui->pushSaveAs, SIGNAL(clicked()), this, SLOT(on_actionSaveAs_triggered()));


    connect(ui->pushCopy, SIGNAL(clicked()), this, SLOT(on_actionCopy_triggered()));
    connect(ui->pushCut, SIGNAL(clicked()), this, SLOT(on_actionCut_triggered()));
    connect(ui->pushPaste, SIGNAL(clicked()), this, SLOT(on_actionPaste_triggered()));
    connect(ui->pushUndo, SIGNAL(clicked()), this, SLOT(on_actionUndo_triggered()));
    connect(ui->pushRedo, SIGNAL(clicked()), this, SLOT(on_actionRedo_triggered()));

    connect(ui->textEdit, SIGNAL(cursorPositionChanged()), this, SLOT(on_cursorPositionChanged()));
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
    QString fileName = QFileDialog::getOpenFileName(this, "Open");
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


void Notepad::on_actionSaveAs_triggered()
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
    ui->textEdit->setCurrentFont(f);
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
}


void Notepad::on_pushUnderline_toggled(bool checked)
{
    ui->textEdit->setFontUnderline(checked);
}


void Notepad::on_pushStrike_toggled(bool checked)
{
    //Strikethrough function is part of QFont, not QText edit, so it needs to be handled differently
    QFont font = ui->textEdit->currentFont();
    font.setStrikeOut(checked);
    ui->textEdit->setCurrentFont(font);
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


void Notepad::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}


void Notepad::on_actionCut_triggered()
{
    ui->textEdit->cut();
}


void Notepad::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}


void Notepad::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}


void Notepad::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}


void Notepad::on_cursorPositionChanged()
{
    if (ui->textEdit->alignment() == Qt::AlignLeft) {
        ui->pushLeft->toggle();
    } else if (ui->textEdit->alignment() == Qt::AlignCenter) {
        ui->pushCenter->toggle();
    } else if (ui->textEdit->alignment() == Qt::AlignRight) {
        ui->pushRight->toggle();
    } else if (ui->textEdit->alignment() == Qt::AlignJustify) {
        ui->pushJustify->toggle();
    }

    ui->fontComboBox->setCurrentFont(ui->textEdit->currentFont());
    int pt_size = qFloor(ui->textEdit->fontPointSize());
    ui->spinPtSize->setValue(pt_size);

    if (ui->textEdit->fontWeight() == QFont::Bold) {
        on_pushBold_toggled(true);
    } else {
        on_pushBold_toggled(false);
    }
    if (ui->textEdit->fontItalic()) {
        ui->pushItalic->setChecked(true);
    } else {
        ui->pushItalic->setChecked(false);
    }
    if (ui->textEdit->fontUnderline()) {
        ui->pushUnderline->setChecked(true);
    } else {
        ui->pushUnderline->setChecked(false);
    }
    //Strikethrough function is part of QFont, not QText edit, so it needs to be handled differently
    QFont current_font = ui->textEdit->currentFont();
    if (current_font.strikeOut()) {
        ui->pushStrike->setChecked(true);
    } else {
        ui->pushStrike->setChecked(false);
    }



}
