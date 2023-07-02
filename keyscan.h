#ifndef KEYSCAN_H
#define KEYSCAN_H
#include <QThread>
class keyScan : public QThread
{
    Q_OBJECT
public:
    explicit keyScan(QObject *parent = nullptr);
    virtual ~keyScan();
signals:
    void sig_buttonPressed(unsigned char);
    void sig_keyPressed(unsigned char);
    void sig_keyRelease(unsigned char);
protected:
        void run();
private:
    void registerd();
    void unregister();
};
#endif // KEYSCAN_H
