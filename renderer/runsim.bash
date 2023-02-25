rm ./renders/test.mp4
rm -r ./renders/test/
echo "generating"
cd ../simulation/
time make
cd ../renderer
mv ../simulation/output.csv ./output.csv
echo "rendering"
python3 ./main.py ./output.csv test
echo "converting"
./convert.sh test
echo "cleaning up"
rm -r ./renders/test/
mpv --keep-open=yes ./renders/test.mp4
