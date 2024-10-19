# luaCrypto
封装crypto接口给lua使用

使用的第三方库为：cryptopp,lua

使用说明：

加载：
```
local crypto=require "luaCrypto"
local needHashString="Hello World"
```

Base64
```
local hash=crypto.base64_encode(needHashString)
local needHashString=crypto.base64_decode(hash)
```

SHA3-256
```
local hash=crypto.sha3_256(needHashString)
```

RSA
```
--生成(参考https://gist.github.com/TimSC/5251670)
local keyLen=2048--RSA长度
crypto.rsa_gen(keyLen,_P.config.publicKey,_P.config.privateKey)

--加密(参考https://cloud.tencent.com/developer/article/2366448)
local hash=crypto.rsa_encode("xxx.pub",needHashString)

--解密（参考https://cloud.tencent.com/developer/article/2366448)
local needHashString=crypto.rsa_decode("xxx.pem",hash,#hash)
```