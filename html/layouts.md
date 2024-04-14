# Holy Grail HTML Layouts

### Two Columns with Header

https://swharden.com/tmp/html-layouts/ColColHeader/

```html
<!doctype html>
<html lang="en">

<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Holy Grail Layout: two columns with header</title>

    <style>
        body {
            margin: 0;
        }

        header {
            background-color: #7da96e;
            position: fixed;
            top: 0px;
            height: 100px;
            width: 100%;
        }

        .sidebar {
            position: fixed;
            top: 0;
            padding-top: 100px;
            height: 100%;
            width: 200px;
        }

        .sidebar-inner {
            height: 100%;
            width: 100%;
            margin: 0px;
            background-color: #88a5c2;
            overflow-y: scroll;
            overflow-x: scroll;
        }

        main {
            display: block !important;
            top: 100px;
            margin-left: 200px;
            margin-top: 100px;
        }
    </style>

</head>

<body>
    <header>
        <div>Header (fixed height)</div>
    </header>

    <div class="sidebar">
        <div class="sidebar-inner">
            Navigation
            <ul>
                <script>
                    for (i = 1; i <= 100; i++)
                        document.write(`<li>Item ${i}</li>`);
                </script>
            </ul>
        </div>
    </div>

    <main>
        Content
        <ul>
            <script>
                for (i = 1; i <= 100; i++)
                    document.write(`<li>Item ${i}</li>`);
            </script>
        </ul>
    </main>
</body>

</html>
```

### Two Columns

https://swharden.com/tmp/html-layouts/ColCol/

```html
<!doctype html>
<html lang="en">

<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Holy Grail Layout: two columns</title>

    <style>
        body {
            margin: 0;
        }

        .sidebar {
            position: fixed;
            top: 0;
            height: 100%;
            width: 200px;
        }

        .sidebar-inner {
            height: 100%;
            width: 100%;
            margin: 0px;
            background-color: #88a5c2;
            overflow-y: scroll;
            overflow-x: scroll;
        }

        main {
            display: block !important;
            margin-left: 200px;
        }
    </style>

</head>

<body>
    <div class="sidebar">
        <div class="sidebar-inner">
            Navigation
            <ul>
                <script>
                    for (i = 1; i <= 100; i++)
                        document.write(`<li>Item ${i}</li>`);
                </script>
            </ul>
        </div>
    </div>

    <main>
        Content
        <ul>
            <script>
                for (i = 1; i <= 100; i++)
                    document.write(`<li>Item ${i}</li>`);
            </script>
        </ul>
    </main>
</body>

</html>
```
