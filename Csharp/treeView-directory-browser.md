# TreeView Directory Browser

To create an explorer-like file browser using TreeView:

* Create a tree view (named `treeViewDir`)
* Copy/paste this code block into your form
* Bind functions to events `AfterSelect`, `BeforeExpand`
* Call `TreeViewDirInit()` in your initialization routine

```cs
#region tree directory browser

// call this when your program loads
public void TreeViewDirInit()
{
    treeViewDir.Nodes.Clear();
    treeViewDir.Nodes.AddRange(TreeViewDirScanFolder());
}

// return path contents as treenodes for a treeview
public TreeNode[] TreeViewDirScanFolder(string path = null)
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

    }
    else
    {
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
	}
	catch
	{
	    // we don't have access to the folder, so return what we can
	    System.Console.WriteLine("DIRECTORY ACCESS ERROR");
	    treeNodes.Add(new TreeNode(""));
	}
    }
    return treeNodes.ToArray();
}

private void TreeViewDir_AfterSelect(object sender, TreeViewEventArgs e)
{
    string selectedFolder = TreeViewDir_nodeToPath(e.Node);
    System.Console.WriteLine($"SELECTED FOLDER: {selectedFolder}");
}

// walk up a node's parents and return its full path
private string TreeViewDir_nodeToPath(TreeNode clickedNode)
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

// when a node is expanded scan and display its contents
private void TreeViewDir_BeforeExpand(object sender, TreeViewCancelEventArgs e)
{
    e.Node.Nodes.Clear();
    e.Node.Nodes.AddRange(TreeViewDirScanFolder(TreeViewDir_nodeToPath(e.Node)));
}
#endregion
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

## Adding Large (Image) Icons
```cs
public void SetFolder(string folder)
{
    // clear the old contents
    listView1.Items.Clear();

    // prepare the new image list
    ImageList imageList = new ImageList();
    int imageScale = 20;
    imageList.ImageSize = new Size(8 * imageScale, 6 * imageScale);
    listView1.LargeImageList = imageList;

    // load the image files
    foreach (string imagePath in ImageFilesInFolder(folder))
    {
	Image image = Image.FromFile(imagePath);
	imageList.Images.Add(image);

	ListViewItem item = new ListViewItem();
	item.Text = Path.GetFileNameWithoutExtension(imagePath);
	item.Text = item.Text.Replace("_", " ").Replace("-", " ");
	item.ImageIndex = imageList.Images.Count - 1;
	listView1.Items.Add(item);
    }

}
```
