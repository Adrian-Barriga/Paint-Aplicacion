#ifndef PAINT_H
#define PAINT_H

#include <QMainWindow>
#include <QImage>
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QDebug>
#include <QInputDialog>
#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class Principal; }
QT_END_NAMESPACE

class Principal : public QMainWindow
{
    Q_OBJECT

public:
    Principal(QWidget *parent = nullptr);
    ~Principal();

//Establecesmo el QMouseEvent el cual nos permite dibujar las diversas figuras mientras se arrastra el mouse
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;


private slots:
    void on_actionAncho_triggered();

    void on_actionSalir_triggered();

    void on_actionColor_triggered();

    void on_actionNuevo_triggered();

    void on_actionGuardar_triggered();

    void on_actionCircunferencias_triggered();

    void on_actionLineas_checkableChanged(bool checkable);

    void on_actionLibre_checkableChanged(bool checkable);

    void on_actionRect_nculos_checkableChanged(bool checkable);

private:
    Ui::Principal *ui;
    QImage *mImagen;        // Establecemos una imagen en blanco sobre la cual empezar a sibujar
    QPainter *mPainter;     // Establecemos el objeto painter
    QPoint mInicial;        // Eventos para dibujar el punto incial de una linea
    QPoint mFinal;          // Eventos para dibujar el punto final de una linea
    QPoint mTempInic;
    QPoint mtempFinal;
    bool mPuedeDibujar;     // Determina si debe o no dibujar
    int mAncho;             // Declaramos el ancho del pincel
    QColor mColor;          // Definimos el color del pincel
    int mNumLineas;         // Variable con el número de lineas
    bool mPuedel;
};
#endif // PAINT_H
