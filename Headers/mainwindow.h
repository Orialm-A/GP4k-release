#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
 * @brief The default MainWindow class
 *
 * This class represents the main application window. It contains two
 * TileGroupWidget objects and a QTextEdit for user input, along with
 * the Controller class to handle gamepad inputs.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief MainWindow constructor
     *
     * Initializes the main window, sets up the UI, and creates the
     * necessary widgets.
     *
     * @param parent Optional pointer to the parent widget.
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief MainWindow destructor
     *
     * Cleans up resources used by the MainWindow.
     */
    ~MainWindow();
};

#endif // MAINWINDOW_H
