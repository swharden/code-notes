/*------------------------------------------------------------------------------*
 * File Name: VectorsEx.c														*
 * Creation: GJL 3/29/2005														*
 * Purpose: OriginC Source C file containing a vector example.					*
 * Copyright (c) OriginLab Corp.	2005, 2006, 2007, 2008, 2009, 2010			*
 * All Rights Reserved															*
 * 																				*
 * Modification Log:															*
 *------------------------------------------------------------------------------*/

#include <Origin.h>

void NumericVectorEx()
{
	// Declare and populate a numeric vector of doubles
	vector vDoubles = { 0, 0, 0, 3.5, 4.8, 0, -6.2,  8.5, -6.3, 2.2, 0, 0};
	vDoubles.Replace(0, NANUM, MATREPL_TEST_EQUAL); // Replace 0s with NANUMs

	// Dynamically allocate and resize
	int iSize = vDoubles.GetSize();
	printf("vDoubles has %d elements\n", iSize);
	vDoubles.SetSize(iSize + 2); // Increase size by 2 elements
	vDoubles[iSize] = 11;
	vDoubles[++iSize] = NANUM;
	iSize = vDoubles.GetSize(); // GetSize
	printf("vDoubles has %d elements\n", iSize);

	// Remove missing values (NANUMs)
	vDoubles.TrimLeft(TRUE); // Remove from beginning
	iSize = vDoubles.GetSize();
	printf("vDoubles has %d elements\n", iSize);
	vDoubles.TrimRight(TRUE); // Remove from from end
	iSize = vDoubles.GetSize();
	printf("vDoubles has %d elements\n", iSize);
	vDoubles.Trim(); // Remove from everywhere
	iSize = vDoubles.GetSize();
	printf("vDoubles has %d elements\n", iSize);

	// Compute sum and get min and max values
	vDoubles *= 2; // Multiply vector by constant
	vDoubles = vDoubles + 3; // Add constant to vector
	double dSum, dMin, dMax;
	vDoubles.Sum(dSum); // Compute sum of vector elements
	vDoubles.GetMinMax(dMin, dMax); // Compute minimum and maximum

	// Sort all elements
	vDoubles.Sort();
	ASSERT(vDoubles[0] == dMin);
	ASSERT(vDoubles[iSize - 1] == dMax);
}		