for ((i=0; i<10; i++))
do
    ./zappy_ai -n $2 -h 127.0.0.1 -p 4242 &
done

exit 0