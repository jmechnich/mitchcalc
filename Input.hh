#ifndef INPUT_HH
#define INPUT_HH

#include <QLineEdit>

#include <cmath>

#include "CalcToolTip.hh"

class Input : public QLineEdit
{
  Q_OBJECT

public:
  Input( QWidget* parent)
          :QLineEdit( parent), _op( 0)
        {}

private slots:
  void calc( double d)
        {
          double current = text().toDouble();
          switch( _op)
          {
          case( Qt::Key_Plus):
            current += d;
            if( !std::isnan(current) && !std::isinf(current))
                setText( QString::number( current, 'f', 2));
            _op = 0;
            break;
          case( Qt::Key_Minus):
            current -= d;
            if( !std::isnan(current) && !std::isinf(current))
                setText( QString::number( current, 'f', 2));
            _op = 0;
            break;
          case( Qt::Key_Asterisk):
            current *= d;
            if( !std::isnan(current) && !std::isinf(current))
                setText( QString::number( current, 'f', 2));
            _op = 0;
            break;
          case( Qt::Key_Slash):
            current /=d;
            if( !std::isnan(current) && !std::isinf(current))
                setText( QString::number( current, 'f', 2));
            _op = 0;
          default:
            break;
          }
        }
            
private:
  void keyPressEvent( QKeyEvent* e)
        {
          switch( e->key())
          {
          case( Qt::Key_Plus):
          case( Qt::Key_Minus):
          case( Qt::Key_Asterisk):
          case( Qt::Key_Slash):
          {
            _op = e->key();
            CalcToolTip* tt= new CalcToolTip( e->text(), this);
            connect( tt, SIGNAL( valueEntered( double)),
                     this, SLOT( calc( double)));
            tt->setGeometry( QRect(  mapToGlobal( QPoint( 0, height()+3)),
                                     QSize( width(), height())));
            tt->show();
            e->accept();
            break;
          }
          default:
            QLineEdit::keyPressEvent( e);
            break;
          }
        }

  int _op;
};

#endif
