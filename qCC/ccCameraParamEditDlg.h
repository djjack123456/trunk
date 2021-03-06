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

#ifndef CC_CAMERA_PARAM_EDIT_DLG_HEADER
#define CC_CAMERA_PARAM_EDIT_DLG_HEADER

//Local
#include "ccOverlayDialog.h"
#include "ccGLWindow.h"

#include <ui_cameraParamDlg.h>

//qCC_db
#include <ccGLMatrix.h>

//system
#include <map>

class QMdiSubWindow;
class ccGLWindow;

//! Dialog to interactively edit the camera pose parameters
class ccCameraParamEditDlg : public ccOverlayDialog, public Ui::CameraParamDlg
{
	Q_OBJECT

public:

	//! Default constructor
	ccCameraParamEditDlg(QWidget* parent);

	//! Destructor
	virtual ~ccCameraParamEditDlg();

	//! Makes this dialog frameless
	void makeFrameless();

	//! Returns matrix corresponding to dialog values
	ccGLMatrixd getMatrix();

	//inherited from ccOverlayDialog
	virtual bool start();
	virtual bool linkWith(ccGLWindow* win);

	public slots:

		//! Links this dialog with a given sub-window
		void linkWith(QMdiSubWindow* qWin);

		//! Inits dialog values with matrix
		void initWithMatrix(const ccGLMatrixd& mat);

		//! Updates dialog values with pivot point
		void updatePivotPoint(const CCVector3d& P);

		//! Updates dialog values with camera center
		void updateCameraCenter(const CCVector3d& P);

		//! Updates current view mode
		void updateViewMode();

		void setFrontView();
		void setBottomView();
		void setTopView();
		void setBackView();
		void setLeftView();
		void setRightView();
		void setIso1View();
		void setIso2View();

		void iThetaValueChanged(int);
		void iPsiValueChanged(int);
		void iPhiValueChanged(int);

		void dThetaValueChanged(double);
		void dPsiValueChanged(double);
		void dPhiValueChanged(double);

		void pivotChanged();
		void cameraCenterChanged();
		void fovChanged(double);

		void pickPointAsPivot();
		void processPickedPoint(int, unsigned, int, int);

protected slots:

	//! Reflects any dialog parameter change
	void reflectParamChange();

	//! Places the camera in a given prefedined orientation
	void setView(CC_VIEW_ORIENTATION orientation);

	//! Pushes current matrix
	void pushCurrentMatrix();

	//! Reverts to pushed matrix
	void revertToPushedMatrix();

protected:

	//! Type of the pushed matrices map structure
	typedef std::map<ccGLWindow*,ccGLMatrixd> PushedMatricesMapType;
	//! Type of an element of the pushed matrices map structure
	typedef std::pair<ccGLWindow*,ccGLMatrixd> PushedMatricesMapElement;

	//! Pushed camera matrices (per window)
	PushedMatricesMapType pushedMatrices;
};

#endif
