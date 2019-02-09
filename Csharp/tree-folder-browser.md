```cs
private void TreeBrowserLoad()
{
    string[] drives = Environment.GetLogicalDrives();
    foreach (string drive in drives)
    {
        System.IO.DriveInfo di = new System.IO.DriveInfo(drive);
        int driveImage;

        // define icon based on drive type
        switch (di.DriveType)
        {
            case System.IO.DriveType.CDRom:
                driveImage = 3;
                break;
            case System.IO.DriveType.Network:
                driveImage = 6;
                break;
            case System.IO.DriveType.NoRootDirectory:
                driveImage = 8;
                break;
            case System.IO.DriveType.Unknown:
                driveImage = 8;
                break;
            default:
                driveImage = 2;
                break;
        }

        TreeNode node = new TreeNode(drive.Substring(0, 1), driveImage, driveImage);
        node.Tag = drive;
        if (di.IsReady == true)
            node.Nodes.Add("...");
        treeView1.Nodes.Add(node);
    }
}
```

```cs
private void treeView1_BeforeExpand(object sender, TreeViewCancelEventArgs e)
{
    if (e.Node.Nodes.Count > 0)
    {
        if (e.Node.Nodes[0].Text == "..." && e.Node.Nodes[0].Tag == null)
        {
            e.Node.Nodes.Clear();

            //get the list of sub direcotires
            string[] dirs = System.IO.Directory.GetDirectories(e.Node.Tag.ToString());

            foreach (string dir in dirs)
            {
                System.IO.DirectoryInfo di = new System.IO.DirectoryInfo(dir);
                TreeNode node = new TreeNode(di.Name, 0, 1);

                try
                {
                    //keep the directory's full path in the tag for use later
                    node.Tag = dir;

                    //if the directory has sub directories add the place holder
                    if (di.GetDirectories().Count() > 0)
                        node.Nodes.Add(null, "...", 0, 0);
                }
                catch (UnauthorizedAccessException)
                {
                    //display a locked folder icon
                    node.ImageIndex = 12;
                    node.SelectedImageIndex = 12;
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message, "DirectoryLister",
                        MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
                finally
                {
                    e.Node.Nodes.Add(node);
                }
            }
        }
    }
}
```

```cs
private void TreeBrowserSelectPath(string path)
{
    path = System.IO.Path.GetFullPath(path);
    List<string> folderNames = new List<string>(path.Split(System.IO.Path.DirectorySeparatorChar));
    TreeBrowserExpandChildren(treeView1.Nodes[0], folderNames);
}

private void TreeBrowserExpandChildren(TreeNode node, List<string> children)
{
    children.RemoveAt(0);
    node.Expand();
    if (children.Count == 0)
        return;
    foreach (TreeNode mynode in node.Nodes)
        if (mynode.Text == children[0])
        {
            treeView1.SelectedNode = mynode;
            TreeBrowserExpandChildren(mynode, children);
            break;
        }
}
```

```cs
private void treeView1_AfterSelect(object sender, TreeViewEventArgs e)
{
    string path = "";
    var mynode = e.Node;
    while (mynode != null)
    {
        path = mynode.Text + "/" + path;
        mynode = mynode.Parent;
    }
    path = path.Insert(1, ":");
    path = System.IO.Path.GetFullPath(path);
    Console.WriteLine(path);
}
```
