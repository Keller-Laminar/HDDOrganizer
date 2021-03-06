/*  Copyright 2013 Matthew Keller

    This file is part of HDDOrganizer.

    HDDOrganizer is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    HDDOrganizer is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with HDDOrganizer.  If not, see <http://www.gnu.org/licenses/>.
*/

// This class is a model that lives within the Drive model.
// It extends the more general AbstractItemModel which allows for trees.

#ifndef TAGTREEMODEL_H
#define TAGTREEMODEL_H

#include <QAbstractItemModel>
#include "QFileInfo.h"

class Tag;
class QDomDocument;
class QDomElement;

class TagTreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:

    explicit TagTreeModel(QString name, QObject *parent = 0);
    ~TagTreeModel();

    // Inherited pure virtual function. This function returns the
    // QModelIndex for a given row column and parent.
    QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const;

    // This function returns the number of tags under the specified parent.
    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    // Returns 2.
    int columnCount(const QModelIndex & parent = QModelIndex()) const;

    // Returns the parent of the specified child.
    QModelIndex parent(const QModelIndex & child) const;

    // Inherited pure virtual function. Returns the data associated with
    // the given QModelIndex and Role.
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    // Allows for the possibility of an editable tag.
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole);

    // Returns the names of the columns.
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    // Defines the interaction for the particular QModelIndex.
    Qt::ItemFlags TagTreeModel::flags(const QModelIndex &index) const;

    // Adds a tag of the given name to the specified parent.
    // If no parent is specified, it is added to the root.
    bool insertTag(const QString tagName, const QModelIndex& parent = QModelIndex());

    // Adds a tag of the given name to the specified parent.
    // If no parent is specified, it is added to the root.
    bool deleteTag(const QModelIndex& tag);

    // Returns a tag pointer given its QModelIndex.
    Tag* getIndexTag(const QModelIndex& index) const;

    // Inherited function.
    // Defines the response to having data dropped in the associated view.
    bool dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column, const QModelIndex& parent);

    // represents the DOM tree as a string.
    QString stringify() const;

    // reads content into the DOM tree from a file.
    bool setContent(QIODevice * dev);

    // recursively creates the tag tree from a full DOM tree.
    void translate(QDomElement *domNode, Tag *tagNode);

    QMimeData *mimeData(const QModelIndexList &indexes) const;

    // Translates a list of QModelIndicies into Tag*s
    QList<Tag *> getTagList(QModelIndexList indicies);
private:
    Tag* root_;
    QDomDocument* domTree_;
    QDomElement* domTreeRoot_;

signals:
    
public slots:

    
};

#endif // TAGTREEMODEL_H
