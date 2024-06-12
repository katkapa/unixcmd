#pragma once
#include <QObject>
#include <QRunnable>
#include <QStringList>

class DirectoryWorker : public QObject, public QRunnable {
    Q_OBJECT

public:
    DirectoryWorker(const QString &path, int start, int count);
    void run() override;

signals:
    void batchReady(const QStringList &files, int start, bool finished);

private:
    QString m_path;
    int m_start;
    int m_count;
};

