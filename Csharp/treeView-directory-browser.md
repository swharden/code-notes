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
```

```cs
/// <summary>
/// tree view item selected
/// </summary>
private void treeViewDir_AfterSelect(object sender, TreeViewEventArgs e)
{
    System.Console.WriteLine("NODE SELECTED");
    lblCurrentFolder.Text = treeViewDir_nodeToPath(e.Node);
}
```

```cs
/// <summary>
/// walk up a node's parents and return its full path
/// </summary>
private string treeViewDir_nodeToPath(TreeNode clickedNode)
{
    string clickedNodePath = "";
    while (clickedNode != null)
    {
	clickedNodePath = System.IO.Path.Combine(clickedNode.Text + "\\", clickedNodePath);
	clickedNode = clickedNode.Parent;
    }
    clickedNodePath = clickedNodePath.Replace("\\\\", "\\");
    return clickedNodePath;
}
```

```cs
/// <summary>
/// when a node is expanded scan and display its contents
/// </summary>
private void treeViewDir_BeforeExpand(object sender, TreeViewCancelEventArgs e)
{
    e.Node.Nodes.Clear();
    e.Node.Nodes.AddRange(TreeViewDirScanFolder(treeViewDir_nodeToPath(e.Node)));
}
```

## Adding Icons
Add an imagelist to your project and import the icons you want.
Set `smallImageList` to your imagelist in the listView properties.
```cs
lvFolders.Items.Clear();
ListViewItem item = new ListViewItem();
item.ImageIndex = 1;
item.Text = "C:/";
item.ForeColor = Color.Blue;
lvFolders.Items.Add(item);
```
