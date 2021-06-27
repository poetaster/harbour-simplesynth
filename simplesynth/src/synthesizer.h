#ifndef SYNTHESIZER_H
#define SYNTHESIZER_H

#include <QObject>
#include <QString>
#include <QtQml>
#include <qqml.h>

class Synthesizer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString voiceDesc READ getVoiceDesc WRITE setVoiceDesc NOTIFY voiceDescChanged)
/*QML_ELEMENT*/
    ;
public:
    explicit Synthesizer(QObject* parent = 0);
    //explicit Synthesizer(QObject *parent = nullptr);

    QString getVoiceDesc();
    void setVoiceDesc(const QString &voiceDesc);
    void makeAsound();

signals:
    void voiceDescChanged();

private:
    QString m_voiceDesc;
};

#endif // SYNTHESIZER_H
