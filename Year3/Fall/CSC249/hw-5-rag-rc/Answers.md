### 1.A. What are the top 3 most relevant movie plots ranked by the cross-encoders from the top 7 retrieved? Are they the most relevant to your query or not? If not, please propose a change that would improve the results.

#### Query 1: "scary movies to watch at night"

**Top 3 Movies:**
1. **Terror in the Aisles (1984)** - Score: 0.4486
2. **They (2002)** - Score: -3.7257
3. **Tales from the Darkside: The Movie (1990)** - Score: -5.1163

**Relevance Assessment:**

The results are **partially relevant**. "Terror in the Aisles" (the only movie with a positive score) is highly relevant as it's a documentary compilation of horror film clips specifically designed to showcase terror and suspense - perfect for scary movie night. "They" is also relevant as it's a horror film about night terrors and mysterious creatures. "Tales from the Darkside: The Movie" is a horror anthology that would also be appropriate for the query. However, all scores except the top movie are negative, which suggests the cross-encoder struggled with matching the casual query language ("scary movies to watch at night") with formal plot descriptions.

---

#### Query 2: "romantic comedy movies to watch for fun"

**Top 3 Movies:**
1. **Premsutra (2013)** - Score: 1.9802
2. **Lal Dupatta Malmal Ka (1989)** - Score: -1.5507
3. **Manasina Maathu (2011)** - Score: -1.9201

**Relevance Assessment:**

The results are **relevant**. "Premsutra" scored highly positive and is explicitly described as "a fun ride in the world of romance" which directly matches the query intent. "Lal Dupatta Malmal Ka" is a romantic drama, and "Manasina Maathu" is described as "family entertaining romantic story." All three movies fit the romantic comedy/fun genre requested.

---

#### Query 3: "worst action movies of all time"

**Top 3 Movies:**
1. **Laparwah (1981)** - Score: -3.3183
2. **Boxer (1984)** - Score: -6.0934
3. **The Hitman (1991)** - Score: -6.7712

**Relevance Assessment:**

The results arent good. All scores are significantly negative, which is expected since the query asks for "worst" movies - a negative sentiment the cross-encoder may interpret as low relevance. However, these are all action movies, so they meet the genre requirement. The issue is that the plot descriptions don't contain quality indicators (reviews, ratings, or mentions of being "bad"), making it impossible to determine if they are actually among the worst. The cross-encoder simply selected action movies but cannot determine quality from plot summaries alone.

---

### Proposed Improvements:

**For Query 3 (Worst Action Movies):**

The main issue is that movie plot summaries don't contain quality/rating information. To improve results for queries about movie quality ("worst," "best"), we would need to:

1. **Augment the dataset with external ratings** (IMDB, Rotten Tomatoes)
2. **Include review snippets or critic descriptions** in the searchable text
3. **Reformulate the query** to focus on action movie characteristics rather than quality (e.g., "action movies with over-the-top plots")

**Implemented Change:**

Since we cannot modify the dataset, I propose reformulating quality-based queries to focus on genre characteristics instead. For example, changing "worst action movies" to "intense action movies" or "action thriller movies" would produce more meaningfully ranked results based on plot content rather than subjective quality.

**General Improvement:**

The chunking strategy with `max_chunk_size=400` and taking the maximum score across chunks works well for handling long plots that exceed the 512 token limit of the cross-encoder model.

---

### 1.B. What issues did you encounter and how did you solve them?

Token Limit Exceeded

**Problem:** The cross-encoder model (cross-encoder/ms-marco-MiniLM-L-6-v2) has a maximum input size of 512 tokens. Many movie plots, when combined with the query and special tokens ([CLS], [SEP]), exceeded this limit, causing errors or truncation.

**Solution:** Implemented a `chunk_text()` function that:
- Uses NLTK's `sent_tokenize()` to split plots into sentences
- Builds chunks by adding sentences one at a time until approaching the `max_chunk_size=400` token limit
- Includes overlap between chunks (last sentence of previous chunk starts the next chunk) to maintain context
- Ensures no chunk exceeds the token limit by testing with the tokenizer before adding each sentence

The `get_relevance_score()` function then:
- Generates a relevance score for each chunk
- Returns the **maximum score** across all chunks, assuming the most relevant section best represents the movie's relevance to the query

---

### 2.A. What is the context size for the small and for the large model you chose? How did you formulate the prompt to the LLM such that it will not exceed the size of the context window?

**Context Window Sizes:**

- **TinyLlama (TinyLlama-1.1B-Chat-v1.0)**: The context window size for TinyLlama is typically **2048 tokens**
- **Mistral-7B-Instruct-v0.2**: The context window size for Mistral-7B-Instruct-v0.2 is **32,000 tokens**

**Prompt Formulation Strategy:**

To ensure the prompt did not exceed the context window size, especially for TinyLlama, I implemented the following strategies:

1. **Limiting Input Movies**: Only the top 3 most relevant movies (along with their titles, years, and plots) from the cross-encoder reranking were passed to the LLMs for each query. This reduced the amount of text in the input prompt.

2. **Concise Prompt Structure**: The `create_prompt` function was designed to be straightforward, including only the most important information: the query and the movie details, minimizing unnecessary conversational overhead.

3. **`max_new_tokens` Parameter**: During generation, the `max_new_tokens` parameter was set to `200`. While this primarily controls the *output* length, it also implicitly prevents the overall sequence (input + output) from growing excessively, especially for the smaller model, ensuring that the model doesn't try to generate an output that would push the total token count beyond its effective operational limit or lead to very long, potentially repetitive, generations.

---

### 2.B. What is the generated output for each of the queries using the small and the big models? Comment on the results you obtained.

#### Query 1: "scary movies to watch at night"

**TinyLlama Response:**

TinyLlama's output was complete gibberish after the initial prompt. The model generated nonsensical text with random words like "hall," "motion," "horror," "live," etc., repeated in various combinations without any coherent meaning or sentence structure.

**Mistral-7B Response:**

"Based on the query 'scary movies to watch at night,' I would recommend 'They' as it is a horror movie that focuses on the theme of night terrors and mysterious creatures that only the protagonist can see. The movie explores the idea of the protagonist's perception of reality being questioned and the fear of being consumed by the creatures. The suspense and terror elements in the movie are sure to keep the viewer engaged and on edge, making it an excellent choice for a scary movie to watch at night."

---

#### Query 2: "romantic comedy movies to watch for fun"

**TinyLlama Response:**

"Based on the query, I would recommend 'Lal Dupatta Malmal Ka' as it has a romantic drama theme and is a fun ride in the world of romance. The film is directed by Santosh Sivan and stars Shruti Haasan and Randeep Hooda. The plot revolves around the family entertaining romantic story. It's a great choice for a romantic comedy movie to watch for fun."

**Mistral-7B Response:**

"Based on the query, I would recommend the movie 'Premsutra' (2013) as it is a romantic comedy and is specifically mentioned as a fun ride in the world of romance."

---

#### Query 3: "worst action movies of all time"

**TinyLlama Response:**

"Given the plot, I would recommend 'The Hitman' by Chuck Norris. It is an action-packed thriller with a great plot, memorable characters, and an intense climax that will leave you on the edge of your seat. The movie also has a great soundtrack and a strong sense of style, making it a standout in the genre."

**Mistral-7B Response:**

"Based on the query for worst action movies of all time, my recommendation would be Laparwah (1981). While The Hitman (1991) is also an action film, it has a more complex plot and better production values, making it less likely to be considered one of the worst action movies of all time. Laparwah, on the other hand, is an out-and-out action film with no notable redeeming qualities, making it a strong contender for the worst action movie title."

---

### Comments on Results:

**TinyLlama (Small Model):**

- For "scary movies to watch at night", TinyLlama's output was **gibberish** after the initial prompt. This indicates a significant struggle with generating coherent text even with a relatively short input due to its smaller size and the complexity of the task (summarizing and recommending from provided plots).

- For "romantic comedy movies to watch for fun", TinyLlama recommended "Lal Dupatta Malmal Ka" and provided a generic explanation, **incorrectly attributing the director and cast**. It struggled to synthesize information directly from the provided plot, which was also quite brief.

- For "worst action movies of all time", TinyLlama surprisingly recommended "The Hitman" and **praised it** as an "action-packed thriller with a great plot," **completely missing the "worst" aspect** of the query. This highlights its difficulty in understanding nuanced instructions and sentiment.

**Mistral-7B (Large Model):**

- For "scary movies to watch at night", Mistral-7B successfully recommended "They" and provided a **coherent, relevant explanation** directly from the movie's plot, demonstrating a good understanding of the query and the provided text.

- For "romantic comedy movies to watch for fun", Mistral-7B recommended "Premsutra" and justified its choice by citing that the movie is described as a "fun ride in the world of romance" in its plot. This shows **better extraction and reasoning** compared to TinyLlama.

- For "worst action movies of all time", Mistral-7B **correctly identified** "Laparwah" as the most suitable recommendation for the "worst" category, by contrasting its lack of notable qualities with "The Hitman"'s more complex plot. This demonstrates a much stronger ability to interpret the negative connotation of the query and reason across the provided movie plots.

**Overall Comparison:**

The larger Mistral-7B model consistently provided much more coherent, relevant, and accurate recommendations with logical justifications based on the provided plots. TinyLlama, due to its significantly smaller size, struggled with coherence, factual accuracy, and correctly interpreting the query's intent, often generating irrelevant or contradictory responses. This clearly illustrates the advantage of larger, more capable models for complex reasoning and generation tasks.

---

### 2.C. Does changing the max_size of the generated output, and/or the temperature improve or not the answers?

Changing `max_new_tokens` and `temperature` can significantly influence the quality and characteristics of the generated answers:

#### `max_new_tokens` (Controls Output Length):

**Increasing `max_new_tokens`:**

Allowing the model to generate more tokens can be beneficial if the current output is too brief or cuts off useful information. For instance, if a recommendation's explanation is truncated, increasing this value could lead to a more complete and informative answer. 

However, if set too high, especially for smaller models, it can lead to repetitive, verbose, or irrelevant text, as the model might struggle to maintain coherence over longer generations. For models like TinyLlama, a high `max_new_tokens` can easily result in gibberish or off-topic content.

**Decreasing `max_new_tokens`:**

A lower value forces conciseness. This can be useful for tasks requiring short, direct answers but might sacrifice detail or depth. If the generated explanations are too long and dilute the main point, reducing `max_new_tokens` could improve clarity.

---

#### `temperature` (Controls Randomness/Creativity):

**Increasing `temperature` (e.g., from 0.7 to 1.0 or higher):**

A higher temperature makes the output more random, diverse, and creative. This can be beneficial when you want the model to explore different phrasings or perspectives, especially for creative tasks like storytelling. However, for fact-based recommendations like in this lab, increased randomness can lead to hallucinations, factual errors, or incoherent responses.

**Decreasing `temperature` (e.g., from 0.7 to 0.3 or lower):**

A lower temperature makes the output more deterministic and focused, as the model tends to choose the most probable tokens. This typically results in more consistent, factual, and coherent responses. For recommendation tasks where accuracy and relevance are crucial, a lower temperature is generally preferable as it reduces the likelihood of the model making things up or straying from the provided information.

---
