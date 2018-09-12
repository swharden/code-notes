/*------------------------------------------------------------------------------*
 * File Name: EasyLR.h		 													*
 * Creation: GJL 7/17/03														*
 * Purpose: OriginC header file containing implementation of EasyLR class.		*
 * Copyright (c) OriginLab Corp.	2003, 2004, 2005, 2006, 2007				*
 * All Rights Reserved															*
 *------------------------------------------------------------------------------*/

#ifndef _EASY_LR_H
#define _EASY_LR_H

class EasyLR : public EasyFit
{
public:
		// Constructors
		EasyLR():EasyFit() {}
		//EasyLR(Curve& crvOriginal):EasyFit(crvOriginal) {}
		EasyLR(DataRange& drOriginal):EasyFit(drOriginal) {}
		EasyLR(DataRange& drX, DataRange& drY):EasyFit(drX, drY) {}
		EasyLR(Worksheet& wks, int nColX, int nColY):EasyFit(wks, nColX, nColY) {}
		EasyLR(Worksheet& wks, int nColY):EasyFit(wks, nColY) {}
		EasyLR(DataPlot& dp):EasyFit(dp) {}
		
		// Destructor
		~EasyLR() {}

		// Virtual Methods
		virtual BOOL Fit();
		virtual BOOL InitFitOptions();
		virtual BOOL PlotCurves();
		virtual BOOL InitData(DataRange& dr);
		
private:
		LROptions m_sLROptions;
	
};

// Virtual Method
// Initialize fit options before fitting
BOOL EasyLR::InitFitOptions()
{
	// Not force slope to be fixed
	m_sLROptions.FixSlope = false;		
	m_sLROptions.FixSlopeAt = 0;
	
	// Force fit to pass thru zero
	m_sLROptions.FixIntercept = true;	
	m_sLROptions.FixInterceptAt = 0;
	
	m_sLROptions.ErrBarWeight = 0;		// Use error column for wt - use (1/err^2) as wt factor
	m_sLROptions.UseReducedChiSq = 0; 	// Scale parameter errors with reduced chisqr

	m_sLROptions.Confidence = 0.90; 	// Confidence value to be used 
	m_sLROptions.ApparentFit = false;   // Not do apparent fit	
	
	return EasyFit::InitFitOptions();
}

// Virtual Method
// Customize settings, perform fit, and create output curve in hidden worksheet
BOOL EasyLR::Fit()
{	
	vector vX, vY, vWeight;
	
	//Get the InputData
	m_drInput.GetData(&vX, 0);
	m_drInput.GetData(&vY, 1);
	
	//Set the X Weight
	vWeight.SetSize(vX.GetSize());
	vWeight = 1;
	
	//Declear the Result structrue
	FitParameter	sFitParameter[2];
	RegStats		sRegStats;
	RegANOVA		sRegANOVA;
	RegCalcInternal	sRegCalInternal;
	
	//do linear fit
	if(STATS_NO_ERROR == stats_linear_fit(vX, vY, vWeight, m_sLROptions, &sFitParameter, &sRegStats, &sRegANOVA, &sRegCalInternal))
	{
		//get the result line data
		vector vFit;
		double dIntercept = sFitParameter[0].Value, dSlope = sFitParameter[1].Value;
		vFit = vX * dSlope + dIntercept; 
		
		//put the fitting line data to the last 2 columns
		Worksheet wks = Project.ActiveLayer();
		int nNumCols = wks.GetNumCols();
		
		int	nFitXCol = wks.AddCol();
		wks.Columns(nFitXCol).SetType(OKDATAOBJ_DESIGNATION_X);
		int	nFitYCol = wks.AddCol();  

		m_drOutput.Add("X", wks, 0, nFitXCol, -1, nFitXCol);
		m_drOutput.Add("Y", wks, 0, nFitYCol, -1, nFitYCol);
		
		m_drOutput.SetData(&vFit, &vX);
		
		//put the result info to the result tree
		//set parameter tree
		Tree trParameter;
		TreeNode trNode;
		trNode = trParameter.AddNode("Intercept");
		trNode = sFitParameter[0];
		
		trNode = trParameter.AddNode("Slope");		
		trNode = sFitParameter[1];
		
		trNode = m_trResult.AddNode("Parameter");
		trNode.Replace(trParameter, true, true);
		
		trNode = m_trResult.AddNode("RegStats");
		trNode = sRegStats;
		
		trNode = m_trResult.AddNode("RegANOVA");
		trNode = sRegANOVA;
		
		
		trNode = m_trResult.AddNode("RegCalInternal");
		trNode = sRegCalInternal;
		
		return TRUE;
	}
	else
		return FALSE;
	
}

// virtual Methods
// Plot input data and output fit curves in new graph
BOOL EasyLR::PlotCurves()
{
	GraphPage gp;
	gp.Create("Origin"); //create graph page

	if( gp.IsValid() )
	{
		GraphLayer gl;
		gl = gp.Layers(); // get active graph layer
		
		if( gl.IsValid() )
		{
			gl.AddPlot(m_drInput, IDM_PLOT_SCATTER); //plot resource data
			int nFitPlot = gl.AddPlot(m_drOutput, IDM_PLOT_LINE);   //plot output data;
			gl.Rescale(); //refresh the graph
			
			if( nFitPlot >= 0)
			{
				DataPlot dpFit = gl.DataPlots(nFitPlot);
				dpFit.SetColor(SYSCOLOR_RED);
			}
			return TRUE;
		}
	}

	return FALSE;
}

//Use customer datarange to initialize the input DataRange.
BOOL EasyLR::InitData(DataRange& dr)
{
	if(dr)
	{
		m_drInput = dr;
		return	TRUE;
	}
	
	return FALSE;
}	
#endif // _EASY_LR_H	
