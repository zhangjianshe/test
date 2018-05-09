json = require("json")

-- 设备驱动编码  将 消息转换为 设备能够接受的数据格式
function ziroom_encode(source,target)

    source.type="from lua data!"
    source.mac="asaddsadsa"
    target:writeInt32(1);
    target:writeInt16(2);
    target:writeString("{abc:123张}")
end

-- 设备驱动解码  将设备传来的数据转换为设备消息
function ziroom_decode(data)
    print(data)
end
