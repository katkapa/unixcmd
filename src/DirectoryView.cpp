#include <QItemDelegate>
#include <QHeaderView>

#include "DirectoryView.h"

DirectoryView::DirectoryView() {
    m_directoryViewModel = new DirectoryViewModel (this);
    setModel(m_directoryViewModel);
    verticalHeader()->setVisible(false);
    m_directoryViewModel->setDirectory("/Users/ekat/Photos/Кировск2021");

    m_timer.setSingleShot(true);
    m_timer.setInterval(5000); // 5000 миллисекунд = 5 секунд

    connect(
        &m_timer,
        &QTimer::timeout,
        m_directoryViewModel,
        [this]() {m_directoryViewModel->setDirectory("/Users/ekat/Photos/Праздник осени"); }
    );

    m_timer.start();
}
