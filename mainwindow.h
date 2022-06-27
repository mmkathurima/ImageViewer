#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    bool endsWith(const std::string  &fullString, const std::string &ending);
    std::string separator();
    void onPrevClicked();
    void onNextClicked();
    void openDirectory();
    void setImage();
    void keyReleaseEvent(QKeyEvent* keyEvent);
};
#endif // MAINWINDOW_H
