/*------------------------------------------------------------------------------*
 * File Name: FindFunctionEx.c 													*
 * Creation: GJL 8/11/03														*
 * Purpose: OriginC Source C file containing FindFunction example.				*
 * Copyright (c) OriginLab Corp.		2003, 2004, 2005, 2006, 2007, 2008		*
 * All Rights Reserved															*
 *------------------------------------------------------------------------------*/

#include <Origin.h>

typedef void (*FUNCTYPE)(Worksheet& wks, int nn); 

void myFunction()
{
	string strPath; // Relative pathing...
	strPath = "..\\Samples\\Origin C Examples\\Programming Guide\\Introduction to Origin C\\WksFuncs.c";

	Function fn = Project.FindFunction("AddColumns", strPath);
	FUNCTYPE pfn = fn;

	// Can be done in one line:
	//FUNCTYPE pfn = Project.FindFunction("AddColumns", strPath);

	if( pfn )
	{
		Worksheet wks;
		wks.Create();
		pfn(wks, 5);
	}
}
