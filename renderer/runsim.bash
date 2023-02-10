rm ./renders/test.mp4
echo "generating"
cd ../simulation/
make
cd ../renderer
mv ../simulation/output.csv ./output.csv
echo "rendering"
python3 ./main.py ./output.csv test
echo "converting"
./convert.sh test
echo "cleaning up"
rm -r ./renders/test/
mpv --keep-open=yes ./renders/test.mp4
