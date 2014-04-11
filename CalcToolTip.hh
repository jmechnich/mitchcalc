#ifndef CALCTOOLTIP_HH
#define CALCTOOLTIP_HH

#include <QLabel>
#include <QKeyEvent>
#include <cmath>

#include <iostream>

class CalcToolTip : public QLabel
{
  Q_OBJECT

public:
  CalcToolTip( const QString& opSymbol, QWidget* parent=0)
          : QLabel( opSymbol + " ", parent, Qt::Popup)
        {
          setAlignment( Qt::AlignRight | Qt::AlignVCenter);
          
          QPalette p = palette();
          p.setColor( QPalette::Background, QColor( 237, 237, 170));
          p.setColor( QPalette::Foreground, QColor( 255,   0,   0));
          setPalette( p);
          
          QFont f( font());
          f.setItalic( true);
          setFont( f);
        }

signals:
  void valueEntered( double);
  
private:
  void keyPressEvent( QKeyEvent* e)
        {
          switch( e->key())
          {
          case( Qt::Key_Escape):
            e->accept();
            close();
            return;
          case( Qt::Key_Return):
          case( Qt::Key_Enter):
          {
            bool ok;
            double ret = text().right(text().length()-2).toDouble( &ok);
            if( ok && !std::isinf( ret) && !std::isnan( ret))
                emit valueEntered( ret);
            e->accept();
            close();
            return;
          }
          case( Qt::Key_Insert):
            setText( text() + "0");
            break;
          case( Qt::Key_End):
            setText( text() + "1");
            break;
          case( Qt::Key_Down):
            setText( text() + "2");
            break;
          case( Qt::Key_PageUp):
            setText( text() + "3");
            break;
          case( Qt::Key_Left):
            setText( text() + "4");
            break;
          case( Qt::Key_Clear):
            setText( text() + "5");
            break;
          case( Qt::Key_Right):
            setText( text() + "6");
            break;
          case( Qt::Key_Home):
            setText( text() + "7");
            break;
          case( Qt::Key_Up):
            setText( text() + "8");
            break;
          case( Qt::Key_PageDown):
            setText( text() + "9");
            break;
          case( Qt::Key_0):
          case( Qt::Key_1):
          case( Qt::Key_2):
          case( Qt::Key_3):
          case( Qt::Key_4):
          case( Qt::Key_5):
          case( Qt::Key_6):
          case( Qt::Key_7):
          case( Qt::Key_8):
          case( Qt::Key_9):
          case( Qt::Key_Comma):
          case( Qt::Key_Period):
            setText( text() + e->text());
            break;
          case( Qt::Key_Backspace):
            if( text().length() > 2)
                setText( text().left( text().length()-1));
            break;
          default:
            e->ignore();
            return;
          }
          e->accept();
        }
};

#endif
