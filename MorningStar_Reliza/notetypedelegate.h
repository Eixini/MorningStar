#ifndef NOTETYPEDELEGATE_H
#define NOTETYPEDELEGATE_H

#include <QStyledItemDelegate>
#include <QObject>

class NoteTypeDelegate : public QStyledItemDelegate
{

    Q_OBJECT

public:

    NoteTypeDelegate(QWidget *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

};

#endif // NOTETYPEDELEGATE_H
