#include "notemodel.h"
#include <QFileInfo>
#include <QIcon>
#include <QPixmap>
#include <QStandardPaths>
#include <QDirIterator>
#include <QDateTime>

NoteModel::NoteModel(QObject *parent)
{
    VoiceNoteDir = QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation) + "/MorningStar" + "/MorningStar_Reliza" + "/VoiceNote";
    TextNoteDir  = QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation) + "/MorningStar" + "/MorningStar_Reliza" + "/TextNote";

    QDirIterator txtFile(TextNoteDir,{"*.txt"});
    while(txtFile.hasNext())
    {
        if(txtFile.next() != "")
        {
            fileData fd;
            fd[NOTETYPE] = txtFile.fileInfo().suffix();
            fd[NOTENAME] = txtFile.fileInfo().baseName();
            fd[CREATEDATE] = txtFile.fileInfo().birthTime().toString();

            filedata.append(fd);
        }

    }

    QDirIterator wavFile(VoiceNoteDir,{"*.wav"});
    while(wavFile.hasNext())
    {
        if(wavFile.next() != "")
        {
            fileData fd;
            fd[NOTETYPE] = wavFile.fileInfo().suffix();
            fd[NOTENAME] = wavFile.fileInfo().baseName();
            fd[CREATEDATE] = wavFile.fileInfo().birthTime().toString();

            filedata.append(fd);
        }

    }

}

int NoteModel::rowCount(const QModelIndex &parent) const   {   return filedata.size();    }

int NoteModel::columnCount(const QModelIndex &parent) const    {   return LAST;    }

QVariant NoteModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || filedata.size() <= index.row() || role != Qt::DisplayRole)
        return QVariant();


    return filedata[index.row()][Column(index.column())];
}

QString NoteModel::noteType(const QModelIndex &index) const   {   return filedata[index.row()][NOTETYPE].toString();  }

QString NoteModel::noteName(const QModelIndex &index) const   {   return filedata[index.row()][NOTENAME].toString();  }

QString NoteModel::noteDate(const QModelIndex &index) const   {   return filedata[index.row()][CREATEDATE].toString();  }

void NoteModel::appendData(QFile &file)
{
    QFileInfo fileinfo(file);

    fileData fd;
    fd[NOTETYPE] = fileinfo.suffix();
    fd[NOTENAME] = fileinfo.baseName();
    fd[CREATEDATE] = fileinfo.birthTime().toString();

    int row = filedata.count();                     // Получение количество элементов в списке
    beginInsertRows(QModelIndex(),row,row);         // Добавление новых данных
    filedata.append(fd);
    endInsertRows();
}

void NoteModel::removeData(int row)
{
    if(!filedata.isEmpty())
    {
        beginRemoveRows(QModelIndex(), row, row);
        if(filedata[row][NOTETYPE] == "txt")
            QFile::remove(TextNoteDir + "/" + (filedata[row][NOTENAME]).toString() + "." + (filedata[row][NOTETYPE]).toString());
        if(filedata[row][NOTETYPE] == "wav")
            QFile::remove(VoiceNoteDir + "/" + (filedata[row][NOTENAME]).toString() + "." + (filedata[row][NOTETYPE]).toString());
        filedata.removeAt(row);
        endRemoveRows();
    }
}

QVariant NoteModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();
    if(orientation == Qt::Vertical)
        return QVariant();

    switch(section)
    {
        case NOTETYPE:
            return trUtf8("Тип");
        case NOTENAME:
            return trUtf8("Имя заметки");
        case CREATEDATE:
            return trUtf8("Дата создания");
    }

    return QVariant();
}

Qt::ItemFlags NoteModel::flags(const QModelIndex &index) const {   return QAbstractTableModel::flags(index);   }

NoteModel::~NoteModel() {}
