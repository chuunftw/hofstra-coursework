[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/hKqEmuYr)
[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-2972f46106e565e64193e422d61a12cf1da4916b45550586e14ef0a7c637dd04.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=21097784)
# HW4 TextMining F25
## IR with dense vector embeddings

* Class code repository: https://github.com/HofstraDoboli/TextMining
* Starting code we did in class: `sentence_transformers.ipynb`
* Use the movie plots dataset: https://www.kaggle.com/datasets/jrobischon/wikipedia-movie-plots

Use the same movie set as in HW 2 (from 1980 to now) and the same queries. 

Steps:

1. Choose 2 embedding models from the MTEB leaderboard (https://huggingface.co/spaces/mteb/leaderboard). One of them should be a BERT-based model with a context length of more than 500 tokens, and the other should be a decoder-based model with a context length of around 1,000.
  a) Describe the models you chose (context length, number of parameters, base model, size of embedding, etc) and why you chose them.
  a) Embed the first 10 movie plots in your dataset using both models (use the starting code in `sentence_transformers.ipynb`)
  b) How many of those 10 plots were embedded without truncation by each model?
  c) What is the max, min, and average word length of all your movie plots? Discuss if the models you chose are good options for embedding the movie plots in your dataset. If they are not, please choose another model or models. 

3. Embed all movie plots using each of the two models. Use faiss vector database to store the vector embeddings. Use this website as a starting point (https://medium.com/loopio-tech/how-to-use-faiss-to-build-your-first-similarity-search-bf0f708aa772). Save your vectors locally. Do not redo the embeddings as it takes the most time. Also, you need to use a GPU type of runtime in your Google colab - and you have limited time to use them. 
    a) How many vectors you have stored in your faiss vector database.
    b) How many movie plots were truncated by your embedding model in each model you selected. 
    b) Describe the main types of exact and ANN algorithms in the FAISS library and how you can select them. 

5. Each of your three queries from HW 2 embed it using the two models, then find the top 7 results (e.g. movie title and plot) for each query using the cosine similarity function from your faiss database. Try both an exact  and an approximate algorithm (IVF).
   * Find the relevant and not-relevant results in the top 7 using both exact and approximate algorithms from faiss and for both embedding models
   * Compute the precision in top 7.
   * Compare precision of these results (exact and ANN) and the small and large embedding models with the results you got with best tf-idf and best Rocchio feedback algorithm.
   * Comment on your results and the use of sentence embedding models for IR.  

## Turn in: 

1. The jupyter notebook(s). Please organize and comment your code so that it is clear where the code and answer for each question are. 

2. Enter in Answers.md file answers to all questions. Add a text description of what you did and what results you got. Please be specific. 

3. Write in Acknowledgements.md file any help you got, and if you used LLMs, all prompts and answers you used for your coding.

