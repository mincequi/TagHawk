#include "SettingsDialog.h"
#include "ui_SettingsDialog.h"

#include "config/Config.h"


SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_buttonBox_accepted()
{
    config::Genres  genres = Config::instance().genres();
    genres.maximumGenreCount = ui->maxGenreCountSpinBox->value();
    genres.minimumGenreWeight = ui->minGenreWeightSpinBox->value();
    genres.whitelistWeight = ui->whitelistWeightSpinBox->value();
    Config::instance().setGenres(genres);

    config::Tags    tags;
    tags.stripId3v1 = ui->stripId3v1Checkbox->isChecked();
    Config::instance().setTags(tags);
}

void SettingsDialog::showEvent(QShowEvent* event)
{
    config::Genres genres = Config::instance().genres();
    ui->maxGenreCountSpinBox->setValue(genres.maximumGenreCount);
    ui->minGenreWeightSpinBox->setValue(genres.minimumGenreWeight);
    ui->whitelistWeightSpinBox->setValue(genres.whitelistWeight);

    QDialog::showEvent(event);
}
