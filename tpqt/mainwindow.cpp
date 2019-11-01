#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QDesktopWidget"
#include <QTextStream>
#include <QFileDialog>
#include <QPrinter>
#include <QPrintDialog>
#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);    

    ui->adminwidget->hide();
    ui->buscarwidget->hide();
    ui->buscadowidget->hide();
    ui->widgetModificar->hide();
    ui->widgetadmventas->hide();

    ui->repositorwidget->hide();
    ui->widgetprodbuscar->hide();
    ui->widgetprodstock->hide();
    ui->widgetprodmodagr->hide();
    ui->widgetprodinfo->hide();

    ui->cajerowidget->hide();

    ui->loginwidget->setGeometry(0,0,450,250);

    ui->adminwidget->setGeometry(0,0,600,350);
    ui->repositorwidget->setGeometry(0,0,600,350);
    ui->cajerowidget->setGeometry(0,0,600,350);

    setMaximumSize(450,250);
    setMinimumSize(450,250);

}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_ingresar_clicked(){
    QString password = ui->passwordline->text();
    QString user= ui->userline->text();
    QString id;
    QString usuarioEnArch;
    QString passwordEnArch;
    QString tipo;
    QString fecha;
    QString vacio;

    QDate fechaactu = QDate::currentDate();
    ui->dateEdit_3->setDate(fechaactu);
    QTime horaactu = QTime::currentTime();
    ui->timeEdit->setTime(horaactu);

    QFile arch("../tpqt/usuarios.txt");

    if (user=="admin" && password=="admin" ){ //ingresar al administrador
        ui->loginwidget->hide();
        ui->adminwidget->show();

        setMaximumSize(600,350);
        setMinimumSize(600,350);

        ui->passwordline->clear();
        ui->userline->clear();

    }else if (arch.open(QIODevice::ReadOnly|QIODevice::Text)) {
        do {
            id = arch.readLine();
            id.chop(1);
            usuarioEnArch = arch.readLine();
            usuarioEnArch.chop(1);
            passwordEnArch = arch.readLine();
            passwordEnArch.chop(1);
            tipo = arch.readLine();
            tipo.chop(1);
            fecha = arch.readLine();
            fecha.chop(1);
            vacio = arch.readLine();

         }while  ((usuarioEnArch!=user||passwordEnArch!=password)&&!arch.atEnd());

        ui->textiduser->setText(id);
        ui->textuseruser->setText(usuarioEnArch);
        ui->textiduser_2->setText(id);
        ui->textuseruser_2->setText(usuarioEnArch);

        if (QString::compare(usuarioEnArch,user,Qt::CaseSensitive)==0
         && QString::compare(passwordEnArch,password,Qt::CaseSensitive)==0) {
            if (QString::compare(tipo,"repositor",Qt::CaseInsensitive)==0){ //ingreso al repositor
                ui->loginwidget->hide();
                ui->repositorwidget->show();
                ui->widgetprodbuscar->show();

                setMaximumSize(600,350);
                setMinimumSize(600,350);
                ui->passwordline->clear();
                ui->userline->clear();

            }
            if (QString::compare(tipo,"cajero",Qt::CaseInsensitive)==0){ //ingreso al repositor
                ui->loginwidget->hide();
                ui->cajerowidget->show();
                ///

                  //  ui->dateTimeEdit->local;
                ///

                setMaximumSize(600,350);
                setMinimumSize(600,350);
                ui->passwordline->clear();
                ui->userline->clear();
            }
        }else {
            QMessageBox::warning(0,"Advertencia","Nombre de usuario o contraseña incorrectos");

        }
      arch.close();

    }}

void MainWindow::on_buscarbutton_clicked(){
    ui->buscarwidget->show();
    ui->widgetAgregar->hide();
}

void MainWindow::on_buscaraccionbutton_clicked(){
    ui->buscadowidget->show();

    QFile arch("../tpqt/usuarios.txt");
    if (arch.open(QIODevice::ReadOnly|QIODevice::Text)) {
        QString usuario= ui->nombreline->text();
        QString id;
        QString usuarioenArch;
        QString contra;
        QString cargo;
        QString fecha;
        QString renglon;

        while (!arch.atEnd() && usuario!=usuarioenArch) {
            id = QString::fromLatin1(arch.readLine());
            id.chop(1);
            usuarioenArch= QString::fromLatin1(arch.readLine());
            usuarioenArch.chop(1);
            contra= QString::fromLatin1(arch.readLine());
            contra.chop(1);
            cargo = QString::fromLatin1(arch.readLine());
            cargo.chop(1);
            fecha = QString::fromLatin1(arch.readLine());
            fecha.chop(1);
            renglon = QString::fromLatin1(arch.readLine());

            if ((QString::compare(usuarioenArch,usuario,Qt::CaseSensitive))==0) {
                ui->lebelcontra->setText(contra);
                ui->lebelid->setText(id);
                ui->lebeluser->setText(usuarioenArch);
                ui->lebelcargo->setText(cargo);
                ui->lebelfecha->setText(fecha);
               }else if(arch.atEnd()){
                QMessageBox::warning(0,"Advertencia","Nombre de usuario no encontrado");
             }
            }
        }
        arch.close();
}

void MainWindow::on_eliminaruserbutton_clicked(){
        QFile arch("../tpqt/usuarios.txt");
        QFile arch2("../tpqt/usuarios.tmp");
        if (arch.open(QIODevice::ReadOnly|QIODevice::Text) && arch2.open(QIODevice::WriteOnly|QIODevice::Text)) {
            QTextStream out (&arch2);
            QString id=ui->lebelid->text();
            QString idEnArch;
            QString renglon;
            while (!arch.atEnd()) {
                idEnArch = arch.readLine();
                idEnArch.chop(1);
                if (idEnArch != id) {
                    out << idEnArch << "\n";
                }
                do {
                    renglon = QString::fromLatin1(arch.readLine());
                    renglon.chop(1);
                    if (idEnArch != id) {
                        out << renglon << "\n";
                    }
                } while (renglon != "*");
            }
            arch.close();
            arch2.close();
            arch.remove();
            arch2.rename("../tpqt/usuarios.txt");
            QMessageBox::information(NULL, "BORRADO EXITOSO", "Se ha borrado el usuario " + ui->lebeluser->text());
        }
}

void MainWindow::on_buttonModificar_clicked(){
    ui->buscarwidget->hide();
    ui->widgetModificar->show();
    ui->widgetModificar->setGeometry(130,30,460,310);

    QDate fechaactu = QDate::currentDate();
    ui->dateEdit->setDate(fechaactu);

    QString id = ui->lebelid->text();
    QString usuarioenArch = ui->lebeluser->text();
    QString contra=ui->lebelcontra->text();
    QString cargo=ui->lebelcargo->text();
    QString fecha=ui->lebelfecha->text();


    ui->lebelid_2->setText(id);
    ui->lineusuario->setText(usuarioenArch);
    ui->lineContra->setText(contra);
}

void MainWindow::on_buttonAceptar_clicked(){
    QFile arch("../tpqt/usuarios.txt");
    QFile arch2("../tpqt/usuarios.tmp");
    if (arch.open(QIODevice::ReadOnly|QIODevice::Text) && arch2.open(QIODevice::WriteOnly|QIODevice::Text)) {
        QTextStream out (&arch2);
        QString id=ui->lebelid_2->text();
        QString idEnArch;
        QString renglon;

        QString usuario= ui->lineusuario->text();
        QString contra=ui->lineContra->text();
        QString cargo=ui->cargonover->text();
        QString fecha=ui->dateEdit->text();

        while (!arch.atEnd()) {
            idEnArch = arch.readLine();
            idEnArch.chop(1);
            out << idEnArch << "\n";

            do {
                renglon = QString::fromLatin1(arch.readLine());
                renglon.chop(1);
                if (id != idEnArch) {
                    out << renglon << "\n";
                }
            } while (renglon != "*");
            if (id == idEnArch) {
                out << usuario << "\n";
                out << contra << "\n";
                out << cargo << "\n";
                out << fecha << "\n";
                out << "*\n";
            }
        }
        arch.close();
        arch2.close();
        arch.remove();
        arch2.rename("../tpqt/usuarios.txt");
        QMessageBox::information(NULL, "MODOFICADO EXITOSO", "Se ha modificado el usuario " + ui->lebeluser->text());
    }
}

void MainWindow::on_radioRepositor_clicked(){
    ui->cargonover->setText("Repositor");
}

void MainWindow::on_radioCajero_clicked(){
    ui->cargonover->setText("Cajero");
}

void MainWindow::on_radioRepositor_2_clicked(){
    ui->cargonover->setText("Repositor");
}

void MainWindow::on_radioCajero_2_clicked(){
    ui->cargonover->setText("Cajero");
}

void MainWindow::on_agregarbutton_clicked(){
    ui->widgetModificar->hide();
    ui->widgetAgregar->show();
    ui->widgetAgregar->setGeometry(130,30,460,310);

    QDate fechaactu = QDate::currentDate();
    ui->dateEdit_2->setDate(fechaactu);

    int id = 0;
    QFile arch("../tpqt/usuarios.txt");
    if (arch.open(QIODevice::ReadOnly|QIODevice::Text)) {
        QString idStr;
        QString renglon;
        while (!arch.atEnd()) {
            idStr = QString::fromLatin1(arch.readLine());
            id = idStr.toInt();
            do {
                renglon=arch.readLine();
                renglon.chop(1);
            }
            while (renglon != "*");
        }
    }
    id++;
    ui->lebelid_3->setNum(id);
}

void MainWindow::on_buttonAceptar_2_clicked(){
    QString id= ui->lebelid_3->text();
    QString usuario= ui->linenewusuario->text();
    QString contra= ui->linenewcontra->text();
    QString cargo= ui->cargonover->text();
    QString fecha= ui->dateEdit_2->text();

    if (ui->linenewusuario->text().isEmpty()) {
        QMessageBox::warning(NULL, "Advertencia", "Debe ingresar el nombre del usuario");
    }else if(ui->linenewcontra->text().isEmpty()){
        QMessageBox::warning(NULL, "Advertencia", "Debe ingresar la contraseña del usuario");
    }else {
        QFile arch("../tpqt/usuarios.txt");
        if (arch.open(QIODevice::Append|QIODevice::Text)) {

    QTextStream out (&arch);
    out << id << "\n";
    out << usuario << "\n";
    out << contra << "\n";
    out << cargo << "\n";
    out << fecha << "\n";
    out << "*\n";
    arch.close();
    QMessageBox::information(NULL, "GRABACIÓN EXITOSA",  usuario + " ha sido agregada correctamente");
}    }
    QString idnew = ui->lebelid_3->text();
    int idInt = idnew.toInt();
    idInt++;
    ui->lebelid_3->setNum(idInt);
    ui->linenewusuario->clear();
    ui->linenewcontra->clear();
    ui->dateEdit_2->clear();


}


void MainWindow::on_buttonprodbusc_clicked()
{
    QString codigobuscar = ui->lineprodcodigo->text();

    QString id;
    QString codigo;
    QString nombre;
    QString fabricante;
    QString stock;
    QString precio;
    QString imagen;
    QString asterisco;

    QFile arch("../tpqt/productos.txt");

    bool encontrado=false;

    if(arch.open(QIODevice::ReadOnly|QIODevice::Text)){
        do{
            id =arch.readLine();
            id.chop(1);
            codigo=arch.readLine();
            codigo.chop(1);
            nombre=arch.readLine();
            nombre.chop(1);
            fabricante=arch.readLine();
            fabricante.chop(1);
            stock=arch.readLine();
            stock.chop(1);
            precio=arch.readLine();
            precio.chop(1);
            imagen=arch.readLine();
            imagen.chop(1);
            asterisco=arch.readLine();


            if (codigobuscar == codigo){
                encontrado=true;}

         }while(codigobuscar != codigo && !arch.atEnd());

        if(encontrado){
           ui->widgetprodinfo->show();
           ui->textprodid->setText(id);
           ui->textprodcodigo->setText(codigo);
           ui->textprodnombre->setText(nombre);
           ui->textprodfabricant->setText(fabricante);
           ui->textprodstock->setText(stock);
           ui->textprodprecio->setText(precio);

           ui->imagenprod->setPixmap(QPixmap(imagen));
           ui->imagenprod->setScaledContents(true);
           ui->textprodimagen->setText(imagen);
        }else {
            QMessageBox::warning(0,"Advertencia","Producto no encontrado.");
}
        arch.close();
    }

}

void MainWindow::on_atrasbutton_2_clicked()
{
    ui->widgetprodinfo->hide();
}


void MainWindow::on_eliminaruserbutton_2_clicked()
{
    QFile arch("../tpqt/productos.txt");
    QFile arch2("../tpqt/productos.tmp");

    if (arch.open(QIODevice::ReadOnly|QIODevice::Text) && arch2.open(QIODevice::WriteOnly|QIODevice::Text)) {

        QTextStream out (&arch2);
        QString id=ui->textprodid->text();
        QString idEnArch;
        QString renglon;
        while (!arch.atEnd()) {
            idEnArch = arch.readLine();
            idEnArch.chop(1);
            if (idEnArch != id) {
                out << idEnArch << "\n";
            }
            do {
                renglon = QString::fromLatin1(arch.readLine());
                renglon.chop(1);
                if (idEnArch != id) {
                    out << renglon << "\n";}
            } while (renglon != "*");
        }
        arch.close();
        arch2.close();
        arch.remove();
        arch2.rename("../tpqt/productos.txt");

        QMessageBox::information(NULL, "BORRADO EXITOSO", "Se ha borrado el producto " + ui->textprodnombre->text());
        ui->widgetprodinfo->show();
    }
}

void MainWindow::on_buttonModificar_2_clicked()
{
    ui->textprodmodagr->setText("Modificar");
    ui->widgetprodbuscar->hide();
    ui->widgetprodmodagr->show();
    ui->widgetprodmodagr->setGeometry(80,30,520,320);

    QString id =ui->textprodid->text();
    QString codigo=ui->textprodcodigo->text();
    QString nombre=ui->textprodnombre->text();
    QString fabricante=ui->textprodfabricant->text();
    QString stock=ui->textprodstock->text();
    QString precio=ui->textprodprecio->text();
    QString imagen=ui->textprodimagen->text();

    ui->textprodidmodagr->setText(id);
    ui->lineprodcodigomodagr->setText(codigo);
    ui->lineprodnombre->setText(nombre);
    ui->lineprodfabrcant->setText(fabricante);
    ui->textprodstockmodagr->setText(stock);
    ui->lineprodorecio->setText(precio);
    ui->lineprodimagen->setText(imagen);
}

void MainWindow::on_atrasbutton_3_clicked()
{
    ui->widgetprodbuscar->show();
    ui->widgetprodstock->hide();
    ui->widgetprodmodagr->hide();
    ui->widgetprodinfo->hide();
}


void MainWindow::on_atrasbutton_5_clicked()
{
    ui->widgetprodbuscar->show();
    ui->widgetprodstock->hide();
    ui->widgetprodmodagr->hide();
    ui->widgetprodinfo->hide();
}

void MainWindow::on_atrasbutton_10_clicked()
{
    ui->buscarwidget->show();
    ui->widgetModificar->hide();
    ui->widgetAgregar->hide();
}

void MainWindow::on_atrasbutton_9_clicked()
{
    ui->buscarwidget->show();
    ui->widgetModificar->hide();
    ui->widgetAgregar->hide();
}


void MainWindow::on_buttonprodaceptarmodagr_clicked()
{
    QString modo=ui->textprodmodagr->text();
if (modo=="Modificar"){
    QFile arch("../tpqt/productos.txt");
    QFile arch2("../tpqt/productos.tmp");
    if (arch.open(QIODevice::ReadOnly|QIODevice::Text) && arch2.open(QIODevice::WriteOnly|QIODevice::Text)) {
        QTextStream out (&arch2);
        QString id=ui->textprodidmodagr->text();
        QString idEnArch;
        QString renglon;

        QString codigo=ui->lineprodcodigomodagr->text();
        QString nombre=ui->lineprodnombre->text();
        QString fabricante=ui->lineprodfabrcant->text();
        QString stock=ui->textprodstockmodagr->text();
        QString precio=ui->lineprodorecio->text();
        QString imagen=ui->lineprodimagen->text();

        while (!arch.atEnd()) {
            idEnArch = arch.readLine();
            idEnArch.chop(1);
            out << idEnArch << "\n";

            do {
                renglon = QString::fromLatin1(arch.readLine());
                renglon.chop(1);
                if (id != idEnArch) {
                    out << renglon << "\n";
                }
            } while (renglon != "*");
            if (id == idEnArch) {
                out << codigo << "\n";
                out << nombre << "\n";
                out << fabricante << "\n";
                out << stock << "\n";
                out << precio << "\n";
                out << imagen << "\n";
                out << "*\n";
            }
        }
        arch.close();
        arch2.close();
        arch.remove();
        arch2.rename("../tpqt/productos.txt");
        QMessageBox::information(NULL, "MODOFICADO EXITOSO", "Se ha modificado el producto " + nombre);

        ui->lineprodcodigomodagr->clear();
        ui->lineprodnombre->clear();
        ui->lineprodfabrcant->clear();
        ui->textprodstockmodagr->setText("0");
        ui->lineprodorecio->clear();
        ui->lineprodimagen->clear();
        ui->widgetprodmodagr->hide();
        ui->widgetprodbuscar->show();
        ui->widgetprodinfo->show();

    }
    }else if (modo=="Agregar") {
    QString id=ui->textprodidmodagr->text();

    QString codigo=ui->lineprodcodigomodagr->text();
    QString nombre=ui->lineprodnombre->text();
    QString fabricante=ui->lineprodfabrcant->text();
    QString stock=ui->textprodstockmodagr->text();
    QString precio=ui->lineprodorecio->text();
    QString imagen=ui->lineprodimagen->text();

    if (ui->lineprodcodigomodagr->text().isEmpty()) {
        QMessageBox::warning(NULL, "Advertencia", "Debe ingresar el codigo del producto");
    }else if(ui->lineprodnombre->text().isEmpty()){
        QMessageBox::warning(NULL, "Advertencia", "Debe ingresar el nombre del producto");
    }else if(ui->lineprodfabrcant->text().isEmpty()){
        QMessageBox::warning(NULL, "Advertencia", "Debe ingresar el nombre del fabricante del producto");
    }else if(ui->lineprodorecio->text().isEmpty()){
        QMessageBox::warning(NULL, "Advertencia", "Debe ingresar el precio del producto");
    }else if(ui->lineprodimagen->text().isEmpty()){
        QMessageBox::warning(NULL, "Advertencia", "Debe ingresar una imagen del producto");
    }else{
        QFile arch("../tpqt/productos.txt");
        if (arch.open(QIODevice::Append|QIODevice::Text)) {

    QTextStream out (&arch);
    out << id << "\n";
    out << codigo << "\n";
    out << nombre << "\n";
    out << fabricante << "\n";
    out << "0" << "\n";
    out << precio << "\n";
    out << imagen << "\n";
    out << "*\n";
    arch.close();
    QMessageBox::information(NULL, "GRABACIÓN EXITOSA",  nombre + " ha sido agregada correctamente");

    ui->lineprodcodigomodagr->clear();
    ui->lineprodnombre->clear();
    ui->lineprodfabrcant->clear();
    ui->lineprodorecio->clear();
    ui->lineprodimagen->clear();

    int idInt = id.toInt();
    idInt++;
    ui->textprodidmodagr->setNum(idInt);

}    }
}
}

void MainWindow::on_buttonprodnuevo_clicked()
{
    ui->textprodmodagr->setText("Agregar");

    ui->widgetprodbuscar->hide();
    ui->widgetprodstock->hide();
    ui->widgetprodmodagr->show();
    ui->widgetprodinfo->hide();
    ui->widgetprodmodagr->setGeometry(80,30,520,320);

    int id = 0;
    QFile arch("../tpqt/usuarios.txt");
    if (arch.open(QIODevice::ReadOnly|QIODevice::Text)) {
        QString idStr;
        QString renglon;
        while (!arch.atEnd()) {
            idStr = QString::fromLatin1(arch.readLine());
            id = idStr.toInt();
            do {
                renglon=arch.readLine();
                renglon.chop(1);
            }
            while (renglon != "*");
        }
    }
    id++;
    ui->textprodidmodagr->setNum(id);
}

void MainWindow::on_buttonModificar_3_clicked()
{
    ui->widgetprodstock->setGeometry(80,30,520,320);
    ui->widgetprodbuscar->hide();
    ui->widgetprodstock->show();
    ui->widgetprodmodagr->hide();
    ui->widgetprodinfo->hide();

    ui->textidprod_2->setText(ui->textprodid->text());
    ui->textcodigoprod_2->setText(ui->textprodcodigo->text());
    ui->textnombreprod_2->setText(ui->textprodnombre->text());
    ui->textfabricantprod_2->setText(ui->textprodfabricant->text());
    ui->textprecioprod_2->setText(ui->textprodprecio->text());
    ui->textstockprod->setText(ui->textprodstock->text());
    ui->textimagenprod->setText(ui->textprodimagen->text());
    ui->imagenprod_4->setPixmap(QPixmap(ui->textprodimagen->text()));
    ui->imagenprod_4->setScaledContents(true);
    ui->textimagenprod->setText(ui->textprodimagen->text());

}

void MainWindow::on_buttonprodexaminarimagen_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Abrir archivo de imagen",
                                                    QDir::currentPath(),
                                                    "Fotos (*.png *.jpg);;Gráficos (*.gif)");
    ui->lineprodimagen->setText(fileName);
    if (ui->lineprodimagen->text().isEmpty()) {
        ui->lineprodimagen->setFocus();
    }
    ui->imagenprod_2->setPixmap(QPixmap(fileName));
    ui->imagenprod_2->setScaledContents(true);
}

void MainWindow::on_buttonprodagregarstock_clicked(){
    QFile arch("../tpqt/productos.txt");
    QFile arch2("../tpqt/productos.tmp");
    if (arch.open(QIODevice::ReadOnly|QIODevice::Text) && arch2.open(QIODevice::WriteOnly|QIODevice::Text)) {
        QTextStream out (&arch2);
        QString id=ui->textidprod_2->text();
        QString idEnArch;
        QString renglon;

        QString codigo=ui->textcodigoprod_2->text();
        QString nombre=ui->textnombreprod_2->text();
        QString fabricante=ui->textfabricantprod_2->text();
        QString stock=ui->textstockprod->text();
        QString newstock=ui->lineprodnewstock->text();
        int stockInt=(stock.toInt())+(newstock.toInt());
        QString precio=ui->textprecioprod_2->text();
        QString imagen=ui->textimagenprod->text();

        while (!arch.atEnd()) {
            idEnArch = arch.readLine();
            idEnArch.chop(1);
            out << idEnArch << "\n";

            do {
                renglon = QString::fromLatin1(arch.readLine());
                renglon.chop(1);
                if (id != idEnArch) {
                    out << renglon << "\n";
                }
            } while (renglon != "*");
            if (id == idEnArch) {
                out << codigo << "\n";
                out << nombre << "\n";
                out << fabricante << "\n";
                out << stockInt << "\n";
                out << precio << "\n";
                out << imagen << "\n";
                out << "*\n";
                ui->textstockprod->setNum(stockInt);
                ui->lineprodnewstock->clear();
            }
        }
        arch.close();
        arch2.close();
        arch.remove();
        arch2.rename("../tpqt/productos.txt");
        QMessageBox::information(NULL, "STOCK MODOFICADO EXITOSO", "Se ha modificado el stock del producto " + nombre);


}}

void MainWindow::on_atrasbutton_clicked()
{
    setMaximumSize(450,250);
    setMinimumSize(450,250);
    ui->loginwidget->show();
    ui->adminwidget->hide();
    this->setGeometry(300,200,450,250);

}

void MainWindow::on_atrasbutton_7_clicked()
{
    setMaximumSize(450,250);
    setMinimumSize(450,250);
    ui->loginwidget->show();
    ui->cajerowidget ->hide();
    this->setGeometry(300,200,450,250);
}

void MainWindow::on_atrasbutton_11_clicked()
{
    setMaximumSize(450,250);
    setMinimumSize(450,250);
    ui->loginwidget->show();
    ui->repositorwidget->hide();
    this->setGeometry(300,200,450,250);

}

void MainWindow::on_buttonprodagregarstock_3_clicked()
{
    ui->widgetcajiniciar->hide();
    ui->widgetcajactual->show();
    ui->widgetcajactual->setGeometry(130,30,460,310);
    QString fecha= ui->dateEdit_3->text();
    QString hora = ui->timeEdit->text();

    QFile arch1("../tpqt/ventaact.txt");
    if (arch1.open(QIODevice::WriteOnly|QIODevice::Text)) {
        QTextStream out (&arch1);
        out<<"";
        arch1.close();
    }

    QFile arch("../tpqt/ventaact.txt");
    if (arch.open(QIODevice::Append|QIODevice::Text)) {
        QTextStream out (&arch);
        out << "Caja actual:\n";
        out <<"Fecha:"<<"\n"<<fecha << "\n";
        out <<"Hora: "<< hora<<"\n";
        out<<"Cajero: "<< ui->textuseruser_2->text()<<"\n";

        arch.close();

    }

    QFile arch2("../tpqt/ventaact.txt");
    if (arch2.open(QIODevice::ReadOnly|QIODevice::Text)) {
        ui->texteditcajaact->setPlainText(arch2.readAll());
        arch2.close();
    }
}

void MainWindow::on_buttonprodagregarstock_2_clicked()
{
    ui->widgetcajactual->hide();
    ui->widgetcajproduct->show();
    ui->widgetcajproduct->setGeometry(130,30,460,310);
    ui->buttonprodagregarstock_4->setText("AGREGAR");

}

void MainWindow::on_atrasbutton_12_clicked()
{
    QString codbuscar = ui->lineeditcajbuscar->text();
    QString id;
    QString codigo;
    QString nombre;
    QString fabricante;
    QString stock;
    QString precio;
    QString imagen;
    QString asterisco;

    QFile arch("../tpqt/productos.txt");
    bool encontrado=false;
    if(arch.open(QIODevice::ReadOnly|QIODevice::Text)){
        do{
            id =arch.readLine();
            id.chop(1);
            codigo=arch.readLine();
            codigo.chop(1);
            nombre=arch.readLine();
            nombre.chop(1);
            fabricante=arch.readLine();
            fabricante.chop(1);
            stock=arch.readLine();
            stock.chop(1);
            precio=arch.readLine();
            precio.chop(1);
            imagen=arch.readLine();
            imagen.chop(1);
            asterisco=arch.readLine();


            if (codbuscar == codigo){
                encontrado=true;}

         }while(codbuscar != codigo && !arch.atEnd());

        if(encontrado){
           ui->textidcajero->setText(id);
           ui->textcajprod->setText(nombre);
           ui->textcajabreb->setText(fabricante);
           ui->textcajstock->setText(stock);
           ui->textcajprecio->setText(precio);

           ui->imagencaj->setPixmap(QPixmap(imagen));
           ui->imagencaj->setScaledContents(true);

           ui->imagencajero->setText(imagen);

        }else {
            QMessageBox::warning(0,"Advertencia","Producto no encontrado.");
}
        arch.close();
    }
}

void MainWindow::on_buttonprodagregarstock_4_clicked(){
    if(!ui->lineprodnewstock_2->text().isEmpty()){
        ui->widgetcajproduct->show();
        ui->widgetcajactual->hide();


        QFile arch("../tpqt/ventaact.txt");
        if (arch.open(QIODevice::Append|QIODevice::Text)) {
            QTextStream out (&arch);
            QString preciotext= ui->textcajprecio->text();
            int preciotextint = preciotext.toInt();
            QString cantidadtext = ui->lineprodnewstock_2->text();
            int cantidadtextint = cantidadtext.toInt();

            out <<ui->lineeditcajbuscar->text()<< "\n";
            if (ui->buttonprodagregarstock_4->text()=="AGREGAR"){
                out <<ui->textcajabreb->text()<<" x " << ui->lineprodnewstock_2->text()<<"  "<< preciotextint * cantidadtextint <<"\n";
                }else{
                out <<ui->textcajabreb->text()<<" x " << ui->lineprodnewstock_2->text()<<"  "<< -preciotextint * cantidadtextint <<"\n";
                }
            arch.close();
        }

            QFile arch1("../tpqt/productos.txt");
            QFile arch2("../tpqt/productos.tmp");
            if (arch1.open(QIODevice::ReadOnly|QIODevice::Text) && arch2.open(QIODevice::WriteOnly|QIODevice::Text)) {
                QTextStream out (&arch2);
                QString id=ui->textidcajero->text();
                QString idEnArch;
                QString renglon;

                QString codigo=ui->lineeditcajbuscar->text();
                QString nombre=ui->textcajprod->text();
                QString fabricante=ui->textcajabreb->text();
                QString stock=ui->textcajstock->text();
                QString newstock=ui->lineprodnewstock_2->text();
                int stockInt;
                if (ui->buttonprodagregarstock_4->text()=="AGREGAR"){
                    stockInt=(stock.toInt())-(newstock.toInt());
                }else{
                    stockInt=(stock.toInt());
                }
                QString precio=ui->textcajprecio->text();
                QString imagen=ui->imagencajero->text();

                while (!arch1.atEnd()) {
                    idEnArch = arch1.readLine();
                    idEnArch.chop(1);
                    out << idEnArch << "\n";

                    do {
                        renglon = QString::fromLatin1(arch1.readLine());
                        renglon.chop(1);
                        if (id != idEnArch) {
                            out << renglon << "\n";
                        }
                    } while (renglon != "*");
                    if (id == idEnArch) {
                        out << codigo << "\n";
                        out << nombre << "\n";
                        out << fabricante << "\n";
                        out << stockInt << "\n";
                        out << precio << "\n";
                        out << imagen << "\n";
                        out << "*\n";
                        ui->textcajstock->setNum(stockInt);
                        }
                }
                arch1.close();
                arch2.close();
                arch1.remove();
                arch2.rename("../tpqt/productos.txt");

          if (ui->buttonprodagregarstock_4->text()=="AGREGAR"){
                ui->lineprodnewstock_2->text();
                ui->textcajprecio->text();
                QString preciototalstr= ui->textcajpreciototal->text();
                int preciototalint = preciototalstr.toInt()+(newstock.toInt()* precio.toInt());
                ui->textcajpreciototal->setNum(preciototalint);
   }else {
              ui->lineprodnewstock_2->text();
              ui->textcajprecio->text();
              QString preciototalstr= ui->textcajpreciototal->text();
              int preciototalint = preciototalstr.toInt()-(newstock.toInt()* precio.toInt());
              ui->textcajpreciototal->setNum(preciototalint);

} }

            ui->textidcajero->setText("########");
            ui->textcajprod->setText("########");
            ui->textcajabreb->setText("########");
            ui->textcajstock->setText("########");
            ui->textcajprecio->setText("########");
            ui->lineprodnewstock_2->clear();

            ui->imagencaj->setPixmap(QPixmap("#######"));
            ui->imagencaj->setScaledContents(true);

            ui->widgetcajproduct->hide();
            ui->widgetcajactual->show();

            QFile arch3("../tpqt/ventaact.txt");
            if (arch3.open(QIODevice::ReadOnly|QIODevice::Text)) {
                ui->texteditcajaact->setPlainText(arch3.readAll());
                arch3.close();
        }
        }else{
        QMessageBox::warning(0,"Advertencia","Ingrese cantidad a comprar.");
    }}


void MainWindow::on_atrasbutton_8_clicked()
{
    ui->textidcajero->setText("########");
    ui->textcajprod->setText("########");
    ui->textcajabreb->setText("########");
    ui->textcajstock->setText("########");
    ui->textcajprecio->setText("########");

    ui->imagencaj->setPixmap(QPixmap("#######"));
    ui->imagencaj->setScaledContents(true);

    ui->widgetcajproduct->hide();
    ui->widgetcajactual->show();
}

void MainWindow::on_buttonprodagregarstock_6_clicked()
{
    ui->widgetcajactual->hide();
    ui->widgetcajproduct->show();
    ui->widgetcajproduct->setGeometry(130,30,460,310);
    ui->buttonprodagregarstock_4->setText("SACAR");
}

void MainWindow::on_atrasbutton_6_clicked()
{
    ui->widgetcajactual->hide();
    ui->widgetcajiniciar->show();
    ui->texteditcajaact->clear();
    ui->textcajpreciototal->setNum(0);
    QDate fechaactu = QDate::currentDate();
    ui->dateEdit_3->setDate(fechaactu);
    QTime horaactu = QTime::currentTime();
    ui->timeEdit->setTime(horaactu);

    QFile arch("../tpqt/ventaact.txt");
    if (arch.open(QIODevice::WriteOnly|QIODevice::Text)) {
        QTextStream out (&arch);
        out<<"";
        arch.close();
    }
}

void MainWindow::on_buttonprodagregarstock_5_clicked()
{
    QFile arch("../tpqt/ventaact.txt");
    if (arch.open(QIODevice::Append|QIODevice::Text)) {
        QTextStream out (&arch);
        out <<"TOTAL:     "<<ui->textcajpreciototal->text()<<" $"<< "\n";
        ui->texteditcajaact->setPlainText(arch.readAll());
        out<<"Muchas gracias por su compra!"<<"\n"<<"Ticket no valido como factura"<<"\n";
        arch.close();
    }

    QString renglon;
    QString cuerpo;

    QFile arch1("../tpqt/ventaact.txt");
    QFile arch2("../tpqt/ventastotales.txt");
    if (arch1.open(QIODevice::ReadOnly|QIODevice::Text) && arch2.open(QIODevice::Append|QIODevice::Text)) {
        QTextStream out (&arch2);

        renglon = arch1.readLine();
        renglon = arch1.readLine();
        cuerpo = arch1.readAll();
        out<<cuerpo;
        ui->texteditcajaact->setPlainText(cuerpo);
        arch1.close();
        arch2.close();
    }


    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog printDialog(&printer, NULL);
    if (printDialog.exec() == QDialog::Accepted) {
        ui->texteditcajaact->print(&printer);
    }
    ui->widgetcajactual->hide();
    ui->widgetcajiniciar->show();

}

void MainWindow::on_buscarbutton_2_clicked()
{
    ui->widgetadmventas->show();
    ui->widgetadmventas->setGeometry(130,30,460,310);
    ui->widgetModificar->hide();
    ui->buscarwidget->hide();
    ui->widgetAgregar->hide();

    QFile arch("../tpqt/ventastotales.txt");
    if (arch.open(QIODevice::ReadOnly|QIODevice::Text)) {
        ui->TextEditventas->setPlainText(arch.readAll());
        arch.close();
    }
}

void MainWindow::on_atrasbutton_13_clicked()
{
    ui->widgetadmventas->hide();
    ui->widgetModificar->hide();
    ui->buscarwidget->show();
    ui->widgetAgregar->hide();

}
