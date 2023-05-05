#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <fstream>
#include <vector>
#include <map>
#include <set>

using Dictionary = std::set<std::string>;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

std::vector<std::string> MainWindow::split(std::string line, char separator,
                                           bool parts_no_empty)
{

    std::vector<std::string> splitted_vector = {};
    std::string substring = "";

    if ( !ui->matchCheckBox->isChecked() )
    {
        for ( char c : line )
        {
            c = std::tolower(c);
            if ( c == separator )
            {
                if (!(parts_no_empty && substring.empty()))
                {
                    splitted_vector.push_back(substring);
                    substring.clear();
                }
            }

            else
            {
                substring += c;
            }
        }
        if (!(parts_no_empty && substring.empty()))
        {
            splitted_vector.push_back(substring);
            substring.clear();
        }
    }

    else
    {
        for ( char c : line )
        {
            if ( c == separator )
            {
                if (!(parts_no_empty && substring.empty()))
                {
                    splitted_vector.push_back(substring);
                    substring.clear();
                }
            }

            else
            {
                substring += c;
            }
        }
        if (!(parts_no_empty && substring.empty()))
        {
            splitted_vector.push_back(substring);
            substring.clear();
        }
    }


    return splitted_vector;

}


void MainWindow::on_fileLineEdit_returnPressed()
{

    FileName_ = ui->fileLineEdit->text();
}


void MainWindow::on_keyLineEdit_returnPressed()
{
    WordToBeSearched_ = ui->keyLineEdit->text();

}


void MainWindow::on_findPushButton_clicked()
{
    Dictionary word_count;

    FileName_ = ui->fileLineEdit->text();

    WordToBeSearched_ = ui->keyLineEdit->text();

    QString text = "";

    std::string line = "";

    std::ifstream FileObject (FileName_.toStdString());

    if ( !FileObject )
    {
        text += "File not found";
        ui->textBrowser->setText(text);
    }

    else
    {
        if ( WordToBeSearched_.size() == 0 )
        {
            text += "File found";
            ui->textBrowser->setText(text);
        }

        else
        {
            while ( getline(FileObject, line) )
            {

                std::vector<std::string> words = split(line, ' ', true);

                for ( std::string word : words )
                {
                    word_count.insert(word);
                }

            }

                if ( !ui->matchCheckBox->isChecked() )
                {
                    WordToBeSearched_ = ui->keyLineEdit->text().toLower();

                    auto it = std::find(word_count.begin(), word_count.end(),
                                    WordToBeSearched_.toStdString());
                    if ( it != word_count.end() )
                    {
                        text += "Word found";
                        ui->textBrowser->toPlainText();

                        ui->textBrowser->setText(text);
                        return;
                    }

                    else
                    {
                        text += "Word not found";
                        ui->textBrowser->toPlainText();

                        ui->textBrowser->setText(text);
                        return;

                    }
                }
                else
                {
                    auto it = std::find(word_count.begin(), word_count.end(),
                                    WordToBeSearched_.toStdString());
                    if ( it != word_count.end() )
                    {
                        text += "Word found";
                        ui->textBrowser->setText(text);
                        return;
                    }

                    else
                    {
                        text += "Word not found";
                        ui->textBrowser->setText(text);
                        return;

                    }
                }

            }
        }

        FileObject.close();

}


void MainWindow::on_matchCheckBox_clicked()
{
    IsChecked_ = ui->matchCheckBox->isChecked();
}

