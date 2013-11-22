CS440-Text-Document-Classification
==================================

We first calculated prior for each class from the training data by: P(i-th class)=total # of words appeared in classs itotal / # of words in the traing set. Then we calculated likelihood of each words given class label for training set by
p(word | i-th class)= (# of word occurences in ith class +1 )/ (total # of words in ith class + # of unique words in the training). Here, the smooth constants V we adopted is the number of unique words in the training set, which is a universal constants for Laplacian smoothing.

Testing
==================================
The overall classification rate 233(hit) / 264(total) = 0.8523

Futher
==================================
We removed stop words and regenerated the 8.trainingdata.nostop.txt and 8.testingdata.nostop.txt files for training and testing. And redo the experiment of part 2. The overall classification rate enhanced to 242(hit) / 264(total) = 0.91667

Word Cloud
==================================
