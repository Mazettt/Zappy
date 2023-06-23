if [ $# -ne 2 ]
then
    echo "Usage: $0 <number of clients> <team name>"
    exit 1
fi

for ((i=0; i<$1; i++))
do
    ./zappy_ai -n $2 &
done

exit 0