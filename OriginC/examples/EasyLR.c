/*------------------------------------------------------------------------------*
 * File Name: EasyLR.c		 													*
 * Creation: GJL 7/17/03														*
 * Purpose: OriginC source file containing example usage of EasyLR class.		*
 * Copyright (c) OriginLab Corp.	2003, 2004, 2005, 2006, 2007				*
 * All Rights Reserved															*
 *------------------------------------------------------------------------------*/

#include <Origin.h>
#include <Stats_Utils.h>
#include "EasyFit.h"
#include "EasyLR.h"
///To run this example, you need to run run.loadoc(originlab\stats_utils.c); in Scrpt Window to load some function bodies first.
// Demonstrate performing an easy linear regression
int DemoEasyLR()  
{
	// Declare EasyLR object named elrDemo
	Worksheet wks = Project.ActiveLayer();
	if( !wks )   
	{
		out_str("Error! Before running please active input data worksheet.");
		return -1;    
	}
	
	int	nXCol = 0;
	int nYCol = 1;  
	EasyLR elrDemo(wks, nXCol, nYCol);

	// Customize fitting options
	elrDemo.InitFitOptions();

	// Perform fit
	elrDemo.Fit();  

	// Plot input and output curves
	elrDemo.PlotCurves();  

	// Output results to Script window
	elrDemo.OutputResults();

	return 0;      
}

// Demonstrate performing an easy linear regression with new and delete operators
int DemoEasyLRwithNew()    
{
	//Customize a DataRange
	Worksheet wks = Project.ActiveLayer();
	if( !wks )
	{
		out_str("Error! Before running please active input data worksheet.");
		return -1;
	}
	
	//Create a new Object
	EasyLR *pelrDemo = new EasyLR;	
	
	DataRange dr;
	dr.Add("X", wks, 0, 0, -1, 0);
	dr.Add("Y", wks, 0, 1, -1, 1);
	
	//set the InputData
	pelrDemo->InitData(dr);
	
	// Perform fit
	pelrDemo->Fit();

	// Plot input and output curves
	pelrDemo->PlotCurves();

	// Output results to Script window
	pelrDemo->OutputResults();
	
	delete pelrDemo;
	return 0;
}