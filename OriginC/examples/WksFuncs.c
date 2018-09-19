/*------------------------------------------------------------------------------*
 * File Name: WksFuncs.c	 													*
 * Creation: GJL 8/11/03														*
 * Purpose: OriginC Source C file containing FindFunction example.				*
 * Copyright (c) OriginLab Corp.		2003, 2004, 2005, 2006, 2007, 2008		*
 * All Rights Reserved															*
 *------------------------------------------------------------------------------*/

#include <Origin.h>

// Function to add columns to a worksheet  
void AddColumns(Worksheet& wks, int nn)
{
	if( wks )
	{
		for( int ii = 0; ii < nn; ii++ )
		{
			wks.AddCol();
		}
	}
}

