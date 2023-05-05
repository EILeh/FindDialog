#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_fileLineEdit_returnPressed();

    void on_keyLineEdit_returnPressed();

    std::vector<std::string> split(std::string line, char separator, bool parts_no_empty = false);

    void on_findPushButton_clicked();

    void on_matchCheckBox_clicked();

private:
    Ui::MainWindow *ui;

    QString FileName_;

    QString WordToBeSearched_;

    bool IsChecked_;
};
#endif // MAINWINDOW_HH
