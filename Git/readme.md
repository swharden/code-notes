# Git Notes

## Clean and Delete Untracked Files

* removes any uncomitted changes
* deletes all `bin` and `obj` folders in a repository

```sh
git clean -xfd
```

## Allow Pulling Another Repo

To correct this issue:

```
fatal: detected dubious ownership in repository at
```

Run this command. If using the Windows command prompt you must not include quotes around the asterisk!

```sh
git config --global safe.directory *
```
