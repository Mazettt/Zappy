# launches multiple times ./zappy_ai -p 4242 -n Leo

if [ $# -ne 2 ]
then
    echo "Usage: $0 <nb> <team>"
    exit 1
fi

nb=$1
team=$2

i=0
while [ $i -lt $nb ]
do
    ./zappy_ai -p 4242 -n $team &
    i=$((i+1))
done

wait

exit 0