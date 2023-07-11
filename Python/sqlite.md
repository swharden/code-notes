# SQLite in Python

```py
con = sqlite3.connect("database.sqlite")
cursor = con.cursor()
cursor.execute("SELECT name FROM sqlite_master WHERE type='table'")
foreach item in cursor.fetchall():
    print(item)
con.close()
```
