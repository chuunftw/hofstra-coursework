[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/emUYAMn6)
[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-2972f46106e565e64193e422d61a12cf1da4916b45550586e14ef0a7c637dd04.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=20927742)
# HW3 TextMining F25
## Feedback algorithm

* Class code repository: https://github.com/HofstraDoboli/TextMining
* Starting code we did in class: `feedback_retrieval_class.ipynb`
* Use the movie plots dataset: https://www.kaggle.com/datasets/jrobischon/wikipedia-movie-plots

Steps:

1. Implement the Rocchio feedback algorithm for the same three queries you used in HW2.
   * Use the same movie set as in HW 2 (from 1980 to now) and the same inverted index (save the inverted index in a json file so you can load it later without doing the nlp steps). 
   * Show the top 7 results (e.g. movie title and plot) for each query using the tf-idf algorithm that gave you the best results in HW 2. 
   * Select the relevant and not-relevant results in the top 7 (you already have this from HW 2)
   * Apply the Rocchio algorithm (compute the modified query and then pass it through the same tf-idf function). Set alpha to 1 and try different sets of values for beta and gamma. Play with the number of terms you include in the modified query (variable th_rel and th_not_rel - see the function get_feedback_query in the `feedback_retrieval_class.ipynb`).
   * Compute the precision in top 3, top 5, and top 7 for what you think is the best result with Rocchio. Keep track of the experiments you did with the values of beta and gamma, th_rel and th_not_rel, and describe them in Answers.md
     
2. Expand your query with synonyms and thesaurus words.
   
   * Use the same queries as before, but expand each of them with additional words (e.g., synonyms, thesaurus) from your collection vocabulary. See the example in `gen_synonyms.ipynb` in the GitHub repository. It uses glove embedding and/or WordNet to find synonyms. First, extract the nouns from your query, then find synonyms for each noun. Finally, add all synonyms to the original query, which will become your modified query. 
   * Apply the same tf-idf algorithm you used on one to the new, modified query. Show the top 7 results for each query.
   * Compute precision in top 3, top 5, and top 7.

## Turn in: 

1. The jupyter notebook(s). Please organize and comment your code so that it is clear where the code and answer for each question are. 

2. Enter in Answers.md file a description of what you did, which methods you used, and the results you got for each step. Comment on the experiments you did and the precision results you got with Rocchio (Step 1) and query expansion algorithms (Step 2) versus the original tf-idf (best result in HW 2). Discuss which methods from HW2 or from this assignment work better.

3. Write in Acknowledgements.md file any help you got, and if you used LLMs, all prompts and answers you used for your coding.

