#include "DirectoryViewModel.h"
#include "DirectoryWorker.h"
#include <QDir>
#include <QDebug>
#include <QThreadPool>
#include <QtCore>


DirectoryViewModel::DirectoryViewModel(QObject *parent)
    : QAbstractTableModel(parent), m_totalFiles(0) {}


int DirectoryViewModel::rowCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : m_totalFiles;
}

int DirectoryViewModel::columnCount(const QModelIndex &parent) const {
    return 2;
}

QVariant DirectoryViewModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    int row = index.row();

    if (m_fileCache.contains(row)) {
        if (index.column() == 0)
            return m_fileCache.value(row);
        else
            return "foo";
    } else {
        if (row >= m_totalFiles)
            return QVariant();

        // Если данных нет в кэше, запускаем загрузку
        fetchFiles(row, 50);
        return "Loading...";
    }
}

void DirectoryViewModel::setDirectory(const QString &path) {
    m_path = path;
    m_fileCache.clear();
    m_totalFiles = 0;
    beginResetModel();
    fetchFiles(0, 50); // Загрузить первые 50 файлов
    endResetModel();
}

void DirectoryViewModel::fetchFiles(int start, int count) const{
   DirectoryWorker *worker = new DirectoryWorker(m_path, start, count);
    connect(worker, &DirectoryWorker::batchReady, this, &DirectoryViewModel::handleBatch);
    QThreadPool::globalInstance()->start(worker);
}

void DirectoryViewModel::handleBatch(const QStringList &files, int start, bool finished) {
    if (files.isEmpty())
        return;

    beginResetModel();
    for (int i = 0; i < files.size(); ++i) {
        m_fileCache[start + i] = QFileInfo(files.at(i)).fileName();
    }
    m_totalFiles = qMax(m_totalFiles, start + files.size());
    endResetModel();

    // Если загрузка завершена, можно установить общее количество файлов
    if (finished) {
        m_totalFiles = start + files.size();
        beginResetModel();
        endResetModel();
    }
}
