# Use SSH to Clone a GitHub Repo on Linux

If you enabled two-factor authentication (2FA) you will be unable 
to easily clone repositories using HTTPS username and password.

### Generate a SSH Key Pair

```bash
ssh-keygen -t ed25519 -C "swharden@gmail.com"
```

### Add the Key to Your System
```bash
ssh-add ~/.ssh/id_ed25519
```

### Give GitHub Your Public Key
```bash
cat ~/.ssh/id_ed25519.pub
```

### Verify SSH Authentication Works
```bash
ssh -T git@github.com
```

Clone a repo
```bash
git clone git@github.com:USERNAME/REPONAME.git
```
