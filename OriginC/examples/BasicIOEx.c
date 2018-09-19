/*------------------------------------------------------------------------------*
 * File Name: BasicIO.C		 													*
 * Creation: GJL 8/7/03															*
 * Purpose: OriginC Source C file containing Basic I/O example.					*
 * Copyright (c) OriginLab Corp.	2003, 2004, 2005, 2006, 2007, 2008			*
 * All Rights Reserved															*
 *------------------------------------------------------------------------------*/

#include <Origin.h>

// Sample function to show different output functions
void BasicIOEx()
{
	int ii = 6;
	out_int("\nint ii = ", ii); // Basic I/O global function
	
	double dd = -3.5;
	out_double("\ndouble dd = ", dd); // Basic I/O global function
	printf("\n");
	
	string str = "This is a test.";
	out_str(str); // Basic I/O global function
	// Options WRITE_SCRIPT_WINDOW, WRITE_STATUS_BAR, WRITE_OUTPUT_LOG, WRITE_MESSAGE_BOX, WRITE_COMPILER_OUTPUT
	str.Write(WRITE_SCRIPT_WINDOW); // string class member function
	str.WriteLine(WRITE_SCRIPT_WINDOW); // string class member function
	
	printf("\nint ii = %d,\tdouble dd = %g,\tstring str = %s\n", ii, dd, str); // Basic I/O global function
	
	complex cc(3.2, -4.9);
	out_complex("\ncomplex cc = ", cc); // Basic I/O global function

	Tree tr;
	tr.Branch1.Node1.nVal = 6;
	tr.Branch1.Node1.ID = 101;
	tr.Branch1.Node1.Enable = 1;
	tr.Branch1.Node1.Show = 0;
	tr.Branch1.Node2.nVal = 7;
	tr.Branch1.Node2.ID = 102;
	tr.Branch1.Node2.Enable = 0;
	tr.Branch2.Node1.nVal = 16;
	tr.Branch2.Node1.ID = 201;
	printf("\nout_tree:\n");
	out_tree(tr); // Basic I/O global function
	printf("\n");
		
	// Options WRITE_SCRIPT_WINDOW, WRITE_STATUS_BAR, WRITE_OUTPUT_LOG, WRITE_MESSAGE_BOX, WRITE_COMPILER_OUTPUT
	out_tree(tr); // Basic I/O global function
}	