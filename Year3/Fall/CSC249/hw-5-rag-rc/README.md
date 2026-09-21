[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/KqA4gI1h)
[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-2972f46106e565e64193e422d61a12cf1da4916b45550586e14ef0a7c637dd04.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=21667691)
# HW5 TextMining F25
## RAG with cross-encoder

* Class code repository: https://github.com/HofstraDoboli/TextMining
* Starting code we did in class: `sentence_transformers.ipynb`, `faiss.ipynb`, `sample_rag.ipynb`
* Use the movie plots dataset: https://www.kaggle.com/datasets/jrobischon/wikipedia-movie-plots
* Article about cross-encoders: https://medium.com/@kakumar1611/the-illustrated-guide-to-cross-encoders-from-deep-to-shallow-2a23a8630016
* Documentation cross-encoders:     https://sbert.net/examples/cross_encoder/applications/README.html
* About cross-encoders efficiency using pytorch (default) library:  https://sbert.net/docs/cross_encoder/usage/efficiency.html
  
Use the same movie set as in HW 2 (from 1980 to now) and the same queries. 
Use the embedding model and embedding vectors that gave you the best results in HW 4. You only need your top 7 movies for each query. 

Steps:

1. Choose a cross-encoder model to encode the query and the best top movie plots you got in HW 4. Encode the query with each of the top 7 movies returned. Select the movies in the top 3 by relevance score.

Typical cross-encoders are based on the encoder architecture (e.g., BERT) and are limited to about 512 tokens for their input. You will have to pair the query to each top 7 movie plot and pass it to the cross-encoder. Here are some popular BERT based cross-encoders, all with a max input token size of 512:
   * `cross-encoder/ms-marco-MiniLM-L-6-v2` Trained for passage re-ranking on the MS MARCO dataset (https://huggingface.co/datasets/microsoft/ms_marco). Often used for search and question answering tasks.
   * `cross-encoder/nli-roberta-base` Trained for natural language inference (entailment, contradiction, neutral).
   * `cross-encoder/stsb-roberta-base` Trained on the Semantic Textual Similarity Benchmark (STSb). Outputs a similarity score between 0 and 1.
   * `cross-encoder/qnli-roberta-base` Trained for question-answer sentence pair classification (Question Natural Language Inference task).

A cross-encoder combines the query and the movie plot as below:
```
   [CLS] Query [SEP] Movie Plot [SEP]
```
And it outputs a relevance score between -1 and 1 or between 0 and 1. 

Here is a sample code using the sentence_transformers library:
```
from sentence_transformers import CrossEncoder

# Load a pretrained cross-encoder
model = CrossEncoder('cross-encoder/ms-marco-MiniLM-L-6-v2')

# Define sentence pairs
pairs = [
    ("What is the capital of France?", "Paris is the capital of France."),
    ("What is the capital of France?", "Berlin is the capital of Germany.")

# Get similarity scores
scores = model.predict(pairs)
print(scores)
```
In many cases, your query + movie plot will exceed 512 tokens. Since your `[CLS] + query + [SEP] + movie plot + [SEP]` may extend over 512 tokens, you need to chunk the movie plot into several chunks such that `# tokens([CLS] + query + [SEP] + movie plot chunk i + [SEP]) < 512'. You will then get a relevance score for each pair of query and movie plot chunk. The final relevance score can be either the maximum relevance or the average relevance. 

Write your own chunking function that attempts to chunk by sentences. Add sentences one by one, until a max_chunk_size (e.g., 400) is reached. Eliminate the last sentence, so the limit is less than the max_chunk_size.  Add the last sentence in each chunk to the beginning of the next chunk (that will represent the overlap). Work with the Autotokenizer and model.encode functions. 
```
   def chunk_text(movie_plot, tokenizer, max_chunk_size=400, max_overlap = 100):
```
Write your function that generates a score for all chunks in a movie plot - try max(score among all chunks):
```
   def get_relevance_score(query, movie_plot, tokenizer, model):
```

**Questions:**
   1. A. What are the top 3 most relevant movie plots ranked by the cross-encoders from the top 7 retrieved with your best method from HW 4 (for each of your queries)? Are they the most relevant to your query or not? If not, please propose a change that would improve the results or your ability to weed out non-relevant plots. And implement your proposed change.
   1. B. What issues did you encounter and how did you solve them?

3. Choose a generative LLM model (not a sentence embedding model) to send a prompt formulated from the query and the top 3 movies. Generate the answer with the LLM. Look at the code in `sample_rag.ipynb` for a starting point. I suggest you try a more advanced LLM (maybe llama3-8B, mistral-7B, but be aware of the GPU memory). First try with a very small model (e.g., TinyLlama (1.1B)). Also, each LLM has a max context window. Adding three long movie plots to each query might exceed the model's context window - especially for smaller-sized models. I suggest adding only the first two sentences in each movie plot to the LLM prompt instead of the whole plot. 
```
!pip install transformers accelerate bitsandbytes

from transformers import AutoTokenizer, AutoModelForCausalLM
import torch

model_id = "meta-llama/Meta-Llama-3-8B"  # TinyLlama/TinyLlama-1.1B-Chat-v1.0 (start with the small one first)
tokenizer = AutoTokenizer.from_pretrained(model_id)
model = AutoModelForCausalLM.from_pretrained(model_id, torch_dtype=torch.float16, device_map="auto")
```
**Questions:**
2. A. What is the context size for the small and for the large model you chose? How did you formulate the prompt to the LLM such that it will not exceed the size of the context window? 

2. B. What is the generated output for each of the queries using the small and the big models? Comment on the results you obtained. 
2. C. Does changing the max_size of the generated output, and/or the temperature improve or not the answers? 


## Turn in: 

1. The jupyter notebook(s). Please organize and comment your code so that it is clear where the code and answer for each question are. 

2. Enter in Answers.md file answers to all questions. Add a text description of what you did and what results you got. Please be specific. 

3. Write in Acknowledgements.md file any help you got, and if you used LLMs, all prompts and answers you used for your coding.

