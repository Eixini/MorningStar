#include "notetypedelegate.h"
#include <QPixmap>
#include <QPainter>
#include <QAbstractItemView>
#include <QString>

NoteTypeDelegate::NoteTypeDelegate(QWidget *parent) {}

void NoteTypeDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.data().canConvert<QString>())
    {
        QString noteType = qvariant_cast<QString>(index.data());

        if (noteType == "txt")
        {
            painter->drawPixmap(option.rect,  QPixmap(":/morningstar_resources/icons/clipboard_icon.png"));

        }
        if(noteType == "wav")
        {
            painter->drawPixmap(option.rect,  QPixmap(":/morningstar_resources/icons/microphone_icon.png"));
        }
    }
    QStyledItemDelegate::paint(painter, option, index);
}
