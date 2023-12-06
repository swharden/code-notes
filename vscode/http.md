# HTTP Files in VS Code

Requries a `HTTP Client` plugin for VS Code

```
### Simple Request
GET https://example.com/api
Accept: application/json
```

```
### Post with Data
POST https://example.com/api/login HTTP/1.1
Content-Type: application/json

{
  "username": "testuser",
  "password": "testpassword"
}
```
