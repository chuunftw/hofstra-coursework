[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/WSg5fgun)
[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-2e0aaae1b6195c2367325f4f02e2d04e9abb55f0b24a779b69b11b9e10269abc.svg)](https://classroom.github.com/online_ide?assignment_repo_id=20639500&assignment_repo_type=AssignmentRepo)
## HW2 Text Mining


**Class code repository: https://github.com/HofstraDoboli/TextMining**

0) Use the movie plots dataset from kaggle: https://www.kaggle.com/datasets/jrobischon/wikipedia-movie-plots
Go over the pandas tutorials in the links on Canvas. You will need to read the dataset (a csv file into a pandas dataframe). Use dataframe processing to answer the following questions:

 * How many movies are in the dataset?
 * Select the movies after 1980's. How many movies do you have?
 * What are the 10 most frequent genres of movies?
 * Select the title, year, the movie plot, and the genre for the movies after 1980.
 * Combine into one column, the movie plot, the title, and the genre: "movie plot " + title + "." + genre + "." 

1) Build the inverted index on the subset of movies (title + plot + genre) after 1980 (use the example we did in class (`indexing_class.ipynb` in the github repository). In addition, use spacy and the NER processing to extract names, locations, organizations - that span more than one word (e.g. San Francisco) - as terms to your vocabulary (look at the sample code in `demo_spacy.ipynb`). 

    * Which nlp processing steps did you use?
    * Give some examples of names, locations, or organizations you found and added to the corpus vocabulary. How many unique such terms did you find?
    * What is the vocabulary size (# of unique terms after processing) after nlp processing?
    * What are the most frequent and least frequent 10 words in the corpus and their document frequencies?
    * Attempt to eliminate the most common and most rare terms. What is the size of your vocabulary now.  

2) Come up with 3 queries related to movie plots. The queries should consist of more than 2-3 words. For example: 'Science fiction movies with aliens attacking earth'. Check if the most relevant words in your queries are in the inverted index - if they are not, then change your query, otherwise you will not find anything relevant. Process the queries using the same nlp processing steps as the documents. Hint: Do not use very common or very rare words in your queries. 
   * For each query, display the query, its terms, and the frequency of each term.

3) Write a function to compute the similarity of a query with the collection. Do this efficiently by computing the similarity between a query and the set of documents that contain at least two words from the query. Implement two different TF-IDF similarity functions (one of them should be BM25 - choose another one from the slides or textbook). Retrieve the ranked list of the first 7 most similar movies for each of your queries and for each of the two similarity functions.
   * For each similarity function, and each query, display the closest 7 titles, plots and genres (not the full text) and their similarity values.
     
4) For each similarity function and each query, compute the top 7 precision in the following way: Look at the top 7 movie plots, titles, and genres in the ranked list for each query. Using your own judgement, rate each movie as either relevant or irrelevant to your query. Count the number of relevant movies and divide it by 7. This is the top 7 precision:

       Top7_Precision(query_x, method_y) =  # relevant movies / 7 
        
   * Display the precision values for each query and each method. 

5) Compare and discuss the precision results you obtained with the two TF-IDF similarity functions you used. Be specific and use your results to convey your findings (avoid much better,very good, okay, fine - be precise). Comment on which method gave you better results and why? 

## Turn in

1. The Jupyter notebook showing the code and output for each question. Please organize and comment your code, so it is clear which code answers which question. Do not print the whole collection of movies. Do not display any long text in your notebook.

   WRITE YOUR OWN TF-IDF FUNCTIONS - DO NOT USE THE ONES IN THE PYTHON LIBRARIES. 

3.  Enter in Answers.md file a description of what you did, which methods you used, the results you got for all questions, and discussion and comments for 6.

4. Write in Acknowledgements.md file any help you got, and if you used LLMs, all prompts and answers you used for your coding.
