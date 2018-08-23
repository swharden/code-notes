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
