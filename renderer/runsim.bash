echo "rendering"
python3 ./main.py $1 $2
echo "converting"
./convert.bash $2
echo "cleaning up"
rm -r ./renders/$2/
