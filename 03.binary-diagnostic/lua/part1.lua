
size = 0
count = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}

for line in io.lines() do
    size = size + 1
    for i = 1,12,1 do
        if line:sub(i, i) == '1' then
            count[i] = count[i] + 2
        end
    end
end

most = 0
least = 0
for i = 1,12,1 do
    most = most * 2
    least = least * 2
    if count[i] > size then
        most = most + 1
    else
        least = least + 1
    end
end

print('Result:', most * least)

