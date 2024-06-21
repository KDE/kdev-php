/*
    SPDX-FileCopyrightText: 2012 Milian Wolff <mail@milianw.de>

    SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

#ifndef PHPDOCS_CONFIG_H
#define PHPDOCS_CONFIG_H

#include <interfaces/configpage.h>

class PhpDocsPlugin;

namespace Ui
{
    class PhpDocsConfigUI;
}

class PhpDocsConfig
    : public KDevelop::ConfigPage
{
  Q_OBJECT

  public:
    explicit PhpDocsConfig(PhpDocsPlugin* plugin, QWidget *parent = nullptr);
    ~PhpDocsConfig() override;

    KDevelop::ConfigPage::ConfigPageType configPageType() const override;

    QString name() const override;
    QString fullName() const override;
    QIcon icon() const override;

  private:
        Ui::PhpDocsConfigUI* m_configWidget;
};

#endif // PHPDOCS_CONFIG_H
