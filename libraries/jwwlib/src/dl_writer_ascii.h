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

#ifndef DL_WRITER_ASCII_H
#define DL_WRITER_ASCII_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <fstream>
#include <string>
#include "dl_writer.h"

/**
 * Implements functions defined in DL_Writer for writing low
 *   level DXF constructs to an ASCII format DXF file.
 * 
 * @para fname File name of the file to be created.
 * @para version DXF version. Defaults to VER_2002.
 *
 * @todo What if \c fname is NULL?  Or \c fname can't be opened for
 * another reason?
 */
class DL_WriterA : public DL_Writer {
public:
    DL_WriterA(const char* fname, DL_Codes::version version=VER_2000)
            : DL_Writer(version), m_ofile(fname) {}
    virtual ~DL_WriterA() = default;

	bool openFailed() const;
    void close() const;
    void dxfReal(int gc, double value) const override;
    void dxfInt(int gc, int value) const override;
    void dxfHex(int gc, int value) const override;
    void dxfString(int gc, const char* value) const override;
    void dxfString(int gc, const std::string& value) const override;

	static void strReplace(char* str, char src, char dest);

private:
    /**
     * DXF file to be created.
     */
    mutable std::ofstream m_ofile;

};

#endif

