# TreeView Directory Browser

To create an explorer-like file browser using TreeView, I did this:

## Return Folder Contents as a TreeNode
```cs
/// <summary>
/// Scan the given path and return its contents as treenodes for a treeview
/// </summary>
public TreeNode[] TreeViewDirScanFolder(string path=null)
{
    List<TreeNode> treeNodes = new List<TreeNode>();
    if (path == null)
    {
	// no path is given, so return drive letters
	foreach (System.IO.DriveInfo drive in System.IO.DriveInfo.GetDrives())
	{
	    if (!drive.IsReady) continue;
	    TreeNode tn = new TreeNode(drive.Name);
	    tn.Nodes.Add("");
	    treeNodes.Add(tn);
	}

    } else
    {
	System.Console.WriteLine("Scanning folder: " + path);
	try
	{
	    // a path is given, so return its contents
	    string[] folderNames = System.IO.Directory.GetDirectories(path);
	    string[] fileNames = System.IO.Directory.GetFiles(path);
	    foreach (string folderName in folderNames)
	    {
		TreeNode tn = new TreeNode(System.IO.Path.GetFileName(folderName));
		tn.Nodes.Add("");

		// skip folders we don't have access to
		try
		{
		    System.Security.AccessControl.DirectorySecurity ds;
		    ds = System.IO.Directory.GetAccessControl(System.IO.Path.Combine(path, folderName));
		}
		catch
		{
		    continue;
		}

		// skip folders starting with $
		if (System.IO.Path.GetFileName(folderName).StartsWith("$")) continue;

		treeNodes.Add(tn);
	    }
	    foreach (string fileName in fileNames)
	    {
		TreeNode tn = new TreeNode(System.IO.Path.GetFileName(fileName));
		treeNodes.Add(tn);
	    }
	} catch
	{
	    // we don't have access to the folder, so return what we can
	    System.Console.WriteLine("DIRECTORY ACCESS ERROR");
	    treeNodes.Add(new TreeNode(""));
	}
    }
    return treeNodes.ToArray();
}
```

## Interact with the TreeView
```cs



/// <summary>
/// clear the tree view directory browser and only display drive letters
/// </summary>
public void TreeViewDirInit()
{
	treeViewDir.Nodes.Clear();
	treeViewDir.Nodes.AddRange(TreeViewDirScanFolder());
}

/// <summary>
/// tree view item selected
/// </summary>
private void treeViewDir_AfterSelect(object sender, TreeViewEventArgs e)
{
	System.Console.WriteLine("NODE SELECTED");
}

/// <summary>
/// when a node is selected determine its full path
/// </summary>
private void treeViewDir_NodeMouseClick(object sender, TreeNodeMouseClickEventArgs e)
{

	// dont scan folders being collapsed
	if (e.Node.IsExpanded == false) return;

	// walk up the node parents to get a full file path
	TreeNode clickedNode = e.Node;
	TreeNode clickedNodeParent = e.Node.Parent;
	string clickedNodePath = clickedNode.Text;
	while (clickedNodeParent != null)
	{
		clickedNodePath = System.IO.Path.Combine(clickedNodeParent.Text+"\\", clickedNodePath);
		clickedNodeParent = clickedNodeParent.Parent;
	}

	// fill the clicked node with its folder contents
	clickedNode.Nodes.Clear();
	clickedNode.Nodes.AddRange(TreeViewDirScanFolder(clickedNodePath));
}
```
