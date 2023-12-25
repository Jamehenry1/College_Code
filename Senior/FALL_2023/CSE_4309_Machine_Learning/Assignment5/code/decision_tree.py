#Nghia Lam
#1001699317

import numpy as np
from uci_data import *

class Tree:
    def __init__(self, best_attribute, best_threshold, gain,node_id,tree_id):
        self.left = None
        self.right = None
        self.best_attribute = best_attribute
        self.best_threshold = best_threshold
        self.gain = gain
        self.node_id = node_id
        self.tree_id = tree_id
        self.default = None

def Forest(forest, test_inputs, test_labels,valLabel):

    size = len(test_inputs)
    acc = 0

    #print(forest)
    for i, test in enumerate(test_inputs):
        cur_acc = 0
        multi_default = []
        dict = {} 

        for val in valLabel:
            dict[val] = 0

        final_dic = {}
        predict_val = -1
        max = 0
        predict_vals = []

        for tree in forest:

            cur_node = tree
            while cur_node.best_attribute != -1:
                if test[cur_node.best_attribute] < cur_node.best_threshold:
                    cur_node = cur_node.left
                else:
                    cur_node = cur_node.right
            
            default = cur_node.default.copy()

            multi_default.append(default)
        #print(multi_default)
        
        
        for k in range(len(multi_default)):
            for j in multi_default[k]:
                holder = multi_default[k]
                #print(j,holder[j])
                dict[j] += holder[j]
        
        for key, value in dict.items():
            final_dic[key] = value / len(forest)

        #print(final_dic)

        for j in final_dic:
            if max < final_dic[j]:
                max = final_dic[j]
                predict_val = j

        predict_vals.append(predict_val)

        for j in final_dic:
            if max < final_dic[j]:
                predict_vals.append(j)

        predict = np.random.choice(predict_vals)

        if test_labels[i] == predict:
            acc = acc + 1/len(predict_vals)
            cur_acc = 1
        else:
            cur_acc = 0

        print("ID={:5d}, predicted={:3d}, true={:3d}, accuracy={:4.2f}".format(i, predict, test_labels[i][0], cur_acc))
        #print(final_dic, predict,predict_val, predict_vals)

    acc = acc/size
    print("classification accuracy={:6.4f}\n".format(acc))


def Classification(tree, test_inputs, test_labels):

    size = len(test_inputs)
    acc = 0

    for i, test in enumerate(test_inputs):
        cur_acc = 0
        predict_val = -1
        predict = -1
        max = 0
        multi_val = []
        cur_node = tree


        while cur_node.best_attribute != -1:
            if test[cur_node.best_attribute] < cur_node.best_threshold:
                cur_node = cur_node.left
            else:
                cur_node = cur_node.right
        
        default = cur_node.default.copy()
        for j in default:
            if max < default[j]:
                max = default[j]
                predict_val = j
        
        multi_val.append(predict_val)
        for j in default:
            if max < default[j]:
                multi_val.append(j)

        predict = np.random.choice(multi_val)

        if test_labels[i] == predict:
            acc = acc + 1/len(multi_val)
            cur_acc = 1
        else:
            cur_acc = 0

        print("ID={:5d}, predicted={:3d}, true={:3d}, accuracy={:4.2f}".format(i, predict, test_labels[i][0], cur_acc))
        #print(default, predict,predict_val, multi_val)

    acc = acc/size
    print("classification accuracy={:6.4f}\n".format(acc))

    #overall_accuracy = predict / size
    #print(f"Overall Accuracy: {overall_accuracy}")

def Traversal_print(tree):
    if tree is None:
        return
    queue = []
    queue.append(tree)

    while(len(queue) > 0):
        #print(queue[0])
        node = queue.pop(0)
        print("tree={:2d}, node={:3d}, feature={:2d}, thr={:6.2f}, gain={:f}".format(node.tree_id, node.node_id, node.best_attribute, node.best_threshold, node.gain))
        if node.left is not None:
            queue.append(node.left)
        if node.right is not None:
            queue.append(node.right)

def Distribution(labels):
    #print(labels[1])
    dic = {}
    total = 0
    val,count = np.unique(labels, return_counts=True)
    total = np.sum(count)

    count = count/total
    for i in range(len(val)):
        dic[val[i]] = count[i]

    #print(dic)
    return dic

def Examples(inputs,labels,threshold,attributes):
    left_inputs = []
    left_labels = []
    right_inputs = []
    right_labels = []
    counter = 0
    for input in inputs:
        if input[attributes] >= threshold:
            right_inputs.append(input)
            right_labels.append(labels[counter])
        else:
            left_inputs.append(input)
            left_labels.append(labels[counter])
        counter += 1 

    left_inputs = np.array(left_inputs)
    left_labels = np.array(left_labels)
    right_inputs = np.array(right_inputs)
    right_labels = np.array(right_labels)

    return left_inputs,left_labels,right_inputs,right_labels
 
def Entropy(labels):

    entropy = 0
    val,count = np.unique(labels,return_counts = True)
    
    total_count = np.sum(count)
    count = count/total_count

    for k in count:
        entropy = entropy-k*np.log2(k)
    
    return entropy,total_count

def Information_Gain(inputs,labels,attributes,threshold):
    
    entropy,countP = Entropy(labels)
    left_inputs = []
    left_labels = []
    right_inputs = []
    right_labels = []
    counter = 0
    for input in inputs:
        if input[attributes] >= threshold:
            right_inputs.append(input)
            right_labels.append(labels[counter])
        else:
            left_inputs.append(input)
            left_labels.append(labels[counter])
        counter += 1 
    
    right_entropy,countR = Entropy(right_labels)
    left_entropy,countL = Entropy(left_labels)

    gain = entropy - ((countL/countP) * left_entropy) - ((countR/countP) * right_entropy)
    
    return gain
    
def Choose_attribute(inputs,labels, attributes, option):
    max_gain = -1
    best_attribute = -1
    best_threshold = -1
    ex = np.transpose(inputs)
    if option == "optimized":
        for i in range(len(attributes)):
            attributes_values = ex[i]
            #print(attributes)
            L = np.min(attributes_values)
            M = np.max(attributes_values)
            
            for K in range(1, 50):
                threshold = L + K *(M-L)/51
                #print(L, M, threshold)
                #print(threshold)
                #gain
                gain = Information_Gain(inputs,labels,attributes[i],threshold)
            
                if gain > max_gain:
                    max_gain = gain
                    best_attribute = attributes[i]
                    best_threshold = threshold
    else:
        rand = np.random.randint(0,len(attributes))
        attributes_values = ex[rand]

        L = np.min(attributes_values)
        M = np.max(attributes_values)
        
        for K in range(1, 50):
            threshold = L + K *(M-L)/51
            #print(threshold)
            #gain
            gain = Information_Gain(inputs,labels,attributes[rand],threshold)
        
            if gain > max_gain:
                max_gain = gain
                best_attribute = attributes[rand]
                best_threshold = threshold

    return max_gain,best_attribute,best_threshold

def DTL(inputs,labels,attributes,default,option,pruning_thr,node_id,tree_id,level):
    #print("done")
    level += 1
    if len(labels) < pruning_thr:
        tree = Tree(-1,-1,0,node_id,tree_id)
        tree.default = default
        #return tree
    elif len(np.unique(labels)) == 1:
        tree = Tree(-1,-1,0,node_id,tree_id)
        tree.default = Distribution(labels)
        #return tree #return_count = true
    else:
        (max_gain, best_attribute, best_thr) = Choose_attribute(inputs,labels, attributes,option)
        tree = Tree(best_attribute,best_thr,max_gain,node_id,tree_id)
        ex_left,ex_left_label,ex_right,ex_right_label = Examples(inputs,labels,best_thr,best_attribute)
        tree.left = DTL(ex_left,ex_left_label,attributes,Distribution(labels),option,pruning_thr,node_id*2,tree_id,level)
        tree.right = DTL(ex_right,ex_right_label,attributes,Distribution(labels),option,pruning_thr,(node_id*2)+1,tree_id,level)
    
    return tree
    
def decision_tree(training_file, test_file, option, pruning_thr):
    print(training_file)
    print(test_file)
    #print("works")
    (training_set, test_set) = read_uci1(training_file, test_file)
    (training_inputs, training_labels) = training_set
    (test_inputs, test_labels) = test_set

    #max_value = np.max(np.abs(training_inputs))
    #print(max_value)
    #training_inputs  = training_inputs / max_value
    #test_inputs = test_inputs/ max_value
    #training_labels = np.array(training_labels)
    
    default = Distribution(training_labels)
    attributes = []
    for i in range(len(training_inputs[0])):
        attributes.append(int(i))
        #print(i)
    attributes = np.array(attributes)
    #print(attributes)
    node_id = 1
    tree_id = 1
    level = 1
    forest = []
    valLable = np.unique(training_labels)
    
    if option == "optimized":
        tree = DTL(training_inputs,training_labels,attributes,default,option,pruning_thr,node_id,tree_id,level)
        Traversal_print(tree)
        Classification(tree, test_inputs, test_labels)
    else:
        for i in range(1,option+1):
            tree = DTL(training_inputs,training_labels,attributes,default,option,pruning_thr,node_id,i,level)
            Traversal_print(tree)
            forest.append(tree)
        
        Forest(forest, test_inputs, test_labels,valLable)
    
    
