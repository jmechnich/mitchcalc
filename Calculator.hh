#ifndef CALCULATOR_HH
#define CALCULATOR_HH

#include <QSettings>
#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include <QValidator>
#include <QGridLayout>

#include "Input.hh"

class Calculator : public QWidget
{
  Q_OBJECT
  
public:
  Calculator()
          :QWidget()
        {
          setWindowTitle( "mitchcalc - Verkaufspreisrechner");
          
          QSettings settings;
          
          QLabel* l1 = new QLabel( "Wareneinsatz", this);
          l1->setAlignment( Qt::AlignHCenter);
          QLabel* l2 = new QLabel( "Betriebskosten", this);
          l2->setAlignment( Qt::AlignHCenter);
          QLabel* l3 = new QLabel( "Gewinn", this);
          l3->setAlignment( Qt::AlignHCenter);
          QLabel* l4 = new QLabel( "Bedienungsgeld", this);
          l4->setAlignment( Qt::AlignHCenter);
          QLabel* l5 = new QLabel( "Mehrwertsteuer", this);
          l5->setAlignment( Qt::AlignHCenter);
          QLabel* l6 = new QLabel( "Bruttoverkaufspreis", this);
          l6->setAlignment( Qt::AlignHCenter);
          
          _input = new Input( this);
          _input->setAlignment( Qt::AlignRight);
          QDoubleValidator* inputValidator =
              new QDoubleValidator( _input);
          inputValidator->setBottom( 0);
          inputValidator->setDecimals( 2);
          _input->setValidator( inputValidator);
          
          _c1 = new QSpinBox( this);
          _c1->setRange( 0, 1000);
          _c1->setSingleStep(1);
          _c1->setSuffix( "%");
          _c1->setValue( settings.value
                         ( "/mitchcalc/percentages/operating_costs").toInt());
          
          _c2 = new QSpinBox( this);
          _c2->setRange( 0, 100);
          _c2->setSingleStep(1);
          _c2->setSuffix( "%");
          _c2->setValue( settings.value
                         ( "/mitchcalc/percentages/profit").toInt());
          
          _c3 = new QSpinBox( this);
          _c3->setRange( 0, 100);
          _c3->setSingleStep(1);
          _c3->setSuffix( "%");
          _c3->setValue( settings.value
                         ( "/mitchcalc/percentages/service_charge").toInt());
          
          _c4 = new QSpinBox( this);
          _c4->setRange( 0, 100);
          _c4->setSingleStep(1);
          _c4->setSuffix( "%");
          _c4->setValue( settings.value
                         ( "/mitchcalc/percentages/vat", 16).toInt());
          
          _output = new QLineEdit( this);
          _output->setAlignment( Qt::AlignRight);
          QDoubleValidator* outputValidator =
              new QDoubleValidator( _output);
          outputValidator->setDecimals( 2);
          connect( _input, SIGNAL( textChanged( const QString&)),
                   this, SLOT( calculate()));
          _output->setValidator( outputValidator);
          QFont outputFont( _output->font());
          outputFont.setBold( true);
          _output->setFont( outputFont);
          _output->setReadOnly( true);
          
          connect( _input, SIGNAL( returnPressed()), this, SLOT( calculate()));
          connect( _input, SIGNAL( returnPressed()),
                   _input, SLOT( selectAll()));

          connect( _c1, SIGNAL( valueChanged( int)), this, SLOT( calculate()));
          connect( _c2, SIGNAL( valueChanged( int)), this, SLOT( calculate()));
          connect( _c3, SIGNAL( valueChanged( int)), this, SLOT( calculate()));
          connect( _c4, SIGNAL( valueChanged( int)), this, SLOT( calculate()));
          
          QGridLayout* layout = new QGridLayout;
          layout->setSpacing( 4);
          
          layout->addWidget(l1, 0, 0);
          layout->addWidget(l2, 0, 1);
          layout->addWidget(l3, 0, 2);
          layout->addWidget(l4, 0, 3);
          layout->addWidget(l5, 0, 4);
          layout->addWidget(l6, 0, 5);
          layout->addWidget(_input, 1, 0);
          layout->addWidget(_c1, 1, 1);
          layout->addWidget(_c2, 1, 2);
          layout->addWidget(_c3, 1, 3);
          layout->addWidget(_c4, 1, 4);
          layout->addWidget(_output, 1, 5);
          this->setLayout( layout);
        }

  ~Calculator()
        {
          QSettings settings;
          settings.setValue
              ( "/mitchcalc/percentages/operating_costs", _c1->value());
          settings.setValue
              ( "/mitchcalc/percentages/profit", _c2->value());
          settings.setValue
              ( "/mitchcalc/percentages/service_charge", _c3->value());
          settings.setValue
              ( "/mitchcalc/percentages/vat", _c4->value());
        }

private slots:
  void calculate()
        {
          _output->setText( QString::number(_input->text().toFloat() *
                                            (1.0 + _c1->value()/100.0) *
                                            (1.0 + _c2->value()/100.0) *
                                            (1.0 + _c3->value()/100.0) *
                                            (1.0 + _c4->value()/100.0),
                                            'f', 2));
        }
          
private:
  Input* _input;
  QLineEdit* _output;
  QSpinBox* _c1;
  QSpinBox* _c2;
  QSpinBox* _c3;
  QSpinBox* _c4;
};

#endif

