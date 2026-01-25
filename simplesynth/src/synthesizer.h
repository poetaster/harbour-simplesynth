#ifndef SYNTHESIZER_H
#define SYNTHESIZER_H

#include <QtCore/QObject>

class Synthesizer : public QObject
{
    Q_OBJECT
    //Q_PROPERTY(QString voiceDesc READ)
/*QML_ELEMENT*/
    ;

public:
    explicit Synthesizer(QObject *parent = nullptr);
    ~Synthesizer();
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
