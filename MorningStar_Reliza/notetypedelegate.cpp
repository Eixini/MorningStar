#include "notetypedelegate.h"
#include <QPixmap>
#include <QPainter>
#include <QAbstractItemView>
#include <QString>
#include <QIcon>
#include <QPoint>

NoteTypeDelegate::NoteTypeDelegate(QWidget *parent) {}

void NoteTypeDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.data().canConvert<QString>())
    {
        QString noteType = qvariant_cast<QString>(index.data());

        QPoint iconRend = option.rect.center();
        iconRend -= QPoint(10,10);

        if (noteType == "txt")
        {
            painter->drawPixmap(iconRend,  QIcon(":/morningstar_resources/icons/clipboard_icon.png").pixmap(QSize(20,20)));

        }
        else if(noteType == "wav")
        {
            painter->drawPixmap(iconRend,  QIcon(":/morningstar_resources/icons/microphone_icon.png").pixmap(QSize(20,20)));
        }
    }
    else
        QStyledItemDelegate::paint(painter, option, index);
}
