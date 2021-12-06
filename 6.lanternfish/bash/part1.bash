
read raw
state=
for i in $(seq 0 8)
do
    state="$state $(grep -o $i <<< "$raw" | wc -l)"
done

for d in $(seq 80)
do
    i=0
    births=
    new_state=
    for val in $state
    do
        if [ $i -eq 0 ]
        then
            births=$val
        elif [ $i -eq 7 ]
        then
            new_state="$new_state $(expr $val + $births)"
        else
            new_state="$new_state $val"
        fi
        i=$(expr $i + 1)
    done
    state="$new_state $births"
done

echo $(dc <<< "$state ++++++++ p")

