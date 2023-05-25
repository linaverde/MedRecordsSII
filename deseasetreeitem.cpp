#include "deseasetreeitem.h"

TreeItem::TreeItem(const DeseaseItem &data, TreeItem *parent)
    : m_itemData(data), m_parentItem(parent)
{}

TreeItem::~TreeItem()
{
    qDeleteAll(m_childItems);
}

void TreeItem::appendChild(TreeItem *item)
{
    m_childItems.append(item);
}

TreeItem *TreeItem::child(int row)
{
    if (row < 0 || row >= m_childItems.size())
        return nullptr;
    return m_childItems.at(row);
}

int TreeItem::childCount() const
{
    return m_childItems.count();
}

int TreeItem::row() const
{
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
}

QList<TreeItem*> TreeItem::children()
{
    return m_childItems;
}

DeseaseItem TreeItem::data() const
{
    return m_itemData;
}

TreeItem *TreeItem::parentItem()
{
    return m_parentItem;
}

DeseaseItem::DeseaseItem(const QString label, bool isSymptom){
    this->data = label;
    this->isSymptom = isSymptom;
}
