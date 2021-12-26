#!/bin/bash


echo "1. Create a file"
echo "2. Create a directory"
echo "3. Remove a file"
echo "4. Remove a directory"
echo -n "Enter: "

read menu

#Enter file/directory name 
#Enter file name
if [ $menu -eq "1" ] || [ $menu -eq "3" ]
then
	echo -n "Enter filename: "
	read file_name
#Enter directory name
else
	echo -n "Enter directory: "
	read dir_name
fi

# Execute code depends on user's select.
# Create a File
if [ $menu -eq "1" ]
then
	touch ./$file_name
# Create a directory
elif [ $menu -eq "2" ]
then
	mkdir ./$dir_name
# Remove a file
elif [ $menu -eq "3" ]
then
	rm ./$file_name
# Remove a directory
else
	rmdir ./$dir_name
fi

exit 0
