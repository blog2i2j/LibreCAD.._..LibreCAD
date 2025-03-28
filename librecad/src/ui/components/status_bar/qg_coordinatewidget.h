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
#ifndef QG_COORDINATEWIDGET_H
#define QG_COORDINATEWIDGET_H

#include "ui_qg_coordinatewidget.h"
#include "rs_vector.h"
#include "rs.h"
#include "rs_graphicview.h"

class RS_Graphic;

class QG_CoordinateWidget : public QWidget, public Ui::QG_CoordinateWidget{
    Q_OBJECT
public:
    QG_CoordinateWidget(QWidget *parent = 0, const char *name = 0, Qt::WindowFlags fl = {});
    ~QG_CoordinateWidget();
    void clearContent();
    void setGraphic(RS_Graphic * g, RS_GraphicView* gv);
public slots:
    virtual void setCoordinates(const RS_Vector & wcsAbs, const RS_Vector & wcsDelta, bool updateFormat ); // fixme - check why updateFormat is always true
protected slots:
    virtual void languageChange();
    virtual void setCoordinates(double ucsX, double ucsY, double ucsDeltaX, double ucsDeltaY, bool updateFormat );
private:
    RS_Graphic* graphic = nullptr;
    RS_GraphicView *graphicView = nullptr;
    LC_GraphicViewport* viewport = nullptr;
    int prec = 0;
    RS2::LinearFormat format = RS2::Decimal;
    int aprec = 0;
    RS2::AngleFormat aformat = RS2::DegreesDecimal;


    RS_Vector absoluteCoordinates;
    RS_Vector relativeCoordinates;
};

#endif // QG_COORDINATEWIDGET_H
