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

#ifndef CC_ARROW_PRIMITIVE_HEADER
#define CC_ARROW_PRIMITIVE_HEADER

#include "ccGenericPrimitive.h"

//CCLib
#include <CCGeom.h>
#include <ccCone.h>
#include <ccCylinder.h>
//! Arrow (primitive)
/** 3D arrow primitive
**/
#ifdef QCC_DB_USE_AS_DLL
#include "qCC_db_dll.h"
class QCC_DB_DLL_API ccArrow: public ccHObject
#else
class ccArrow : public ccHObject
#endif
{
public:
	//! Simplified constructor
	/** For ccHObject factory only!
	**/
    ccArrow(QString name = QString("Arrow"));

    //desctructor
    virtual ~ccArrow();

    //! Returns class ID
    virtual CC_CLASS_ENUM getClassID() const {return CC_ARROW;}

    void setPosition(const CCVector3 pos) ;

    void setDirection(const CCVector3 dir) ;

    void setScale(const PointCoordinateType sca) ;

//    virtual ccBBox getBB(bool relative = true, bool withGLfeatures = false, const ccGenericGLDisplay* window = NULL);

    //! Sets the color
    /** \param col RGB color
    **/
    void setColor(const colorType col[]) ;

//    virtual ccBBox getFitBB(ccGLMatrix& trans);
    virtual ccBBox getMyOwnBB();


    void buildPrimitives();

    SelectionBehavior getSelectionBehavior(){return SELECTION_FIT_BBOX;}



protected:

    //inherited methods (ccHObject)
    virtual void drawMeOnly(CC_DRAW_CONTEXT& context);

    CCVector3 m_position;

    CCVector3 m_direction;

    PointCoordinateType m_scale;

    ccCylinder * m_arrowShaft;

    ccCone * m_arrowHead;

    colorType m_color[3];


};

#endif //CC_SPHERE_PRIMITIVE_HEADER
