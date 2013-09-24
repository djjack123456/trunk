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

//Qt
#include <QSharedPointer>

//Local
#include "ccPointCloud.h"
#include "ccNormalVectors.h"
#include "ccCylinder.h"
#include "ccCone.h"

//static QSharedPointer<ccCylinder> c_arrowShaft(0);
//static QSharedPointer<ccCone> c_arrowHead(0);

ccArrow::ccArrow(QString name/*=QString("Arrow")*/)
    : ccHObject(name)

{    
    memcpy(m_rgbColor,ccColor::blue,sizeof(colorType)*3);
    m_direction = CCVector3(0,0,1);
    m_position = CCVector3(0,0,0);

    m_arrowShaft = ccCylinder(0.15f,0.6f,0,"ArrowShaft",12);
    m_arrowShaft.setVisible(true);

    m_arrowHead = ccCone(0.3f,0.0f,0.4f,0,0,0,"ArrowHead",24);
    m_arrowHead.setVisible(true);

}

void ccArrow::setPosition(const CCVector3 pos)
{
    m_position = pos;
}

void ccArrow::setDirection(const CCVector3 dir)
{
    m_direction = dir;
}

void ccArrow::setScale(const PointCoordinateType sca)
{
    m_scale = sca;
}

ccBBox ccArrow::getMyOwnBB()
{
    ccBBox bb_shaft = m_arrowShaft.getMyOwnBB();
//    m_arrowShaft.getBoundingBox(bb_shaft.minCorner().u, bb_shaft.maxCorner().u);

    ccBBox bb_head = m_arrowHead.getMyOwnBB();
//    m_arrowHead.getBoundingBox(bb_head.minCorner().u, bb_head.maxCorner().u);


    bb_shaft += bb_head;
//    all.setValidity(true);

    return bb_shaft;
}

//! Sets the color
/** \param col RGB color
**/
void ccArrow::setColor(const colorType col[])
{
    memcpy(m_rgbColor,col,sizeof(colorType)*3);



}



void ccArrow::drawMeOnly(CC_DRAW_CONTEXT& context)
{

    CC_DRAW_CONTEXT markerContext = context;
    markerContext._win = 0;

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(m_position.x,m_position.y,m_position.z);
    glScalef(m_scale,m_scale,m_scale);

    //we compute scalar prod between the two vectors
    CCVector3 Z(0.0,0.0,1.0);
    float ps = Z.dot(m_direction);

    if (ps < 1.0)
    {
        CCVector3 axis(1.0,0.0,0.0);
        float angle_deg = 180.0;

        if (ps>-1.0)
        {
            //we deduce angle from scalar prod
            angle_deg = acos(ps)*CC_RAD_TO_DEG;

            //we compute rotation axis with scalar prod
            axis = Z.cross(m_direction);
        }

        glRotatef(angle_deg, axis.x, axis.y, axis.z);
    }




    glTranslatef(0.0f,0.0f,0.3f);
    m_arrowShaft.setTempColor(m_rgbColor);
    m_arrowShaft.draw(markerContext);

    glTranslatef(0.0f,0.0f,0.3f+0.2f);
    m_arrowHead.setTempColor(m_rgbColor);
    m_arrowHead.draw(markerContext);


    glPopMatrix();
}
