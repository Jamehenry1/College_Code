from naive_bayes import *
#from naive_bayes_test import *

# When you test your code, you can change this line to reflect where the 
# dataset directory is located on your machine.
dataset_directory = "C:/Users/nghia/OneDrive/Desktop/College/Senior/Machine_Learning/Assignment2/uci_dataset"

# When you test your code, you can select the dataset you want to use 
# by commenting out the other dataset names.

#dataset = "pendigits"
dataset = "satellite"
#dataset = "yeast"

training_file = dataset_directory + "/" + dataset + "_training.txt"
test_file = dataset_directory + "/" + dataset + "_test.txt"

naive_bayes(training_file, test_file)
#naive_bayes_test(training_file, test_file)
