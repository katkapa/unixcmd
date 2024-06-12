#pragma once

#include <QAbstractTableModel>
#include <QHash>
#include <QThreadPool>
#include <QStringList>

class DirectoryViewModel : public QAbstractTableModel {
    Q_OBJECT

public:
    DirectoryViewModel(QObject *parent = nullptr);
    void setDirectory(const QString &path);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private slots:
    void handleBatch(const QStringList &files, int start, bool finished);

private:
    void fetchFiles(int start, int count) const;

    QString m_path;
    QHash<int, QString> m_fileCache;
    int m_totalFiles;
};


