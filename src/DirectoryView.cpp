#include <QItemDelegate>
#include <QHeaderView>

#include "DirectoryView.h"
#include "DirectoryViewModel.h"


DirectoryView::DirectoryView() {
    setModel(new DirectoryViewModel(this));
    verticalHeader()->setVisible(false);
}
