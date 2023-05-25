#ifndef DESEASETREEITEM_H
#define DESEASETREEITEM_H

#include <QString>
#include <QList>


class DeseaseItem{
public:
    DeseaseItem(const QString label, bool isSymptom = false);

    QString data;
    bool isSymptom;


};

class TreeItem
{
public:
    explicit TreeItem(const DeseaseItem &data, TreeItem *parentItem = nullptr);
    ~TreeItem();

    void appendChild(TreeItem *child);

    TreeItem *child(int row);
    QList<TreeItem*> children();
    int childCount() const;
    DeseaseItem data() const;
    int row() const;
    TreeItem *parentItem();

private:
    QList<TreeItem*> m_childItems;
    DeseaseItem m_itemData;
    TreeItem *m_parentItem = nullptr;
};



#endif // DESEASETREEITEM_H
