cd build/
output=$(./super_charger $1 $2)
echo $output
cd ../
./checker_linux "$output"