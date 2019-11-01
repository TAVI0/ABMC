#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ingresar_clicked();

    void on_buscarbutton_clicked();

    void on_buscaraccionbutton_clicked();

    void on_eliminaruserbutton_clicked();

    void on_buttonModificar_clicked();

    void on_buttonAceptar_clicked();

    void on_radioRepositor_clicked();

    void on_radioCajero_clicked();

    void on_radioRepositor_2_clicked();

    void on_radioCajero_2_clicked();

    void on_agregarbutton_clicked();

    void on_buttonAceptar_2_clicked();

    void on_buttonprodbusc_clicked();

    void on_atrasbutton_2_clicked();

    void on_eliminaruserbutton_2_clicked();

    void on_buttonModificar_2_clicked();

    void on_atrasbutton_3_clicked();

    void on_buttonprodaceptarmodagr_clicked();

    void on_buttonprodnuevo_clicked();

    void on_buttonModificar_3_clicked();

    void on_buttonprodexaminarimagen_clicked();

    void on_buttonprodagregarstock_clicked();

    void on_atrasbutton_5_clicked();

    void on_atrasbutton_10_clicked();

    void on_atrasbutton_9_clicked();

    void on_atrasbutton_clicked();

    void on_atrasbutton_7_clicked();

    void on_atrasbutton_11_clicked();

    void on_buttonprodagregarstock_3_clicked();

    void on_buttonprodagregarstock_2_clicked();

    void on_atrasbutton_12_clicked();

    void on_buttonprodagregarstock_4_clicked();

    void on_atrasbutton_8_clicked();

    void on_buttonprodagregarstock_6_clicked();

    void on_atrasbutton_6_clicked();

    void on_buttonprodagregarstock_5_clicked();

    void on_buscarbutton_2_clicked();

    void on_atrasbutton_13_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
