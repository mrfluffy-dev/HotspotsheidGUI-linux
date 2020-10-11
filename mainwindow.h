#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QTimer *timer; // NEW

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onButtonClicked();
    void ConnectStatus();
    void connectionUpdate();
    void TimerSlot();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
