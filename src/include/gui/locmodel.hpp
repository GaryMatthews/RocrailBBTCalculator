

#pragma once

#include <QtCore/QAbstractTableModel>

#include "core/datastructs.hpp"

namespace BBTCalculator
{
    namespace Gui
    {
        class LocModel : public QAbstractTableModel
        {
        public:
            explicit LocModel(Core::LocList& lList, QObject* parent = nullptr);

            int rowCount(const QModelIndex& parent) const override;

            int columnCount(const QModelIndex& parent) const override;

            QVariant data(const QModelIndex& index, int role) const override;

            QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

        private:
            Core::LocList& locList;
        };
    }
}

