/*------------------------------------------------------------------------------*
 * File Name: GlobalFunctionsEx.c												*
 * Creation: GJL 1/25/05														*
 * Purpose: OriginC Source C file containing GlobalFunctions example.			*
 * Copyright (c) OriginLab Corp.		2003, 2004, 2005, 2006, 2007, 2008		*
 * All Rights Reserved															*
 *------------------------------------------------------------------------------*/
 
#include <Origin.h>
#include <page_utils.h>

void CallGlobalFuncsEx()
{
	Worksheet wks = Project.ActiveLayer();
	
	if( wks.IsValid() )
	{
		DataRange dr;
		dr.Add("X", wks, 0, 0, -1, 0);
		dr.Add("Y", wks, 0, 1, -1, 1);
		
		GraphPage gp;
		gp.Create("Origin");
		GraphLayer gl = gp.Layers();
		plot_data_range(dr, gl, IDM_PLOT_LINE);  //global function
	}
}
