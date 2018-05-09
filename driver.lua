json = require("json")

-- 设备驱动编码  将 消息转换为 设备能够接受的数据格式
function ziroom_encode(source,target)

    source.type="from lua data!"
    source.mac="asaddsadsa"
    source:setData("name","zjs")
    target:writeInt16(0); --length
    target:writeInt8(0);
    target:writeInt8(0x11);
    target:writeString(source:toJSON())
    target:writeInt16(0)  -- CRC
    target:setInt16(0,target.length)
end

-- 设备驱动解码  将设备传来的数据转换为设备消息
function ziroom_decode(data)
    print(data)
end
