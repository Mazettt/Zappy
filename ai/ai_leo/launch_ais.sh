# executes ./zappy_ai -p 4242 -n Leo X times

if [ $# -ne 2 ]
then
    echo "Usage: $0 <number of clients> <team name>"
    exit 1
fi

for i in `seq 1 $1`
do
    ./zappy_ai -p 4242 -n $2 &
done

wait
exit 0