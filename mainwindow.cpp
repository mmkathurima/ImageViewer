#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <filesystem>
#include <QFileDialog>
#include <QDebug>
#include <QKeyEvent>
#include <string>
#include <vector>
#include <iostream>
#include <dirent.h>


std::vector<std::string> ext{"png","jpg","bmp"};
std::vector<std::string> path;
std::vector<std::string> finalPath;
static int position = 0;
QString directory;

bool MainWindow::endsWith(const std::string  &fullString, const std::string &ending) {
    return (fullString.length() >= ending.length()) ?
                (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending)) : false;
}

std::string MainWindow::separator(){
    #ifdef _WIN32
        return "\\";
    #else
        return "/";
    #endif
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->picture->setScaledContents(true);
    ui->picture->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    connect(ui->prev, &QPushButton::clicked, this, &MainWindow::onPrevClicked);
    connect(ui->next, &QPushButton::clicked, this, &MainWindow::onNextClicked);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openDirectory);
}

void MainWindow::onPrevClicked(){
    position = (position > 0) ? position - 1 : finalPath.size() - 1;
    setImage();
}

void MainWindow::onNextClicked(){
    position = ((unsigned) position < finalPath.size() - 1) ? position + 1 : 0;
    setImage();
}

void MainWindow::openDirectory(){
    DIR *dir;
    struct dirent *diread;
    path.clear();
    finalPath.clear();

    directory=QFileDialog::getExistingDirectory(this, tr("Open Directory"), nullptr
                                              ,QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if ((dir = opendir(directory.toStdString().c_str())) != nullptr) {
        while ((diread = readdir(dir)) != nullptr) {
            path.push_back(diread->d_name);
        }
        closedir(dir);
    } else {
        qDebug() << "opendir";
    }
    for(const std::string& s : path){
        for(const std::string& exts : ext){
            if(endsWith(s,exts)){
                qDebug() <<QString::fromStdString(s);
                finalPath.push_back(s);
            }
        }
    }
    qDebug() << directory+QString::fromStdString(separator())+finalPath.at(position).c_str();
    setImage();
}

void MainWindow::setImage(){
    try{
        QPixmap pix(directory+QString::fromStdString(separator())+finalPath.at(position).c_str());
        ui->picture->setPixmap(pix);
    } catch(std::exception& ex){
        ui->picture->setText("Error in displaying image");
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent* keyEvent){
    switch(keyEvent->key()){
        case Qt::Key_Left:
            onPrevClicked();
        break;
        case Qt::Key_Right:
            onNextClicked();
        break;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

