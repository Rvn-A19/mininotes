// Minimal notes application.


#include <QApplication>
#include <QDir>
#include <QFile>
#include <QLabel>
#include <QLayout>
#include <QPlainTextEdit>


static const QString filename = ".mynotes.txt";


int main(int argc, char * argv[]) {
  QApplication app(argc, argv);

  QWidget *widget = new QWidget;

  QVBoxLayout *mainLayout = new QVBoxLayout(widget);
  QLabel *label = new QLabel("Notes text:");
  QPlainTextEdit *textEdit = new QPlainTextEdit(widget);

  mainLayout->addWidget(label);
  mainLayout->addWidget(textEdit);

  widget->setLayout(mainLayout);
  widget->setWindowTitle("Notes");
  widget->setGeometry(40, 60, 640, 480);
  widget->show();

  auto fullpath = qEnvironmentVariable("HOME") + QDir::separator() + filename;

  std::string strText{ "" };
  QFile f{ fullpath };

  if (f.open(QIODevice::ReadOnly)) {
    strText = f.readAll().toStdString();
    textEdit->setPlainText( QString::fromStdString(strText) );
    f.close();
  }

  int returnCode = app.exec();
  auto newText = textEdit->toPlainText().toStdString();
  if ( newText != strText && f.open(QIODevice::ReadWrite) ) {
    if (newText.length() < strText.length()) {
      f.resize(newText.length());
    }
    f.write(newText.c_str());
    f.close();
  }

  delete widget;
  return returnCode;
}
