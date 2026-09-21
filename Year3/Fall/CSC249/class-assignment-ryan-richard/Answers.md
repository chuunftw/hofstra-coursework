1. Naive bayes:

Preprocessing Steps:

1. Lowercase everything
2. Remove special characters 
3. Tokenization 
4. Filter short tokens

Built Vocab of 5k words w/ min freq of 5

Wrapped in OneVSRest to train 19 seperate binary classifiers, one per genre 

Accuracy: 13.00%
Precision (Micro): 59.11%
Recall (Micro): 61.72%
F1 (Micro): 60.39%
F1 (Macro): 46.69%

2. Bert: DistilBERT-base-uncased 66M parameters, 256 token length 

Preprocessing:

Multi-hot encoding for genres (binary vector of 19 genres, 1 = present, 0 = absent)
Tokenized using DistilBERT's tokenizer with padding and truncation to 256 tokens

Config w 3 epochs, batch size of 16 

Epoch 1:
Training Loss: 0.1905
Validation Loss: 0.2186
Accuracy: 0.1888
Precision: 0.7307
Recall: 0.5740
F1 Micro: 0.6429
F1 Macro: 0.4901

Epoch 2:
Training Loss: 0.1648
Validation Loss: 0.2173
Accuracy: 0.1800
Precision: 0.7211
Recall: 0.5986
F1 Micro: 0.6542
F1 Macro: 0.5133

Epoch 3:
Training Loss: 0.1484
Validation Loss: 0.2172
Accuracy: 0.1763
Precision: 0.7288
Recall: 0.5875
F1 Micro: 0.6506
F1 Macro: 0.5209

3. Decoder: GPT 2 Base, 124 mil parameters

Few-shot prompting: Provided 3 training examples showing plot → genres
Zero-shot prompting: Also tested without examples, just instructed model to classify

GPT had no multilabel complexitity, no fine tuning, and generally not designed for classification made it a bad model choice 

RESULTS: 

BERT achieved the highest performance 

Naive Bayes performed slightly under 

Decoder underperformance, probably due to complexity of multi-label prediction 

Multi-Label classification is challenging for the decoder due to genre overlap
