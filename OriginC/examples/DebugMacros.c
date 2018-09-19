/*------------------------------------------------------------------------------*
 * File Name: DebugMacros.c	 													*
 * Creation: GJL 9/22/03														*
 * Purpose: OriginC Source C file demonstrating debug macros.					*
 * Copyright (c) OriginLab Corp.	2003										*
 * All Rights Reserved															*
 *------------------------------------------------------------------------------*/

#include <Origin.h>

void AssertMacro(int imax = 10)
{
	vector<int> aa(imax);
	vector<int> bb;

	for (int ii = 0; ii < aa.GetSize(); ii++)
		aa[ii] = ii;

	bb = 10 * aa; 
	
//	imax+=1;
	ASSERT(bb.GetSize() == imax);

	for (ii = 0; ii < bb.GetSize(); ii++)
		printf("bb[%d]=%d \n", ii, bb[ii]);
}


#define		DBG_OUT(_text, _value)			out_int(_text, _value);

void DebugStatements()
{
	int ii;
	DBG_OUT("ii at t0 = ", ii)
	ii++;
	DBG_OUT("ii at t1 = ", ii)
	ii++;
	DBG_OUT("ii at t2 = ", ii)
	ii++;
	DBG_OUT("ii at t3 = ", ii)
	printf("Finished running DebugMacros.");
}


