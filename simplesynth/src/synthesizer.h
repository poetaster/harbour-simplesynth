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
    Q_INVOKABLE void setVoiceDesc(const QString &voiceDesc);
    Q_INVOKABLE void makeAsound();
    Q_INVOKABLE void removeGenerator(const QString &voiceDesc);

signals:
    void voiceDescChanged();

private:
    QString m_voiceDesc;
};

#endif // SYNTHESIZER_H
