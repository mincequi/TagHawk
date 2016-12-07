#include "JobsModel.h"

#include <QDebug>


JobsModel::JobsModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    //setHorizontalHeaderLabels( { "Job", "Original Value", "New Value", "Confirmed" } );

    m_jobs.push_back( { Job::Type::CategorizeArtist, "alternative", "Metal", true, "Tool" } );
    m_jobs.push_back( { Job::Type::RenameArtist, "Queens Of The Stonage", "Queens of zhe Stonage" } );
}

JobsModel::~JobsModel()
{
}

std::vector<Job> JobsModel::jobs() const
{
    std::vector<Job> jobs;



    return jobs;
}

void JobsModel::addJobs(const std::vector<Job>& jobs)
{
    /*
    for (const auto& job : jobs) {
        QStandardItem* jobItem = new QStandardItem();
        switch (job.type) {
        case Job::Type::CategorizeArtist:
            jobItem->setText("Genrefy " + job.field);
            break;
        case Job::Type::RenameArtist:
            jobItem->setText("Rename Artist");
            break;
        default:
            qDebug() << "Unhandled job type:" << static_cast<int>(job.type);
        }

        QStandardItem* confirmedItem = new QStandardItem();
        confirmedItem->setCheckable(true);
        confirmedItem->setCheckState(Qt::Checked);
        int row = 0;
        appendRow(QList<QStandardItem*> { jobItem, new QStandardItem(job.originalValue.toString()), new QStandardItem(job.newValue.toString()), confirmedItem } );
        row = rowCount()-1;
    }

    this->clear();


    //// 3.1 No genres
    //if (genres.isEmpty()) {
    //    return;
    //}
    //
    //// 3.2 Set first genre
    //item(row, 0)->setText(genres.last());
    //item(row, 0)->setData(ArtistItem, TypeRole);
    //item(row, 0)->setData(QString::number(genres.lastKey()), WeightRole);
    //item(row, 1)->setText(QString::number(genres.lastKey()));
    //item(row, 3)->setCheckable(true);
    //item(row, 3)->setCheckState(genres.lastKey() >= m_config.whitelistWeight ? Qt::Checked : Qt::Unchecked);
    */

    emit jobsChanged(5);
}

int JobsModel::rowCount(const QModelIndex& /*parent*/) const
{
    return m_jobs.size();
}

int JobsModel::columnCount(const QModelIndex& /*parent*/) const
{
    return 4;
}

QVariant JobsModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::DisplayRole) {
        if (index.column() == 0) {
            return m_jobs.at(index.row()).typeAsString();
        } else if (index.column() == 1) {
            return m_jobs.at(index.row()).originalValue;
        } else if (index.column() == 2) {
            return m_jobs.at(index.row()).newValue;
        }
    } else if (role == Qt::CheckStateRole) {
        if (index.column() == 3) {
            return m_jobs.at(index.row()).confirmed ? Qt::Checked : Qt::Unchecked;
        }
    }

    return QVariant();
}
