/****************************************************************************
**
** This file is part of the LibreCAD project, a 2D CAD program
**
** Copyright (C) 2010 R. van Twisk (librecad@rvt.dds.nl)
** Copyright (C) 2001-2003 RibbonSoft. All rights reserved.
**
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software 
** Foundation and appearing in the file gpl-2.0.txt included in the
** packaging of this file.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
** 
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**
** This copyright notice MUST APPEAR in all copies of the script!  
**
**********************************************************************/
#ifndef QG_LINEPARALLELOPTIONS_H
#define QG_LINEPARALLELOPTIONS_H

#include "lc_actionoptionswidgetbase.h"

class RS_ActionInterface;
class RS_ActionDrawLineParallel;

namespace Ui {
    class Ui_LineParallelOptions;
}

class QG_LineParallelOptions : public LC_ActionOptionsWidgetBase{
    Q_OBJECT
public:
    QG_LineParallelOptions(RS2::ActionType actionType);
    ~QG_LineParallelOptions() override;
public slots:
    void languageChange() override;
    void onNumberValueChanged(int number);
    void onDistEditingFinished();
protected:
    void doSetAction(RS_ActionInterface *a, bool update) override;
    void doSaveSettings() override;
    bool checkActionRttiValid(RS2::ActionType actionType) override;
private:
    RS_ActionDrawLineParallel* m_action = nullptr;
	std::unique_ptr<Ui::Ui_LineParallelOptions> ui;
    void setDistanceToActionAndView(QString val);
    void setNumberToActionAndView(int number);
};

#endif // QG_LINEPARALLELOPTIONS_H
