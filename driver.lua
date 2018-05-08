json=require("json")
function ziroom_encode(data)
    print(data)
    d=json.decode(data)
    print(d.type)
    return d.type
end

function ziroom_decode(data)
    print(data)
end
