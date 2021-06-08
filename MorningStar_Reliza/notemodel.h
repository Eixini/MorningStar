#ifndef NOTEMODEL_H
#define NOTEMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QModelIndex>
#include <QFile>
#include <QString>

class NoteModel : public QAbstractTableModel
{
    Q_OBJECT

private:

    enum Column
    {
        NOTETYPE = 0,
        NOTENAME,
        CREATEDATE,
        LAST
    };

    QString VoiceNoteDir;
    QString TextNoteDir;

    typedef QHash<Column, QVariant> fileData;
    typedef QList<fileData> Data;

    Data filedata;

public:
    NoteModel(QObject *parent = nullptr);
    ~NoteModel();

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    QString noteType(const QModelIndex &index) const;
    QString noteName(const QModelIndex &index) const;
    QString noteDate(const QModelIndex &index) const;

public slots:

    void appendData(QFile &file);
    void removeData(int row);


};

#endif // NOTEMODEL_H
