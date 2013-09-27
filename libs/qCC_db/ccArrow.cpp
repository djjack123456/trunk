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

#include <iostream> //for debug



ccArrow::ccArrow(QString name/*=QString("Arrow")*/)
    : ccHObject(name), m_scale(1.0)

{    
    m_direction = CCVector3(0,0,1);
    m_position = CCVector3(0,0,0);


    memcpy(m_color,ccColor::black,3*sizeof(colorType));

    buildPrimitives();
}


void ccArrow::buildPrimitives()
{

    m_arrowShaft = new ccCylinder(0.15f * m_scale,0.6f * m_scale,0,"ArrowShaft",12);
    m_arrowShaft->enableGLTransformation(true);
    CCVector3 trans_shaft (0,0,-0.2*m_scale);
    m_arrowShaft->translateGL(trans_shaft);
    m_arrowShaft->setColor(m_color); //def color
    m_arrowShaft->setVisible(true);


    m_arrowHead = new ccCone(0.3f*m_scale,0.0f,0.4f*m_scale,0,0,0,"ArrowHead",24);
    m_arrowHead->enableGLTransformation(true);
    CCVector3 trans_head (0,0,0.3*m_scale);
    m_arrowHead->translateGL(trans_head);
    m_arrowHead->setColor(m_color);
    m_arrowHead->setVisible(true);
}

ccArrow::~ccArrow()
{
    delete m_arrowHead;
    delete m_arrowShaft;
}

void ccArrow::setPosition(const CCVector3 pos)
{
    enableGLTransformation(true);
    m_position = pos;
    m_glTrans.setTranslation(pos);
}

void ccArrow::setDirection(const CCVector3 dir)
{
    enableGLTransformation(true);
    m_direction = dir;
    ccGLMatrix mat = ccGLMatrix::FromToRotation(m_direction, CCVector3(0,0,1));

    m_glTrans *= mat;
}

void ccArrow::setScale(const PointCoordinateType sca)
{
    m_scale = sca;
    buildPrimitives(); //force to rebuild the primitives with this scale
}



ccBBox ccArrow::getMyOwnBB()
{
    CCVector3 mincorner(-0.3*m_scale,-0.3*m_scale,-0.5*m_scale);
    CCVector3 maxcorner(0.3*m_scale, 0.3*m_scale, 0.5*m_scale);

    ccBBox box(mincorner, maxcorner);
    return box;
}




void ccArrow::setColor(const colorType col[])
{    
    m_arrowHead->setColor(col);
    m_arrowShaft->setColor(col);
}



void ccArrow::drawMeOnly(CC_DRAW_CONTEXT& context)
{


    CCVector3 minc = getBB(false).minCorner();
    std::cout << "min corner" << std::endl;
    std::cout << minc.x << " " << minc.y << " " << minc.z << std::endl;

    CCVector3 maxc = getBB(false).maxCorner();
    std::cout << "max corner" << std::endl;
    std::cout << maxc.x << " " << maxc.y << " " << maxc.z << std::endl;


    //Box dimensions
    CCVector3 bboxDiag = getMyOwnBB().getDiagVec();
    std::cout << "digonal" << std::endl;
    std::cout << bboxDiag.x << " " << bboxDiag.y << " " << bboxDiag.z << std::endl;

    //Box center
    CCVector3 bboxCenter = getMyOwnBB().getCenter();
    std::cout << "center" << std::endl;
    std::cout << bboxCenter.x << " " << bboxCenter.y << " " << bboxCenter.z << std::endl;




    CC_DRAW_CONTEXT markerContext = context;
    markerContext._win = 0;
    //    setScale(markerContext.pickedPointsRadius*10);
    buildPrimitives();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    m_arrowShaft->draw(markerContext);
    m_arrowHead->draw(markerContext);

    glPopMatrix();
}
