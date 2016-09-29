#ifndef ABSTRACTREADER_H
#define ABSTRACTREADER_H


class AbstractReader : public QObject
{
    Q_OBJECT
public:
    explicit AbstractReader(QObject *parent = 0);

signals:

public slots:
};

#endif // ABSTRACTREADER_H
