#ifndef JOBSMODEL_H
#define JOBSMODEL_H

#include <QAbstractTableModel>

#include "Job.h"


class JobsModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit JobsModel(QObject *parent = 0);
    ~JobsModel();

    std::vector<Job> jobs() const;
    void addJobs(const std::vector<Job>& jobs);

signals:
    void jobsChanged(int count);

private:
    int rowCount(const QModelIndex& parent) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex& parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex& index, int role) const Q_DECL_OVERRIDE;
    //QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
    //Qt::ItemFlags flags(const QModelIndex& index) const Q_DECL_OVERRIDE;
    //bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) Q_DECL_OVERRIDE;

    std::vector<Job>    m_jobs;
};

#endif // JOBSMODEL_H
