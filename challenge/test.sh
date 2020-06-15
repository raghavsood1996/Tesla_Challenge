cd build/
start=$SECONDS
output=$(./super_charger $1 $2)
duration=$(( SECONDS - start ))
echo $duration
echo $output
cd ../
./checker_linux "$output"