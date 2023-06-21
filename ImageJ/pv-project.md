# PV Project

Project and save PrairieView data as a single TIF file:

```java
function ProcessFolder(dir, folderName){
	
	// locate the XML file
    xmlFilePath = dir+folderName+"/"+folderName+".xml";
    if (!File.exists(xmlFilePath))
        exit("XML file does not exist:\n" + xmlFilePath);
        
    // determine output filenames
    outputTifPath = dir+folderName+"/References/"+folderName+".tif";
    outputPngPath = dir+folderName+"/References/"+folderName+"_proj.png";
    
    // check if analysis is required
    if (File.exists(outputTifPath)){
    	print("Skipping (output file exists)");
    	return;
    }
    
    // load source data
    print("Loading...");
    run("Quick PrairieView Loader", "select=[" + xmlFilePath + "]");
    
    // make channel 1 magenta instead of red
	Stack.setPosition(1,1,1);
	run("Magenta");
	
	// save the full stack
    print("Saving...");
	saveAs("Tiff", outputTifPath);

	// create and save a projection
	run("Z Project...", "projection=[Average Intensity]");
	run("RGB Color");
	saveAs("PNG", outputPngPath);
}

function ProcessSubFolders(dir){
	print("\\Clear");
	if (!endsWith(dir, "/"))
		dir = dir + "/";
		
	if (!File.isDirectory(dir))
	    exit("Folder not found:\n" + dir);
	        
	list = getFileList(dir);
	for (i=0; i<list.length; i++) {
	    if (!endsWith(list[i], "/"))
	        continue;
	    folderName = list[i].replace("/","");
	    
	    print("");
	    print("Processing " + i + " of " + list.length + ": " + folderName);
	    ProcessFolder(dir, folderName);
		close("*");
	}
}

ProcessSubFolders("X:\\Data\\zProjects\\project\\2p");
```
