/*  This file is part of KDevelop

    Copyright 2009 Milian Wolff <mail@milianw.de>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#ifndef PHPDOCS_CONFIG_H
#define PHPDOCS_CONFIG_H

#include <KCModule>

#include "ui_phpdocsconfig.h"

namespace Ui
{
    class PhpDocsConfigUI;
}

class PhpDocsConfig
    : public KCModule
{
  Q_OBJECT

  public:
    explicit PhpDocsConfig(QWidget *parent = 0, const QVariantList &args = QVariantList());
    virtual ~PhpDocsConfig();

  private:
        Ui::PhpDocsConfigUI* m_configWidget;
};

#endif // PHPDOCS_CONFIG_H
