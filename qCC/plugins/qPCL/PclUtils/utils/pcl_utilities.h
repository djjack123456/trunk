//##########################################################################
//#                                                                        #
//#                       CLOUDCOMPARE PLUGIN: qPCL                        #
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
//#                        COPYRIGHT: Luca Penasa                          #
//#                                                                        #
//##########################################################################
//
#ifndef PCL_UTILITIES_H
#define PCL_UTILITIES_H

#ifndef LP_PCL_ON_TRUNK
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/PointField.h>
#else

#include <pcl/PCLPointCloud2.h>
#include <pcl/PCLPointField.h>
namespace sensor_msgs
{
typedef pcl::PCLPointCloud2 PointCloud2;
typedef pcl::PCLPointCloud2ConstPtr PointCloud2ConstPtr;
typedef pcl::PCLPointCloud2Ptr PointCloud2Ptr;
typedef pcl::PCLPointField PointField;
}


#endif



//Qt
#include <QString>

sensor_msgs::PointCloud2 mergeVectorOfClouds(std::vector<sensor_msgs::PointCloud2> &clouds);

//! Utility function that loads a given PCD file in a sensor_msgs PointCloud2
/** \param[in] filename
	\return a shared pointer to a sensor_msgs cloud
**/
sensor_msgs::PointCloud2::Ptr loadSensorMessage(const QString &filename);

#endif // PCL_UTILITIES_H
