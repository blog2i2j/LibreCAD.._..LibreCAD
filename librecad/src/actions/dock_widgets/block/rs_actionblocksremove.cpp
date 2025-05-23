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

#include "rs_actionblocksremove.h"

#include "rs_debug.h"
#include "rs_dialogfactory.h"
#include "rs_dialogfactoryinterface.h"
#include "rs_graphic.h"
#include "rs_insert.h"

class RS_BlockList;

RS_ActionBlocksRemove::RS_ActionBlocksRemove(LC_ActionContext *actionContext)
    :RS_ActionInterface("Remove Block", actionContext, RS2::ActionBlocksRemove) {}

void RS_ActionBlocksRemove::trigger() {
    RS_DEBUG->print("RS_ActionBlocksRemove::trigger");

    if (!(m_graphic && m_document)) {
        finish(false);
        return;
    }

    RS_BlockList *blockList = m_graphic->getBlockList();
    QList<RS_Block *> blocks = RS_DIALOGFACTORY->requestSelectedBlocksRemovalDialog(blockList);

    if (blocks.isEmpty()) {
        finish(false);
        return;
    }

    // list of containers that might refer to the block via inserts:
    std::vector<RS_EntityContainer *> containerList;
    containerList.push_back(m_graphic);
    for (int bi = 0; bi < blockList->count(); bi++) {
        containerList.push_back(blockList->at(bi));
    }

    undoCycleStart();

    for (auto block: blocks) {
        if (nullptr == block) {
            continue;
        }
        for (auto cont: containerList) {
        // remove all inserts from the graphic:
            bool done;
            do {
                done = true;
                for (auto e: *cont) {
                    if (e->is(RS2::EntityInsert)) {
                        auto *ins = static_cast<RS_Insert *>(e);
                        if (ins->getName() == block->getName() && !ins->isUndone()) {
                            m_document->addUndoable(ins);
                            ins->setUndoState(true);
                            done = false;
                            break;
                        }
                    }
                }
            } while (!done);
        }

        // clear selection and active state
        block->selectedInBlockList(false);
        if (block == blockList->getActive()) {
            blockList->activate(nullptr);
        }

        // close all windows that are editing this block:
        RS_DIALOGFACTORY->closeEditBlockWindow(block);

        // Now remove block from the block list, but do not delete:
        block->setUndoState(true);
        m_document->addUndoable(block);
    }
    undoCycleEnd();

    m_graphic->addBlockNotification();
    m_graphic->updateInserts();
    redrawDrawing();
    blockList->activate(nullptr);

    finish(false);
    updateSelectionWidget();
}

void RS_ActionBlocksRemove::init(int status) {
    RS_ActionInterface::init(status);
    trigger();
}
