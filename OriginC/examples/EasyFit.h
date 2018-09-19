/*------------------------------------------------------------------------------*
 * File Name: EasyFit.h		 													*
 * Creation: GJL 7/17/03														*
 * Purpose: OriginC header file containing implementation of EasyFit class.		*
 * Copyright (c) OriginLab Corp.	2003, 2004, 2005, 2006, 2007				*
 * All Rights Reserved															*
 *------------------------------------------------------------------------------*/

#ifndef _EASY_FIT_H
#define _EASY_FIT_H

class EasyFit
{
	public:
		EasyFit() {}
		EasyFit(DataRange& drOriginal) {m_drInput = drOriginal;}
		EasyFit(DataRange & drX, DataRange& drY) 
		{
			m_drInput.Merge(drX); 
			m_drInput.Merge(drY);
		}
		
		EasyFit(Worksheet& wks, int nColX, int nColY) 
		{
			m_drInput.Add("X", wks, 0, nColX, -1, nColX); 
			m_drInput.Add("Y", wks, 0, nColY, -1, nColY);
		}
		
		EasyFit(Worksheet& wks, int nColY) 
		{
			m_drInput.Add("X", wks, 0, 0, -1, 0); 
			m_drInput.Add("Y", wks, 0, nColY, -1, nColY);
		}
		
		EasyFit(DataPlot& dp) 
		{
			DataRange drTemp; 
			dp.GetDataRange(drTemp); 
		}

		// Destructor
		~EasyFit()
		{
			
		}

		// Methods
		virtual BOOL InitData(DataRange& dr){return  FALSE;}
		
		virtual BOOL PlotCurves(){return FALSE;}
		
		BOOL OutputResults();

	protected:
		// Virtual Methods
		virtual BOOL InitFitOptions(){ return FALSE;}
		virtual BOOL Fit() {return FALSE;}

		// Protected Data Members
		DataRange m_drInput;
		DataRange m_drOutput;
		
		Tree	  m_trResult;

};

// Output settings and result parameters
BOOL EasyFit::OutputResults()
{	
	out_tree(m_trResult);
	return FALSE;
}

#endif // _EASY_FIT_H