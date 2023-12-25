import numpy as np
import os
import sys

# arguments:
#    pathname: source file of the data
#    labels_to_ints: maps original class labels to consecutive ints starting at 0
#    ints_to_labels: maps int labels to original class labels 
# returns:
#    data (each row is an object)
#    labels (one label per row of data)

def str_to_int():
    word_to_num = {
        "zero": 0,
        "one": 1,
        "two": 2,
        "three": 3,
        "four": 4,
        "five": 5,
        "six": 6,
        "seven": 7,
        "eight": 8,
        "nine": 9,
        "ten": 10,
        "class0": 0,
        "class1": 1,
        "class2": 2,
        "class3": 3,
        "class4": 4,
        "class5": 5,
        "class6": 6,
        "class7": 7,
        "class8": 8,
        "class9": 9,
        "class10": 10

    }

def read_uci_file(pathname, labels_to_ints, ints_to_labels):
    if not(os.path.isfile(pathname)):
        print("read_data: %s not found", pathname)
        return None

    in_file = open(pathname)
    file_lines = in_file.readlines()
    in_file.close()

    dict = {"class1"}

    rows = len(file_lines)
    if (rows == 0):
        print("read_data: zero rows in %s", pathname)
        return None
        
    
    cols = len(file_lines[0].split())
    data = np.zeros((rows, cols-1))
    labels = np.zeros((rows,1))
    for row in range(0, rows):
        line = file_lines[row].strip()
        items = line.split()
        if (len(items) != cols):
            print("read_data: Line %d, %d columns expected, %d columns found" %(row, cols, len(items)))
            return None
        for col in range(0, cols-1):
            data[row][col] = float(items[col])
        
        # the last column is a string representing the class label
        label = items[cols-1]
        if (label in labels_to_ints):
            ilabel = labels_to_ints[label]
        else:
            ilabel = len(labels_to_ints)
            labels_to_ints[label] = ilabel
            ints_to_labels[ilabel] = label
        
        labels[row] = ilabel

    labels = labels.astype(int)
    return (data, labels)


def read_uci_dataset(training_file, test_file):
    #training_file = directory + "/" + dataset_name + "_training.txt"
    #test_file = directory + "/" + dataset_name + "_test.txt"

    labels_to_ints = {}
    ints_to_labels = {}

    (train_data, train_labels) = read_uci_file(training_file, labels_to_ints, ints_to_labels)
    (test_data, test_labels) = read_uci_file(test_file, labels_to_ints, ints_to_labels)
    return ((train_data, train_labels), (test_data, test_labels), (ints_to_labels, labels_to_ints))


def read_uci1(training_file, test_file):
    #training_file = directory + "/" + dataset_name + "_training.txt"
    #test_file = directory + "/" + dataset_name + "_test.txt"

    labels_to_ints = {}
    ints_to_labels = {}

    (train_data, train_labels) = read_uci_file(training_file, labels_to_ints, ints_to_labels)
    (test_data, test_labels) = read_uci_file(test_file, labels_to_ints, ints_to_labels)
    return ((train_data, train_labels), (test_data, test_labels))


