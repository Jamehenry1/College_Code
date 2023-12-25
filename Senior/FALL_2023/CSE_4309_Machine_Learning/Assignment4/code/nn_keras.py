#Nghia Lam
#1001699317

import tensorflow as tf
import numpy as np

print(tf.__version__)

from uci_data import *

#%%

# loading the dataset

def nn_keras(directory, dataset, layers, units_per_layer, epochs):
  (training_set, test_set) = read_uci1(directory, dataset)
  (training_inputs, training_labels) = training_set
  (test_inputs, test_labels) = test_set

  max_value = np.max(np.abs(training_inputs))
  training_inputs  = training_inputs / max_value
  test_inputs = test_inputs/ max_value

  #%%

  # Creating the model


  input_shape = training_inputs[0].shape
  number_of_classes = np.max([np.max(training_labels), np.max(test_labels)]) + 1

  model = tf.keras.Sequential([tf.keras.Input(shape = input_shape)])

  #This is to add the number of classes in when the layer is more than 2
  if layers > 2:
    for i in range(layers - 2):
      model.add(tf.keras.layers.Dense(units_per_layer, activation = 'sigmoid'))

  model.add(tf.keras.layers.Dense(number_of_classes, activation = 'sigmoid'))


  #model = tf.keras.Sequential([
  #    tf.keras.Input(shape = input_shape),
  #    tf.keras.layers.Dense(number_of_classes, activation='sigmoid')])

  model.compile(optimizer='adam',
                loss=tf.keras.losses.SparseCategoricalCrossentropy(),
                metrics=['accuracy'])
  
  #for some reason epochs does not work when pushing it into the model
  #got no idea why but sure so I had to do it this way
  testEpochs = epochs

  # Training the model
  print(f"epochs:{epochs}")
  model.fit(training_inputs, training_labels, epochs=testEpochs)
  print(f"epochs:{epochs}")

  # Testing the model
  test_loss, test_acc = model.evaluate(test_inputs,  test_labels, verbose=0)
  print('\nTest accuracy: %.2f%%' % (test_acc * 100))

  #%%

  # applying the model on a specific input vector

  fAcc = 0
  #This is the classification, Had to do this to print out each ID
  for input in range(len(test_inputs)):
    test = np.reshape(test_inputs[input], (1, len(test_inputs[0])))
    nn_output = model.predict(test).flatten()
    predicted_class = np.argmax(nn_output)
    actual_class = test_labels[input]
    #print("predicted: %d\nactual: %d\n" % (predicted_class, actual_class))

    (indices,) = np.nonzero(nn_output == nn_output[predicted_class])
    #print("indices =", indices)
    number_of_ties = np.prod(indices.shape)

    if (nn_output[actual_class] == nn_output[predicted_class]):
        accuracy = 1.0 / number_of_ties
    else:
        accuracy = 0

    fAcc += accuracy

    print("accuracy = %.4f" % (accuracy))
    print('ID=%5d, predicted=%10s, true=%10s, accuracy=%4.2f\n' % (input + 1, predicted_class, actual_class, accuracy))

  print('classification accuracy=%6.4f\n' % (fAcc/len(test_inputs)))