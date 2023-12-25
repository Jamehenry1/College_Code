# Nghia Lam
# 1001699317
# Windows 
# Using python 3.9.7

import os

location = '.'			#This is the current working directory

def sizeCal(ldir):		
	size = 0 			

	for file in os.scandir(ldir):		#loops for every file in the directory

		if file.is_file():				#if it is a file
			file_stats = os.stat(file)	#gets the stats of the file then put it in size
			size += file_stats.st_size
			#print(size)

		if file.is_dir():				#if it is a directory
			#print(file.path)
			size += sizeCal(file)		#recursively does the function and puts it into size

	return size

total_size = sizeCal(location)
print(total_size)
