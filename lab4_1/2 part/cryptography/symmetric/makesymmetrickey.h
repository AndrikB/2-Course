#ifndef MAKESYMMETRICKEY_H
#define MAKESYMMETRICKEY_H

#include <QDialog>
#include <QFileDialog>
#include <QTextStream>
#include <openssl/rand.h>
namespace Ui {
class MakeSymmetricKey;
}

class MakeSymmetricKey : public QDialog
{
    Q_OBJECT

public:
    explicit MakeSymmetricKey(QWidget *parent = nullptr);
    ~MakeSymmetricKey() override;

private slots:
    void on_save_to_clicked();

    void changed_size_key_slider();

    void on_exit_clicked();
signals:
    void close_wndw();
private:
    Ui::MakeSymmetricKey *ui;

    void closeEvent(QCloseEvent *event)override;
};

#endif // MAKESYMMETRICKEY_H
