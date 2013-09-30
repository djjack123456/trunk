//##########################################################################
//#                                                                        #
//#                            CLOUDCOMPARE                                #
//#                                                                        #
//#  This program is free software; you can redistribute it and/or modify  #
//#  it under the terms of the GNU General Public License as published by  #
//#  the Free Software Foundation; version 2 of the License.               #
//#                                                                        #
//#  This program is distributed in the hope that it will be useful,       #
//#  but WITHOUT ANY WARRANTY; without even the implied warranty of        #
//#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         #
//#  GNU General Public License for more details.                          #
//#                                                                        #
//#          COPYRIGHT: EDF R&D / TELECOM ParisTech (ENST-TSI)             #
//#                                                                        #
//##########################################################################

#include "ccArrow.h"

#include "ccCylinder.h"
#include "ccCone.h"

ccArrow::ccArrow(const PointCoordinateType scale,
                 const ccGLMatrix *transmat /*= 0*/,
                 QString name/*=QString("Arrow")*/,
                 unsigned precision/*=12*/)
    : ccGenericPrimitive(name, transmat), m_scale(scale)

{
    setDrawingPrecision(std::max<unsigned>(precision,4));
}

ccArrow::ccArrow(QString name/* = QString("Arrow")*/)
    : ccGenericPrimitive(name), m_scale(1.0)
{

}

bool ccArrow::buildUp()
{
    ccGLMatrix shaft_mat;
    //the shaft
    shaft_mat.setTranslation( CCVector3 (0, 0, -0.2*m_scale));
    *this += ccCylinder(0.15f*m_scale, 0.6f*m_scale, &shaft_mat, "ArrowShaft", m_drawPrecision);

    ccGLMatrix head_mat;
    //now the head
    head_mat.setTranslation(CCVector3 (0, 0, 0.3*m_scale));
    *this += ccCone(0.3f*m_scale,0.0f,0.4f*m_scale,0,0, &head_mat,"ArrowHead",m_drawPrecision);

    return true;
}

 ccGenericPrimitive* ccArrow::clone() const
 {
     return finishCloneJob(new ccArrow(m_scale,&m_transformation,getName()));
 }






