package main

import (
	"log"
	"os"

	wechat "github.com/silenceper/wechat/v2"
	"github.com/silenceper/wechat/v2/cache"
	"github.com/silenceper/wechat/v2/officialaccount/config"
)

// ref:
// https://mp.weixin.qq.com/debug/cgi-bin/sandboxinfo?action=showinfo&t=sandbox/index
func main() {
	cfg := &config.Config{
		AppID:     os.Getenv("WECHAT_APPID"),
		AppSecret: os.Getenv("WECHAT_APPSECRET"),
		Cache:     cache.NewMemory(),
	}

	wc := wechat.NewWechat()
	oa := wc.GetOfficialAccount(cfg)

	accessToken, err := oa.GetAccessToken()
	if err != nil {
		panic(err)
	}
	log.Printf("access token: %v\n", accessToken)

	ids, err := oa.GetUser().ListAllUserOpenIDs()
	if err != nil {
		panic(err)
	}
	log.Printf("ids: %v\n", ids)

	bd := oa.GetBroadcast()
	//result, err := bd.SendText(nil, "test msg")
	result, err := bd.SendNews(nil, "E8fUInABnwPD_Rm875-9t-EDtUSXweA2wrAiRFW_4OMyt8Da1Gi0s13IA040LU_j", false)
	if err != nil {
		panic(err)
	}
	log.Printf("broadcast result: %+v\n", result)
}
