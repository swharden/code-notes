# Forms

## Passing data between forms
I like to pass reference types on the initializer of new forms. This lets them share variables.

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
## Launch another form by default
Edit `Program.cs`
```cs
static void Main()
{
    Application.EnableVisualStyles();
    Application.SetCompatibleTextRenderingDefault(false);
    Application.Run(new Form2());
}
```
