%Module (name=pyJR , version = 0)
%Import QtGui/QtGuimod.sip
%Import QtXml/QtXmlmod.sip
%If (Qt_4_2_0 -)

%Include jrTypes.sip
%Include tList.sip
%Include tVector.sip
%Include tRGB.sip

%Include tElement.sip

%Include tVariableNameSpace.sip
%Include tOperator.sip
%Include tVariable.sip 
%Include tVariableNameSpace.sip
%Include tRealOperator.sip
%Include tRealVariable.sip
%Include tVectorOperator.sip
%Include tVectorVariable.sip
%Include tListOperator.sip
%Include tListVariable.sip  

%Include tDot.sip
%Include tPoint.sip
%Include tRelPoint.sip
%Include tRotatedPoint.sip
%Include tProjectedPoint.sip
%Include tOffsetPoint.sip
%Include tAbsBead.sip
%Include tMagnet.sip
%Include tAbsMagnet.sip
%Include tStickyMagnet.sip
%Include tMidPoint.sip

%Include tCurve.sip
%Include tLine.sip
%Include tDotListCurve.sip
%Include tAbstractSpline.sip
%Include tBSpline.sip
%Include tCSpline.sip
%Include tHermiteSpline.sip
%Include tTransformedDotListCurve.sip
%Include tDistortedSpline.sip
%Include tSubCurve.sip
%Include tPolyCurve.sip
%Include tRotatedCurve.sip
%Include tMidCurve.sip
%Include tSumCurve.sip
%Include tOffsetCurve.sip
%Include tSnake.sip
%Include tLineSnake.sip
%Include tCSnake.sip

%Include tSurface.sip
%Include tCLoft.sip
%Include tRuledSurface.sip
%Include tRotatedSurface.sip
%Include tRevolvedSurface.sip
%Include tFunctionSurface.sip
%Include tSubSurface.sip
%Include tKaSeries.sip
%Include tPropSurface.sip
%Include tWageningenBSeries.sip
%Include tPropHubSurface.sip
%Include tDuct19A.sip

%Include tStructuredAbstractGrid.sip
%Include tStructured3DGrid.sip
%Include tStructured3DBlockMeshGrid.sip
%Include tStructured3DTwoSidedGrid.sip
%Include tStructured2DSubGrid.sip
%Include tStructured2DInterpolGrid.sip
%Include tStructured2DSurfaceGrid.sip
%Include tStructured2DGrid.sip
%Include tQuad.sip

%Include tBasicPlane.sip
%Include tPlane.sip
%Include tXPlane.sip
%Include tYPlane.sip
%Include tZPlane.sip

%Include tGroup.sip
%Include tLayer.sip

%Include tModel.sip
%Include tConnectiveModel.sip

%Include tMainForm.sip

%End
