echo "rendering"
python3 ./main.py ./tests/$1.csv $1
echo "converting"
./convert.bash $1
echo "cleaning up"
rm -r ./renders/$1/