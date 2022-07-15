#include "paint.h"
#include "ui_principal.h"



#define DEFAULT_ANCHO 3

Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);

    // Creando la imagen (Una imagen en blanco que funcione como lienzo)
    mImagen = new QImage(this->size(),QImage::Format_ARGB32_Premultiplied);
    // Establecemos el color de la imagen en blanco
    // (Podemos modificar al color que querramos usar como lienzo)
    mImagen->fill(Qt::white);
    // Instanciar el Painter a partir de la imagen
    mPainter = new QPainter(mImagen);
    mPainter->setRenderHint(QPainter::Antialiasing);
    // Inicialisamos variables como el color del pincel
    // El ancho y el numero de lineas
    mPuedeDibujar = false;
    mColor = Qt::black;
    //Valor preestablecido antes de iniciar el programa
    mAncho = 3;
    mNumLineas = 0;
}

Principal::~Principal()
{
    delete ui;
    delete mPainter;
    delete mImagen;
}

void Principal::paintEvent(QPaintEvent *event)
{
    // Creamos el painter de la ventana principal
    QPainter painter(this);
    // Dibujamos la imagen
    //Estableciendo coordenadas (0,0) para tener una pantalla mas precisa
    painter.drawImage(0, 0, *mImagen);
    // Acepatr el evento
    event->accept();
}
//Declaramos el evento en el que se dibuja cuando el mouse es presionado
void Principal::mousePressEvent(QMouseEvent *event)
{
    mPuedeDibujar = true;
    mInicial = event->pos();
    event->accept();
}

void Principal::mouseMoveEvent(QMouseEvent *event)
{

    // Realizamos una validacion con if para verificar si se puede dibujar o no
    if ( !mPuedeDibujar ) {

        event->accept();
        return;
    }
    mFinal = event->pos();
    if(ui->actionLibre->isChecked()==true){
        on_actionLibre_checkableChanged(true);
    }

}

void Principal::mouseReleaseEvent(QMouseEvent *event)
{
    mPuedeDibujar = false;

    // Aceptar el vento
    event->accept();
    if(ui->actionLineas->isChecked()==true){
        on_actionLineas_checkableChanged(true);
    }
    if(ui->actionRect_nculos->isChecked()==true){
        on_actionRect_nculos_checkableChanged(true);
    }
    if(ui->actionCircunferencias->isChecked()==true){
        on_actionCircunferencias_triggered();
    }
}


void Principal::on_actionAncho_triggered()
{
    mAncho = QInputDialog::getInt(this,
                                  "Ancho del pincel",
                                  "Ingrese el ancho del pincel de dibujo",
                                  mAncho,
                                  //Ajestamos los valores maximos para el grosor de la linea
                                  1, 100);
}

void Principal::on_actionSalir_triggered()
{
    this->close();
}

void Principal::on_actionColor_triggered()
{
    mColor = QColorDialog::getColor(mColor,
                                    this,
                                    "Color del pincel");
}

void Principal::on_actionNuevo_triggered()
{
    //E lienzo de la Imagen se debe mandeter en blanco
    mImagen->fill(Qt::white);
    mNumLineas = 0;
    update();
}

void Principal::on_actionGuardar_triggered()
{
    QString nombreArchivo = QFileDialog::getSaveFileName(this,
                                                         "Guardar imagen",
                                                         QString(),
                                                         "Imágenes (*.png)");
    if ( !nombreArchivo.isEmpty() ){
        if (mImagen->save(nombreArchivo))
            QMessageBox::information(this,
                                     "Guardar imagen",
                                     "Archivo almacenado en: " + nombreArchivo);
        else
            QMessageBox::warning(this,
                                 "Guardar imagen",
                                 "No se pudo almacenar la imagen.");
    }
}


void Principal::on_actionCircunferencias_triggered()
{
    QPen pincel;
    pincel.setColor(mColor);
    pincel.setWidth(mAncho);
    // Dibujar una linea
    mPainter->setPen(pincel);
    // Declaramos una funcion para pode dibujar un circulo
    // Y los parameotros dentro del circuo son variables que luego le daran sentido a esta figura

    mPainter->drawEllipse(mInicial.x(),mInicial.y(),mFinal.x()-mInicial.x(),mFinal.y()-mInicial.y());
    update();
}


void Principal::on_actionLineas_checkableChanged(bool checkable)
{
    if(checkable==true){
        QPen pincel;
        pincel.setColor(mColor);
        pincel.setWidth(mAncho);
        // Dibujar una linea
        mPainter->setPen(pincel);
        QLine line(mInicial.x(),mInicial.y(),mFinal.x(),mFinal.y());
        mPainter->drawLine(line);
        update();
    }
}


void Principal::on_actionLibre_checkableChanged(bool checkable)
{
    // Capturar el punto donde se suelta el mouse
    if(checkable==true){
        QPen pincel;
        pincel.setColor(mColor);
        pincel.setWidth(mAncho);
        // Dibujar una linea
        mPainter->setPen(pincel);
        mPainter->drawEllipse(QRect(QPoint(mInicial.x(),mFinal.y()),QSize(5,5)));
       // Crear un pincel y establecer atributos
       // Mostrar el número de líneas en la barra de estado
       ui->statusbar->showMessage("Número de líneas: " + QString::number(++mNumLineas));
       // Actualizar la interfaz
       update();
       // actualizar el punto inicial
       mInicial = mFinal;
    }
}


void Principal::on_actionRect_nculos_checkableChanged(bool checkable)
{
    if(checkable==true){
        QPen pincel;
        pincel.setColor(mColor);
        pincel.setWidth(mAncho);
        // Dibujar una linea
        mPainter->setPen(pincel);
        if(mInicial != mFinal)
        {
            // Dibujamos un rectangulo
            // Y los parameotros dentro del rectangulo son variables que luego le daran sentido a esta figura
            mPainter->drawRect(mInicial.x(),mInicial.y(),mFinal.x()-mInicial.x(),mFinal.y()-mInicial.y());
        }
        update();
    }
}

