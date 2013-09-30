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
class QCC_DB_DLL_API ccArrow: public ccGenericPrimitive
#else
class ccArrow : public ccGenericPrimitive
#endif
{
public:    
    //! Constructor
    ccArrow(const PointCoordinateType scale,
            const ccGLMatrix * transmat = 0,
            QString name = QString("Arrow"),
            unsigned precision = 12);


    //! simplified const
    ccArrow(QString name = QString("Arrow"));


    //! Returns class ID
    virtual CC_CLASS_ENUM getClassID() const {return CC_ARROW;}


    //! inherited from ccGenericPrimitive
    virtual QString getTypeName() const { return "Arrow"; }
    virtual bool hasDrawingPrecision() const { return true; }
    virtual ccGenericPrimitive* clone() const ;
    virtual bool buildUp();

protected:
    PointCoordinateType m_scale;

};

#endif //CC_SPHERE_PRIMITIVE_HEADER
