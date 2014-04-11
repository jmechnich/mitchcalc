#include <QApplication>
#include "Calculator.hh"

int main( int argc, char** argv)
{
  QApplication app( argc, argv);
  
  Calculator c;
  c.show();
  
  return app.exec();
}
