/*------------------------------------------------------------------------------*
 * File Name: StringsEx.c	 													*
 * Creation: GJL 3/24/2005														*
 * Purpose: OriginC Source C file contaning strings example.					*
 * Copyright (c) OriginLab Corp.	2005, 2006, 2007, 2008, 2009, 2010			*
 * All Rights Reserved															*
 * 																				*
 * Modification Log:															*
 *------------------------------------------------------------------------------*/

#include <Origin.h>

/**
	Parse a workbook selection string and if successful print the workbook name,
	sheet name, and column and row selection indices (0 based offsets, as
	integers). The default argument for this example function assumes that columns
	named A and B exist in a worksheet named Data1 in a workbook named Book1.
*/
BOOL ParseSelectionStringEx(string strWksSelection = "  [Book1]Data1!$A$1:$B$7 ")
{
	string strBookName, strSheetName, str, strCol, strRow;
	int iC1, iC2, iR1, iR2, ii;

	WorksheetPage wpBook; // Workbbook and Worksheet objects 
	Worksheet wksSheet;

	strBookName.Empty(); // Initialize strings (not necessary but possible)
	strSheetName.Empty();

	iC1=iC2=iR1=iR2=-1; // Initialize indices

	// Trim white space if any on ends: strWksSelection=="  [Book1]Data1!$A$1:$B$7 "
	str = strWksSelection; // Work with str
	str.TrimLeft();
	str.TrimRight();

	// str=="[Book1]Data1!$A$1:$B$7"
	str = str.Mid(1); // Strip off [ character

	// str=="Book1]Data1!$A$1:$B$7"
	ii = str.Find(']'); // Find ] character
	if( ii < 0 ) // If no ] return error
		return FALSE;
	strBookName = str.Left(ii); // Get workbook name
	wpBook = Project.Pages(strBookName);// Attach to workbook 
	if( !wpBook.IsValid() ) // If workbook not valid return error
		return FALSE;
	str = str.Mid(ii + 1); // Strip off workbook name and ] character

	// str=="Data1!$A$1:$B$7"
	ii = str.Find('!'); // Find ! character
	if( ii < 0 ) // If no ! return error
		return FALSE;
	strSheetName = str.Left(ii); // Get sheet name from input string
	wksSheet = (Worksheet) wpBook.Layers(strSheetName); // Get internal workbook sheet object by name
	if( !wksSheet.IsValid() ) // If worksheet not valid return error
		return FALSE;
	str = str.Mid(ii + 1); // Strip off sheet name and ! character

	// str=="$A$1:$B$7"
	ii = str.Find('$'); // Find first $ character
	if( ii != 0 ) // If $ is not next character return error
		return FALSE;		
	str = str.Mid(ii + 1); // Strip off first $ character

	// str=="A$1:$B$7"
	ii = str.Find('$'); // Find second $ character
	if( ii < 0 )                     // If no $ return error
		return FALSE;
	strCol = str.Left(ii); // Get name of first column
	if( !wksSheet.Columns(strCol).IsValid() ) // If first selected column is not valid return error  
		return FALSE;
	iC1 = wksSheet.Columns(strCol).GetIndex(); // Get column number of first selected column
	if( iC1 < 0 ) // If column not valid return error
		return FALSE;
	str = str.Mid(ii + 1); // Strip off name of first column and second $ character

	// str=="1:$B$7"
	ii = str.Find(':'); // Find : character
	if( ii < 0 ) // If no : return error
		return FALSE;
	strRow = str.Left(ii); // Get first row number (as string)
	iR1 = atoi(strRow) - 1; // Get first row number (as integer, subtract 1 for 0 based offset)
	strRow.Format("%d", iR1 + 1); // Rebuild strRow (as string from integer) for check
	if( strRow.Compare(str.Left(ii)) ) // If not same return error 
		return FALSE;
	str = str.Mid(ii + 1); // Strip off first row number and : character

	// str=="$B$7"
	ii = str.Find('$'); // Find third $ character		
	if( ii != 0 ) // If $ is not next character return error
		return FALSE;
	str = str.Mid(ii + 1); // Strip off third $ character

	// str=="B$7"
	ii = str.Find('$'); // Find fourth $ character
	if( ii < 0 ) // If no $ return error
		return FALSE;
	strCol = str.Left(ii); // Get name of second column
	if( !wksSheet.Columns(strCol).IsValid() ) // If second selected column is not valid return error
		return FALSE;
	iC2 = wksSheet.Columns(strCol).GetIndex(); // Get column number of second selected column
	if( iC2 < 0 ) // If column not valid return error
		return FALSE;
	str = str.Mid(ii + 1); // Strip off name of second column and fourth $ character

	// str=="7" - Remaining characters are second row number (as string)
	iR2 = atoi(str) - 1; // Get second row number (as integer, subtract 1 for 0 based offset)
	strRow.Format("%d", iR2 + 1); // Rebuild strRow (as string from integer) for check
	if( strRow.Compare(str) ) // If not same return error 
		return FALSE;

	// If column numbers are not in correct bounds return error
	if( iC1 < 0 || iC1 > iC2 || iC2 >= wksSheet.GetNumCols() )
		return FALSE;

	// If row numbers are not in correct bounds return error
	if( iR1	< 0 || iR1 > iR2 || iR2 >= wksSheet.GetNumRows() )
		return FALSE;

	printf("Book Name = %s\nSheet Name = %s\niC1 = %d\niC2 = %d\niR1 = %d\niR2 = %d\n", 
		strBookName, strSheetName, iC1, iC2, iR1, iR2);

	return TRUE;
}
