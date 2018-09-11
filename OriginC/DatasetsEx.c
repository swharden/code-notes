/*------------------------------------------------------------------------------*
 * File Name: DatasetsEx.c														*
 * Creation: GJL 3/29/2005														*
 * Purpose: OriginC Source C file containing a Dataset example.					*
 * Copyright (c) OriginLab Corp.	2005, 2006, 2007, 2008, 2009, 2010			*
 * All Rights Reserved															*
 * 																				*
 * Modification Log:															*
 *------------------------------------------------------------------------------*/

#include <Origin.h>

// A worksheet with data in first two columns must be active prior to execution
void DatasetEx()
{
	Worksheet wks = Project.ActiveLayer();
	if( wks.IsValid() )
	{
		// Construct Dataset object and attach to dataset...
		Dataset ds(wks, 0); // ...in first column of worksheet
		if( ds.IsValid() ) // If Dataset is valid continue...
		{
			BasicStats bsStatVal; // Result structure for dataset statistics
			int iSize = 10;
			ds.SetSize(iSize); // Set size of dataset
			ds.Data(1, iSize, 1); // Populate Dataset with row numbers
			Data_sum(&ds, &bsStatVal); // Compute dataset statistics
			ASSERT( bsStatVal.min == 1 ); // Verify expected min
			ASSERT( bsStatVal.max == ds.GetSize() ); // Verify expected max

			ds.SetLowerBound(2); // Set lower display range of dataset
			ds.SetUpperBound(7); // Set upper display range of dataset 
			Data_sum(&ds, &bsStatVal); // Compute dataset statistics
			ASSERT( bsStatVal.min == 3 ); // Verify expected min
			ASSERT( bsStatVal.max == 8 ); // Verify expected max

			ds.Detach(); // Detach OC Dataset object ds from Origin dataset
			if( !ds.IsValid() ) // ds should be NOT valid
			{
				ds.Attach(wks, 1); // Re-attach ds to different Origin dataset
				if( ds ) // Dataset ds should again be valid, if so continue...
				{
					iSize*=2;
					ds.SetSize(iSize); // Set size of dataset
					ds.Data(iSize, 1, -1); // Populate second column with 21 - row number
					ds.Sort(); // Sort dataset ascending
					Data_sum(&ds, &bsStatVal); // Compute dataset statistics
					ASSERT( bsStatVal.min == 1 ); // Verify expected min
					ASSERT( bsStatVal.max == ds.GetSize() ); // Verify expected max
				}
			}
		}
	}
}