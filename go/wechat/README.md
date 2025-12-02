# WeChat Official Account API

WeChat Official Account (公眾號) API integration example.

## Features

- Get access token
- List all user OpenIDs
- Broadcast messages (text/news) to followers

## Configuration

```bash
export WECHAT_APPID="your_app_id"
export WECHAT_APPSECRET="your_app_secret"
```

## Usage

```bash
go run main.go
```

## Reference

- [WeChat Sandbox](https://mp.weixin.qq.com/debug/cgi-bin/sandboxinfo?action=showinfo&t=sandbox/index)

## Dependencies

- `github.com/silenceper/wechat/v2`
