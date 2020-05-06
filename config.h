#ifndef CONFIG_H
#define CONFIG_H

#include <QDialog>

namespace Ui {
class Config;
}

class Config : public QDialog
{
    Q_OBJECT

public:
    explicit Config(QString player1, QString player2, QWidget *parent = nullptr);
    ~Config();
    QString whiteNick();
    QString blackNick();

private:
    Ui::Config *ui;
//   void	accept();
};

#endif // CONFIG_H
