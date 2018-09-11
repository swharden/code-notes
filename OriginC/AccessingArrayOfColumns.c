/*------------------------------------------------------------------------------*
 * File Name:				 													*
 * Creation: 																	*
 * Purpose: OriginC Source C file												*
 * Copyright (c) ABCD Corp.	2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010		*
 * All Rights Reserved															*
 * 																				*
 * Modification Log:															*
 *------------------------------------------------------------------------------*/
 
////////////////////////////////////////////////////////////////////////////////////
// Including the system header file Origin.h should be sufficient for most Origin
// applications and is recommended. Origin.h includes many of the most common system
// header files and is automatically pre-compiled when Origin runs the first time.
// Programs including Origin.h subsequently compile much more quickly as long as
// the size and number of other included header files is minimized. All NAG header
// files are now included in Origin.h and no longer need be separately included.
//
// Right-click on the line below and select 'Open "Origin.h"' to open the Origin.h
// system header file.
#include <Origin.h>
////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////
// Include your own header files here.


////////////////////////////////////////////////////////////////////////////////////
// Start your functions here.
void AccessingArrayOfColumns()
{
	Worksheet wks = Project.ActiveLayer();//Get the active worksheet layer
	if( !wks )//if not valid, stop here
		return;
	
	uint nCols = wks.Columns.Count();//Get the number of columns in wks
	nCols = nCols > 10 ? 10 : nCols; //Maximum number of columns is 10
	Column arrCols[10];
	for( int ii = 0; ii < nCols; ii++ )
	{
		arrCols[ii].Attach( wks, ii );
		if( !arrCols[ii].IsValid() ) //if not valid, go on with next column
			continue;
		string	strColName = arrCols[ii].GetName();
		int		nLowerBound  = arrCols[ii].GetLowerBound();
		int		nUpperBound  = arrCols[ii].GetUpperBound();
		printf("Column %s's data size is : %d\n", strColName, nUpperBound - nLowerBound + 1);
	}
	return;
}