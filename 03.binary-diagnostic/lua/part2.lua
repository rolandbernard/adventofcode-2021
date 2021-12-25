
most = {}
least = {}

for line in io.lines() do
    table.insert(most, line)
    table.insert(least, line)
end

function countCommon(t, i)
    ones = 0
    for k, v in pairs(t) do
        if v:sub(i, i) == '1' then
            ones = ones + 2
        end
    end
    if ones < #t then
        return {'0', '1'}
    else
        return {'1', '0'}
    end
end

function filter(t, i, e)
    filtered = {}
    for k, v in pairs(t) do
        if v:sub(i, i) == e then
            table.insert(filtered, v)
        end
    end
    return filtered
end

for i = 1,12,1 do
    if #most > 1 then
        common = countCommon(most, i)
        most = filter(most, i, common[1])
    end
    if #least > 1 then
        common = countCommon(least, i)
        least = filter(least, i, common[2])
    end
end

print('Result:', tonumber(most[1], 2) * tonumber(least[1], 2))

