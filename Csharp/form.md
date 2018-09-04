# Forms

## Create/Launch a new Form
```cs
Form2 f2 = new Form2();
f2.Show();
```

## Switch to another form
```cs
private void button2_Click(object sender, EventArgs e)
{
    Form2 f2 = new Form2();
    f2.Show();
    this.Hide();
}
```
