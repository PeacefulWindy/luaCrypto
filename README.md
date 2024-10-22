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
--生成
local keyLen=2048--RSA长度
local publicKey,privateKey=crypto.rsa_gen(keyLen)

--加密
local hash=crypto.rsa_encode(publicKey,needHashString)

--解密
local needHashString=crypto.rsa_decode(privateKey,hash,#hash)
```