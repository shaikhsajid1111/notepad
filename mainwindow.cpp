#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    current_file.clear();
    ui->textEdit->setText(QString());


}

void MainWindow::on_actionOpen_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this,"Open the file");
    QFile file(file_name);
    current_file = file_name;

    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"warning","Cannot open file:" + file.errorString());
        return;
    }
    setWindowTitle(file_name);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void MainWindow::on_actionSave_AS_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(this,"Save as");
    QFile file(file_name);

    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"Warning","Cannot Save file" + file.errorString());
        return;
    }
    current_file = file_name;
    setWindowTitle(file_name);
    QTextStream out(&file);

    QString text = ui->textEdit->toPlainText();

    out << text;
    file.close();
}


void MainWindow::on_actionSave_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(this,"Save");
    QFile file(file_name);

    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"Warning","Cannot Save file : " + file.errorString());
        return;
    }
    current_file = file_name;
    setWindowTitle(file_name);
    QTextStream out(&file);

    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();

}

void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;
    printer.setPrinterName("Printer Name: ");

    QPrintDialog pDialog(&printer,this);

    if(pDialog.exec() == QDialog::Rejected){
        QMessageBox::warning(this,"Warning","Cannot Access Printer!");
        return;
    }
    ui->textEdit->print(&printer);
}

void MainWindow::on_actionExit_triggered()
{
    QMessageBox msgBox;
    msgBox.setText("Do you really want to exits?");
    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();

    switch (ret) {
      case QMessageBox::Save:
          on_actionSave_triggered();
          break;
      case QMessageBox::Discard:
            QApplication::quit();
          break;
      case QMessageBox::Cancel:

          break;
      default:
          // should never be reached
          break;
    }

}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}



void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}


void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPAste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionSelect_All_triggered()
{
    ui->textEdit->selectAll();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionFont_triggered()
{
    bool selectedFont;
    QFont font_name = QFontDialog::getFont(&selectedFont,this);
    if(selectedFont){
        ui->textEdit->setCurrentFont(font_name);

    }
}

void MainWindow::on_actionAbout_triggered()
{

    QMessageBox::about(this,"About","Notepad \n\n\nDeveloped By Sajid Shaikh");
}

