
#pragma once

#include <QSortFilterProxyModel>

namespace BBTCalculator
{
    namespace Gui
    {
        class ImageSortFilterProxyModel : public QSortFilterProxyModel
        {
        public:
           explicit ImageSortFilterProxyModel(QObject* parent = nullptr);

        protected:

            bool lessThan(const QModelIndex& source_left, const QModelIndex& source_right) const override;
        };

    } // end namespace Gui

} // end namespace BBTCalculator
