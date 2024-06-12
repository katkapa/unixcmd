#include "DirectoryWorker.h"
#include <QDirIterator>
#include <QDebug>

DirectoryWorker::DirectoryWorker(const QString &path, int start, int count)
    : m_path(path), m_start(start), m_count(count) {}

void DirectoryWorker::run() {
    QStringList batchFiles;
    QDirIterator it(m_path, QDir::Files, QDirIterator::NoIteratorFlags);
    int index = 0;

    // Пропуск файлов до m_start
    while (index < m_start && it.hasNext()) {
        it.next();
        ++index;
    }

    // Чтение следующих m_count файлов
    while (index < m_start + m_count && it.hasNext()) {
        batchFiles.append(it.next());
        ++index;
    }

    bool finished = !it.hasNext();
    emit batchReady(batchFiles, m_start, finished);
}
