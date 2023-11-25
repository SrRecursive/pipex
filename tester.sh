#/bin/bash

# Save current directory
root=$(pwd)

# Finished testing

if [ $# -eq 1 ]; then
	rm -rf $root/txt $root/test $root/*dSYM
	printf "🗑️  🦔 \033[1;33mDirectories \033[0;31mremoved!\033[0m\n"
	exit 0
fi

printf "\033[35m\
==============================================================================================
|\033[33m __________  __                             ___________                __                   \033[35m|
|\033[33m \______   \|__|______    ____  ___  ___    \__    ___/____    _______/  |_   ____ _______  \033[35m|
|\033[33m  |     ___/|  |\____ \ _/ __ \ \  \/  /      |    | _/ __ \  /  ___/\   __\_/ __ \\_  __  \ \033[35m|
|\033[33m  |    |    |  ||  |_> >\  ___/  >    <       |    | \  ___/  \___ \  |  |  \  ___/ |  | \/ \033[35m|
|\033[33m  |____|    |__||   __/  \___  >/__/\_ \      |____|  \___  >/____  > |__|   \___  >|__|    \033[35m|
|\033[33m                |__|         \/       \/                  \/      \/             \/         \033[35m|
==============================================================================================
\033[0m"

# Directory to save test outputs

rm -rf $root/test
printf "Creating \033[1;33mtest \033[0mdirectory...\n"
mkdir $root/test

# Directory to save txts

rm -rf $root/txt
printf "Creating \033[1;33mtxt \033[0mdirectory...\n"
mkdir $root/txt

# Generate txts
echo "" > $root/txt/text1.txt

printf "Hello world
How are you doing these days?
This is a test for pipex
" > $root/txt/text2.txt

printf "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789\n" > $root/txt/text3.txt

printf "Testing absolute paths :O\n" > $root/txt/text4.txt

printf "Invalid first command\n" > $root/txt/text5.txt

printf "Invalid second command\n" > $root/txt/text6.txt

printf "Invalid both command\n" > $root/txt/text7.txt

printf "Empty first command\n" > $root/txt/text8.txt

printf "Empty second command\n" > $root/txt/text9.txt

printf "Empty both commands" > $root/txt/text10.txt

# Go to pipex directory
if [ ! $(echo "$root" | grep "pipex") ]; then
	cd $root/pipex
else
# Save git command path 
	git=$(which git)
	$git submodule update --init --recursive
fi

# Save make command path
make=$(which make)
$make -s

# Save norminette
norminette=$(which norminette)
$norminette | grep "Error!" > /dev/null
if [ $? -eq 0 ]; then
	printf "\033[33mnorminette: \033[31mKO\033[0m\n"
else
	printf "\033[33mnorminette: \033[32mOK\033[0m\n"
fi
$norminette | grep "Error!"

# Check if valgrind exists
valgrind=$(which valgrind)
if [ $? -eq 0 ]; then
	valgrind_installed=1
else
	valgrind_installed=0
fi

test_number=0

# Test 1
((test_number++))
printf "\033[1;33mTest \033[31m$test_number\033[0m: "

./pipex $root/txt/text${test_number}.txt cat echo $root/test/my_test${test_number}_output.txt
echo $? >> $root/test/my_test${test_number}_output.txt
#./pipex $root/txt/text2.txt "cat" "cat" $root/here.txt
#echo $? >> $root/here.txt
#echo "WTF" >> $root/here.txt
#echo $? >> $root/here

cat < $root/txt/text${test_number}.txt | echo > $root/test/og_test${test_number}_output.txt
echo $? >> $root/test/og_test${test_number}_output.txt

diff $root/test/my_test1_output.txt $root/test/og_test1_output.txt > /dev/null
if [ $? -eq 0 ]; then
	printf "\033[32mOK\033[0m"
else
	printf "\033[31mKO\033[0m"
fi

if [ $valgrind_installed -eq 1 ]; then
	$valgrind ./pipex $root/txt/text1.txt "cat -e" echo /dev/null 2>&1 | grep "lost" | awk '{ printf $4 }' | grep -E '[123456789]' > /dev/null
	if [ $? -eq 1 ]; then
		printf " \033[32mMOK\033[0m\n"
	else
		printf " \033[31mMKO\033[0m\n"
	fi
else
	printf "\n"
fi

# Test 2
((test_number++))
printf "\033[1;33mTest \033[31m$test_number\033[0m: "

./pipex $root/txt/text2.txt "cat -e" echo $root/test/my_test2_output.txt
echo $? >> $root/test/my_test2_output.txt

cat -e < $root/txt/text2.txt | echo > $root/test/og_test2_output.txt
echo $? >> $root/test/og_test2_output.txt

diff $root/test/my_test2_output.txt $root/test/og_test2_output.txt
if [ $? -eq 0 ]; then
	printf "\033[32mOK\033[0m"
else
	printf "\033[31mKO\033[0m"
fi

if [ $valgrind_installed -eq 1 ]; then
	$valgrind ./pipex $root/txt/text2.txt "cat -e" echo /dev/null 2>&1 | grep "lost" | awk '{ printf $4 }' | grep -E '[123456789]' > /dev/null
	if [ $? -eq 1 ]; then
		printf " \033[32mMOK\033[0m\n"
	else
		printf " \033[31mMKO\033[0m\n"
	fi
else
	printf "\n"
fi

# Test 3
((test_number++))
printf "\033[1;33mTest \033[31m$test_number\033[0m: "

./pipex $root/txt/text${test_number}.txt "cat -e" "wc -c" $root/test/my_test${test_number}_output.txt
echo $? >> $root/test/my_test${test_number}_output.txt

cat -e < $root/txt/text${test_number}.txt | wc -c > $root/test/og_test${test_number}_output.txt
echo $? >> $root/test/og_test${test_number}_output.txt

diff $root/test/my_test${test_number}_output.txt $root/test/og_test${test_number}_output.txt
if [ $? -eq 0 ]; then
	printf "\033[32mOK\033[0m"
else
	printf "\033[31mKO\033[0m"
fi

if [ $valgrind_installed -eq 1 ]; then
	$valgrind ./pipex $root/txt/text${test_number}.txt "cat -e" "wc -c" /dev/null 2>&1 | grep "lost" | awk '{ printf $4 }' | grep -E '[123456789]' > /dev/null
	if [ $? -eq 1 ]; then
		printf " \033[32mMOK\033[0m\n"
	else
		printf " \033[31mMKO\033[0m\n"
	fi
else
	printf "\n"
fi

# Test 4
((test_number++))
printf "\033[1;33mTest \033[31m$test_number\033[0m: "

./pipex $root/txt/text${test_number}.txt "/bin/cat -e" "wc -c" $root/test/my_test${test_number}_output.txt
echo $? >> $root/test/my_test${test_number}_output.txt

/bin/cat -e < $root/txt/text${test_number}.txt | wc -c > $root/test/og_test${test_number}_output.txt
echo $? >> $root/test/og_test${test_number}_output.txt

diff $root/test/my_test${test_number}_output.txt $root/test/og_test${test_number}_output.txt
if [ $? -eq 0 ]; then
	printf "\033[32mOK\033[0m"
else
	printf "\033[31mKO\033[0m"
fi

if [ $valgrind_installed -eq 1 ]; then
	$valgrind ./pipex $root/txt/text${test_number}.txt "/bin/cat -e" "wc -c" /dev/null 2>&1 | grep "lost" | awk '{ printf $4 }' | grep -E '[123456789]' > /dev/null
	if [ $? -eq 1 ]; then
		printf " \033[32mMOK\033[0m\n"
	else
		printf " \033[31mMKO\033[0m\n"
	fi
else
	printf "\n"
fi

# Test 5
((test_number++))
printf "\033[1;33mTest \033[31m$test_number\033[0m: "

./pipex $root/txt/text${test_number}.txt invent ls $root/test/my_test${test_number}_output.txt
echo $? >> $root/test/my_test${test_number}_output.txt

invent < $root/txt/text${test_number}.txt | ls > $root/test/og_test${test_number}_output.txt
echo $? >> $root/test/og_test${test_number}_output.txt

diff $root/test/my_test${test_number}_output.txt $root/test/og_test${test_number}_output.txt
if [ $? -eq 0 ]; then
	printf "\033[32mOK\033[0m"
else
	printf "\033[31mKO\033[0m"
fi

if [ $valgrind_installed -eq 1 ]; then
	$valgrind ./pipex $root/txt/text${test_number}.txt invent ls /dev/null 2>&1 | grep "lost" | awk '{ printf $4 }' | grep -E '[123456789]' > /dev/null
	if [ $? -eq 1 ]; then
		printf " \033[32mMOK\033[0m\n"
	else
		printf " \033[31mMKO\033[0m\n"
	fi
else
	printf "\n"
fi

# Test 6
((test_number++))
printf "\033[1;33mTest \033[31m$test_number\033[0m: "

./pipex $root/txt/text${test_number}.txt ls invent $root/test/my_test${test_number}_output.txt
echo $? >> $root/test/my_test${test_number}_output.txt

ls < $root/txt/text${test_number}.txt | invent > $root/test/og_test${test_number}_output.txt
echo $? >> $root/test/og_test${test_number}_output.txt

diff $root/test/my_test${test_number}_output.txt $root/test/og_test${test_number}_output.txt
if [ $? -eq 0 ]; then
	printf "\033[32mOK\033[0m"
else
	printf "\033[31mKO\033[0m"
fi

if [ $valgrind_installed -eq 1 ]; then
	$valgrind ./pipex $root/txt/text${test_number}.txt ls invent /dev/null 2>&1 | grep "lost" | awk '{ printf $4 }' | grep -E '[123456789]' > /dev/null

	if [ $? -eq 1 ]; then
		printf " \033[32mMOK\033[0m\n"
	else
		printf " \033[31mMKO\033[0m\n"
	fi
else
	printf "\n"
fi

# Test 7
((test_number++))
printf "\033[1;33mTest \033[31m$test_number\033[0m: "

./pipex $root/txt/text${test_number}.txt invent invent $root/test/my_test${test_number}_output.txt
echo $? >> $root/test/my_test${test_number}_output.txt

invent < $root/txt/text${test_number}.txt | invent > $root/test/og_test${test_number}_output.txt
echo $? >> $root/test/og_test${test_number}_output.txt

diff $root/test/my_test${test_number}_output.txt $root/test/og_test${test_number}_output.txt
if [ $? -eq 0 ]; then
	printf "\033[32mOK\033[0m"
else
	printf "\033[31mKO\033[0m"
fi

if [ $valgrind_installed -eq 1 ]; then
	$valgrind ./pipex $root/txt/text${test_number}.txt ls invent /dev/null 2>&1 | grep "lost" | awk '{ printf $4 }' | grep -E '[123456789]' > /dev/null

	if [ $? -eq 1 ]; then
		printf " \033[32mMOK\033[0m\n"
	else
		printf " \033[31mMKO\033[0m\n"
	fi
else
	printf "\n"
fi

# Test 8
((test_number++))
printf "\033[1;33mTest \033[31m$test_number\033[0m: "

./pipex $root/txt/text${test_number}.txt " " cat $root/test/my_test${test_number}_output.txt
echo $? >> $root/test/my_test${test_number}_output.txt

" " < $root/txt/text${test_number}.txt | cat > $root/test/og_test${test_number}_output.txt
echo $? >> $root/test/og_test${test_number}_output.txt

diff $root/test/my_test${test_number}_output.txt $root/test/og_test${test_number}_output.txt
if [ $? -eq 0 ]; then
	printf "\033[32mOK\033[0m"
else
	printf "\033[31mKO\033[0m"
fi

if [ $valgrind_installed -eq 1 ]; then
	$valgrind ./pipex $root/txt/text${test_number}.txt ls invent /dev/null 2>&1 | grep "lost" | awk '{ printf $4 }' | grep -E '[123456789]' > /dev/null

	if [ $? -eq 1 ]; then
		printf " \033[32mMOK\033[0m\n"
	else
		printf " \033[31mMKO\033[0m\n"
	fi
else
	printf "\n"
fi

# Test 9
((test_number++))
printf "\033[1;33mTest \033[31m$test_number\033[0m: "

./pipex $root/txt/text${test_number}.txt cat " " $root/test/my_test${test_number}_output.txt
echo $? >> $root/test/my_test${test_number}_output.txt

cat < $root/txt/text${test_number}.txt | " " > $root/test/og_test${test_number}_output.txt
echo $? >> $root/test/og_test${test_number}_output.txt

diff $root/test/my_test${test_number}_output.txt $root/test/og_test${test_number}_output.txt
if [ $? -eq 0 ]; then
	printf "\033[32mOK\033[0m"
else
	printf "\033[31mKO\033[0m"
fi

if [ $valgrind_installed -eq 1 ]; then
	$valgrind ./pipex $root/txt/text${test_number}.txt ls invent /dev/null 2>&1 | grep "lost" | awk '{ printf $4 }' | grep -E '[123456789]' > /dev/null

	if [ $? -eq 1 ]; then
		printf " \033[32mMOK\033[0m\n"
	else
		printf " \033[31mMKO\033[0m\n"
	fi
else
	printf "\n"
fi

# Test 10
((test_number++))
printf "\033[1;33mTest \033[31m$test_number\033[0m: "

./pipex $root/txt/text${test_number}.txt " " " " $root/test/my_test${test_number}_output.txt
echo $? >> $root/test/my_test${test_number}_output.txt

" " < $root/txt/text${test_number}.txt | " " > $root/test/og_test${test_number}_output.txt
echo $? >> $root/test/og_test${test_number}_output.txt

diff $root/test/my_test${test_number}_output.txt $root/test/og_test${test_number}_output.txt
if [ $? -eq 0 ]; then
	printf "\033[32mOK\033[0m"
else
	printf "\033[31mKO\033[0m"
fi

if [ $valgrind_installed -eq 1 ]; then
	$valgrind ./pipex $root/txt/text${test_number}.txt ls invent /dev/null 2>&1 | grep "lost" | awk '{ printf $4 }' | grep -E '[123456789]' > /dev/null

	if [ $? -eq 1 ]; then
		printf " \033[32mMOK\033[0m\n"
	else
		printf " \033[31mMKO\033[0m\n"
	fi
else
	printf "\n"
fi
