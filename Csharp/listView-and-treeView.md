# ListView
```cs
listView1.Items.Clear();
foreach (string parentID in ab.abfIDsByParent.Keys)
{
    List<string> childrenIDs = ab.abfIDsByParent[parentID];

    ListViewItem itemParent = new ListViewItem(parentID);
    itemParent.BackColor = ab.abfColors[parentID];

    if (cbParentsOnly.Checked)
    {
        listView1.Items.Add(itemParent);
    }
    else
    {
        itemParent.Font = new Font(itemParent.Font, FontStyle.Bold);
        listView1.Items.Add(itemParent);
        foreach (string childID in childrenIDs)
        {
            ListViewItem itemChild = new ListViewItem(childID);
            listView1.Items.Add(itemChild);
        }
    }
}
```

# TreeView
```cs
treeViewABFs.Nodes.Clear();
foreach (string parentID in ab.abfIDsByParent.Keys)
{
    List<string> childrenIDs = ab.abfIDsByParent[parentID];

    TreeNode parentNode = new TreeNode(parentID);
    parentNode.BackColor = ab.abfColors[parentID];

    if (cbParentsOnly.Checked == false)
    {
        foreach (string childID in childrenIDs)
        {
            parentNode.Nodes.Add(childID + ".abf");
        }
    }

    treeViewABFs.Nodes.Add(parentNode);

}
```

# Large Icons in ListView

```cs
string folder = @"C:\Users\scott\Documents\important\abfs\swhlab";
ImageList imageList = new ImageList();
int imageScale = 25;
imageList.ImageSize = new Size(8* imageScale, 6* imageScale);
listView1.LargeImageList = imageList;
listView1.Clear();
foreach (string imagePath in System.IO.Directory.GetFiles(folder))
{
    System.Console.WriteLine(imagePath);
    Image image = Image.FromFile(imagePath);
    imageList.Images.Add(image);
    ListViewItem item = new ListViewItem();
    item.Text = System.IO.Path.GetFileNameWithoutExtension(imagePath);
    item.Text = item.Text.Replace("_", " ").Replace("-", " ");
    item.ImageIndex = imageList.Images.Count - 1;
    listView1.Items.Add(item);
}
```
