Ryan worked on encoder, Richard Worked on Decoder 

1. Describe the models you chose (context length, number of parameters, base model, size of embedding, etc.) and why you chose them
    Model 1: jina-embeddings-v2-base-en (ENCODER)

    Context length of 2048/8192 tokens
    Parameters: 137M
    Base Model: BERT
    Embedding Dimension 768
    Rank: 157th
    Zero-shot Coverage: 100%

    We chose this model b/c it meets the 500+ token requirements. Its 100% zero shot means it can perform well on embedding tasks without being specifically trained for the individual tasks.

    Model 2: Qwen3-Embedding-0.6B

    Context length of 1024/32768
    Parameters: 595M
    Base Model: Qwen3
    Embedding Dimension 1024
    Rank: 5
    Zero-shot Coverage: 99%

    I chose this model b/c its high model rank and high zero shot coverage, meaning it doesnt need to be trained specically well for tasks.

2. How many of those 10 plots were embedded without truncation by each model? c) What is the max, min, and average word length of all your movie plots
  Tokenizing with Jina v3 (Encoder)
  
  Plot 1: 925 tokens (OK)
    Title: Absence of Malice
  Plot 2: 531 tokens (OK)
    Title: All Night Long
  Plot 3: 66 tokens (OK)
    Title: ...All the Marbles
  Plot 4: 68 tokens (OK)
    Title: The Amateur
  Plot 5: 997 tokens (OK)
    Title: American Pop
  Plot 6: 1083 tokens (OK)
    Title: An American Werewolf in London
  Plot 7: 127 tokens (OK)
    Title: Amy
  Plot 8: 588 tokens (OK)
    Title: Arthur
  Plot 9: 93 tokens (OK)
    Title: Back Roads
  Plot 10: 1172 tokens (OK)
    Title: Blow Out
  
  Summary: 10/10 plots embedded without truncation
  Truncation rate: 0.0%
  
  Tokenizing with Qwen3 (Decoder)
  
  Plot 1: 737 tokens (OK)
    Title: Absence of Malice
  Plot 2: 465 tokens (OK)
    Title: All Night Long
  Plot 3: 56 tokens (OK)
    Title: ...All the Marbles
  Plot 4: 56 tokens (OK)
    Title: The Amateur
  Plot 5: 838 tokens (OK)
    Title: American Pop
  Plot 6: 946 tokens (OK)
    Title: An American Werewolf in London
  Plot 7: 110 tokens (OK)
    Title: Amy
  Plot 8: 511 tokens (OK)
    Title: Arthur
  Plot 9: 82 tokens (OK)
    Title: Back Roads
  Plot 10: 965 tokens (OK)
    Title: Blow Out
  
  Summary: 10/10 plots embedded without truncation
  Truncation rate: 0.0%

  Total movies analyzed: 19994

  Word Count Statistics:
    Maximum: 6,752 words
    Minimum: 3 words
    Average: 425.0 words
  
  Approximate Token Count Statistics:
    Maximum: 8,777 tokens
    Minimum: 3 tokens
    Average: 552.0 tokens

Discuss if the models you chose are good options for embedding the movie plots in your dataset. If they are not, please choose another model or models.
  Both models resulted in no truncation

2a) How many vectors you have stored in your faiss vector database.
    19,994 vectors stored
2b) Describe the main types of exact and ANN algorithms in the FAISS library and how you can select them.

Approx vs Exact: Exact computes distances to every vector, takes longer but gets more accurate results

Exact Indexes: FlatL2: Euclidean distance FlatIP: Inner product

ANN: IVF: groups vecotrs into clusters, searches closest ones HNSW: builds graph, has skipped linked list + NSW for quick loop up PQ: Compresses vectors to save space IVF + PQ: hybrid of clustering + compression

Selection: Small: Flat medium: IVF Large: HNSW or hybrid


  3. Find the relevant and not-relevant results in the top 7 using both exact and approximate algorithms from faiss and for both embedding models
  Compute the precision in top 7.
  Compare precision of these results (exact and ANN) and the small and large embedding models with the results you got with best tf-idf and best Rocchio feedback algorithm.
  Comment on your results and the use of sentence embedding models for IR.

  Results Summary

  TF-IDF: 0.190

  BM25: 0.524

  Rocchio: 0.476

  Encoder (Jina): 0.690 average
      Flat: 0.619 | IVF: 0.762

  Decoder (Qwen3): 0.595 average
      Flat: 0.619 | IVF: 0.571

Query-Level Results

Query 1 (horror movies): Embeddings excelled with 0.857-1.000 precision vs. 0.429 for traditional methods.

Query 2 (romantic comedy): Decoder performed better (0.429-0.571) than encoder (0.143-0.286). Both beat TF-IDF's 0.000.

Query 3 (worst action): Highly variable. Encoder IVF achieved 1.000, decoder flat only 0.429.
Key Findings

Encoder outperformed the decoder based on precision. Encoder beating decoder is reasonable bc they are meant for understanding meaning in both directions while decoders are mainly for text generation. Encoder seemed to have out performed the other model types. Some reason alot of indian movies were selected.
Conclusion

Sentence embeddings provide better understandings then normal keyword based IR methods. They resulted with higher precision and overall embeddings are a strong upgrade for semantic search.



    
