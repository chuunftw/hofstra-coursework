PART 0: 

1. There are 34886 movies in the dataset

2. There are 19994 movies in the post 1980 dataset

3. The 10 most frequent genres of movies are 
Genre
unknown      6083
drama        5964
comedy       4379
horror       1167
action       1098
thriller      966
romance       923
western       865
crime         568
adventure     526
Name: count, dtype: int64 

4.                    Title  Release Year  \
9796   Absence of Malice          1981   
9797      All Night Long          1981   
9798  ...All the Marbles          1981   

                                                   Plot          Genre  
9796  Miami liquor wholesaler Michael Gallagher (Pau...          drama  
9797  George Dupler (Gene Hackman), a married man ne...         comedy  
9798  Harry is the manager of a tag team of gorgeous...  comedy, drama   

5. Top 3 from Combined Column 
9796    Miami liquor wholesaler Michael Gallagher (Pau...
9797    George Dupler (Gene Hackman), a married man ne...
9798    Harry is the manager of a tag team of gorgeous...
dtype: object
------------------------------------------------------------------------------------------------------

PART 1: 
1. NLP steps: tokenization, lemmatization, stop word removal, Named Entity Recognition (NER)

2. Vocabulary size: 179862 terms

3. Most frequent 10 terms:
   find: 10802 docs
   leave: 9196 docs
   take: 8867 docs
   tell: 8202 docs
   friend: 8019 docs
   go: 7983 docs
   life: 7962 docs
   try: 7913 docs
   come: 7883 docs
   kill: 7787 docs

4. Least frequent 10 terms:
   axani: 1 docs
   reddit: 1 docs
   buzzfeed: 1 docs
   amy_tyler: 1 docs
   jordan_axani: 1 docs
   elizabeth_gallagher: 1 docs
   brendan_bradley: 1 docs
   soysal: 1 docs
   orhan_şahin: 1 docs
   deniz_soysal: 1 docs

5. After filtering (min_df=2, max_df=9997): 59808 terms left

Extracting entity examples...
6. Entity examples: ['merle webb', 'choke canyon.sci', 'the cycle lords', 'royal canadian mounted police', 'the sword of protection', 'david mendenhall', 'goth violet', 'anne osborne', 'robert morse', 'johnny steele']

7. Total unique multi-word entities found (from first 1000 docs): 6494
------------------------------------------------------------------------------------------------------------------------
PART 2: 
Query 1: scary movies to watch at night
Terms: ['scary', 'movie', 'watch', 'night']
Term frequencies: defaultdict(<class 'int'>, {'scary': 1, 'movie': 1, 'watch': 1, 'night': 1})
Terms in vocabulary:
  scary: found in 34 docs
  movie: found in 2435 docs
  watch: found in 2398 docs
  night: found in 4779 docs

Query 2: romantic comedy movies to watch for fun
Terms: ['romantic', 'comedy', 'movie', 'watch', 'fun']
Term frequencies: defaultdict(<class 'int'>, {'romantic': 1, 'comedy': 1, 'movie': 1, 'watch': 1, 'fun': 1})
Terms in vocabulary:
  romantic: found in 759 docs
  comedy: found in 1234 docs
  movie: found in 2435 docs
  watch: found in 2398 docs
  fun: found in 476 docs

Query 3: worst action movies of all time
Terms: ['bad', 'action', 'movie', 'time']
Term frequencies: defaultdict(<class 'int'>, {'bad': 1, 'action': 1, 'movie': 1, 'time': 1})
Terms in vocabulary:
  bad: found in 1588 docs
  action: found in 1656 docs
  movie: found in 2435 docs
  time: found in 7732 docs
---------------------------------------------------------------------------------------
PART 3: 
Query: scary movies to watch at night

TF-IDF Results:

Score: 357.33
Title: Dark Tales of Japan
Genre: horror
Plot: Introduction: Would You Like to Hear a Scary Tale? (Intorodakushon: Kowai hanashi, kikitai desu ka) Directed by Yoshihiro Nakamura; teleplay by Yoshihiro Nakamura and Katsuhide Suzuki
Plot: At a bus ...

Score: 235.25
Title: Winter
Genre: horror
Plot: Jayaram and Bhavana takes the lead roles as Dr. Ramdas and his wife in the film. Dr. Ramdas is leading medical practitioner in Hyderabad. Fed up with the fast-paced city life, Ramdas and his wife deci...

Score: 182.21
Title: Movie 43
Genre: comedy
Plot: Movie 43 is a series of different sketches containing different scenes and scenarios.
The film is composed of multiple comedy shorts presented through an overarching segment titled "The Pitch", in wh...

Score: 172.03
Title: Darna Zaroori Hai
Genre: horror
Plot: Darna Zaroori Hai interweaves six stories into one film. Five children get lost in the middle of a forest until they find a haunted house. Inside, there is an old woman who agrees to tell them six sca...

Score: 171.44
Title: 24
Genre: science fiction
Plot: Dr. Sethuraman (Suriya) is a reputed scientist and watchmaker who lives with his wife Priya (Nithya Menen) and newborn son Mani in a mansion with a laboratory at Megamalai. In January 1990, on his bir...

Score: 125.97
Title: Brigsby Bear
Genre: comedy, drama
Plot: James lives in an underground home with his parents Ted and April Mitchum. Forced to stay underground by his parents, James' only connection with the outside world is an educational children's show ca...

Score: 123.63
Title: Pooh's Heffalump Movie
Genre: animation
Plot: Winnie the Pooh and his friends hear a strange noise and find a set of large, circular footprints in the Hundred Acre Wood. During the night, Tigger's house is damaged by what appears to be an earthqu...


BM25 Results:

Score: 20.67
Title: Winter
Genre: horror
Plot: Jayaram and Bhavana takes the lead roles as Dr. Ramdas and his wife in the film. Dr. Ramdas is leading medical practitioner in Hyderabad. Fed up with the fast-paced city life, Ramdas and his wife deci...

Score: 20.18
Title: Dark Tales of Japan
Genre: horror
Plot: Introduction: Would You Like to Hear a Scary Tale? (Intorodakushon: Kowai hanashi, kikitai desu ka) Directed by Yoshihiro Nakamura; teleplay by Yoshihiro Nakamura and Katsuhide Suzuki
Plot: At a bus ...

Score: 16.31
Title: A Paying Ghost
Genre: comedy, love story, drama
Plot: [3] The movie, “Paying Ghost”, is based on a comedy fiction by renowned Marathi novelist, Late P. V. Kale. It picturizes typical life of a Mumbai resident and how a ghost helps him to overcome the cha...

Score: 16.00
Title: Whore
Genre: drama
Plot: Liz is a Los Angeles street prostitute. The audience first sees her attempting to get a customer on a busy downtown street near a tunnel. She addresses the audience directly on her life and problems t...

Score: 14.51
Title: Pooh's Heffalump Movie
Genre: animation
Plot: Winnie the Pooh and his friends hear a strange noise and find a set of large, circular footprints in the Hundred Acre Wood. During the night, Tigger's house is damaged by what appears to be an earthqu...

Score: 13.60
Title: Darna Zaroori Hai
Genre: horror
Plot: Darna Zaroori Hai interweaves six stories into one film. Five children get lost in the middle of a forest until they find a haunted house. Inside, there is an old woman who agrees to tell them six sca...

Score: 13.58
Title: Boys and Girls
Genre: short
Plot: The father of a girl is a fox farmer. He had silver foxes. In autumn and early winter, when their fur was good, he killed them and shaved their skins and sold them to the company. In winter, the famil...


Query: romantic comedy movies to watch for fun

TF-IDF Results:

Score: 233.79
Title: Movie 43
Genre: comedy
Plot: Movie 43 is a series of different sketches containing different scenes and scenarios.
The film is composed of multiple comedy shorts presented through an overarching segment titled "The Pitch", in wh...

Score: 165.53
Title: 24
Genre: science fiction
Plot: Dr. Sethuraman (Suriya) is a reputed scientist and watchmaker who lives with his wife Priya (Nithya Menen) and newborn son Mani in a mansion with a laboratory at Megamalai. In January 1990, on his bir...

Score: 144.30
Title: Heavyweights
Genre: comedy
Plot: As school ends for the summer, Gerry Garner (Aaron Schwartz) is sent by his parents to Camp Hope, a weight loss camp for boys. Despite worrying at first, Gerry makes friends easily at camp and learns ...

Score: 126.95
Title: Daddy's Home 2
Genre: comedy
Plot: After finally becoming friends at the end of the first film, Brad Whittaker and Dusty Mayron have a co-dad system where their two children, Megan and Dylan, take turns at each father's house. Dusty ha...

Score: 119.04
Title: Anbulla Rajinikanth
Genre: unknown
Plot: Rosy (Meena), a limb and left arm paralysed girl with weak cardiac health, lives at an orphanage (Karunai Illam) along with other orphans that were dumped by their parents forsaking due to disabilitie...

Score: 116.08
Title: Nine
Genre: musical
Plot: Guido Contini (Daniel Day-Lewis) is a gifted Italian filmmaker in 1965 at the famous Cinecittà movie studios in Rome. At the age of fifty he has developed writer's block and surrealistically summons a...

Score: 112.14
Title: Pinocchio
Genre: family
Plot: A magical log falls off a wagon and rolls through an Italian town causing considerable damage and some injuries. It comes to rest in front of the house of Geppetto, a poor wood carver who carves a pup...


BM25 Results:

Score: 20.97
Title: Rocket
Genre: action romance
Plot: The movie is a romantic comedy. The main lead of the movie, Rakesh (Sathish Ninasam), falls in love with Shwetha (Aishani Shetty), and goes through a romantic journey. He faces a lot of hurdles in the...

Score: 20.81
Title: Oyee
Genre: romantic comedy
Plot: The movie is based on 2004 South Korean romantic comedy Too Beautiful to Lie.[5]...

Score: 20.14
Title: Itazura na Kiss the Movie 2 ~Campus-Hen~
Genre: drama, romantic comedy
Plot: In this romantic comedy story, a high school girl named Kotoko Aihara finally tells a fellow senior named Naoki that she has loved him from afar since she saw him on their first day of high school. Ho...

Score: 20.14
Title: Itazura na Kiss the Movie 3 ~Proposal-Hen~
Genre: drama, romantic comedy
Plot: In this romantic comedy story, a high school girl named Kotoko Aihara finally tells a fellow senior named Naoki that she has loved him from afar since she saw him on their first day of high school. Ho...

Score: 20.10
Title: Itazura na Kiss the Movie ~High School-Hen~
Genre: drama, romantic comedy
Plot: In this romantic comedy story, a high school girl named Kotoko Aihara finally tells a fellow senior named Naoki that she has loved him from afar since she saw him on their first day of high school. Ho...

Score: 18.68
Title: Hyderabad Blues
Genre: social
Plot: The protagonist of Hyderabad Blues is Varun, played by the director, Nagesh Kukunoor. The movie revolves around his visit to his home after 12 years in the USA and his resulting culture shock. The mov...

Score: 17.83
Title: Mooru Guttu Ondu Sullu Ondu Nija
Genre: comedy
Plot: This is a less expensive comedy movies with the overall movie being shot in a single house. The movie starts with the family having four children with komal as eldest son and three girls. The overall ...


Query: worst action movies of all time

TF-IDF Results:

Score: 145.68
Title: Crayon Shin-chan: The Storm Called The Jungle
Genre: animated
Plot: Shin-chan and his parents including Shiro along with his friends and families go on a cruise to for several days to meet Action Mask (the actor). But a group of monkeys raid the ship and all the middl...

Score: 141.06
Title: Just My Luck
Genre: comedy
Plot: The film follows the life of lucky and popular Ashley Albright (Lindsay Lohan) who has an extremely fortunate life and is always experiencing remarkable strokes of luck in contrast to the life of unlu...

Score: 135.87
Title: The Flu
Genre: unknown
Plot: The opening scene shows a group of illegal immigrants that are being prepared to be smuggled to South Korea inside a shipping container. As they are about to be sent overseas, one of the traffickers n...

Score: 122.34
Title: Dhoondte Reh Jaaoge
Genre: comedy
Plot: Set in Mumbai, the film starts with Raj (Paresh Rawal), a good-for-nothing movie director who has released certain films, but none of them ever do well at the box office. He gets threatened by his lan...

Score: 119.29
Title: Crayon Shin-chan: The Storm Called: Operation Golden Spy
Genre: anime
Plot: A girl named Lemon suddenly appears. She shows Shin-chan a message which is sent from Shinnosuke's hero Action Mask. Shinnosuke totally believes Lemon and they start spy training together. They duo be...

Score: 109.86
Title: Movie 43
Genre: comedy
Plot: Movie 43 is a series of different sketches containing different scenes and scenarios.
The film is composed of multiple comedy shorts presented through an overarching segment titled "The Pitch", in wh...

Score: 102.67
Title: In Time
Genre: science fiction, thriller
Plot: In 2169, people are genetically engineered to stop aging on their 25th birthday. Everyone then develops a countdown on their forearm set for a year. When the clock reaches zero, that person "times out...


BM25 Results:

Score: 17.28
Title: Doubles
Genre: unknown
Plot: The movie starts projecting Prabhu (Prabhu Deva) as a Shop Keeper who sells toys to kids. He will be wearing a Mask which is similar to his face and he will be wearing that mask on the backside of his...

Score: 15.81
Title: Varsham
Genre: romance/action
Plot: Venkat (Prabhas), an unemployed youngster meets Shailaja (Trisha), a middle-class beauty in a train journey and they immediately get attracted to each other after dancing in a rain shower. At the same...

Score: 14.64
Title: Tulkalam
Genre: romance
Plot: Tulkalam is a political action film, it is based on land scam in West Bengal. It is an all-time record blockbuster hit movie in the Bengali film industry.[citation needed]...

Score: 14.37
Title: Land of the Blind
Genre: drama
Plot: Hollander plays Maximilian II (often called Junior), the ignorant, vindictive and petulant ruler of a troubled (but unnamed) country. Maximilian has two main interests: enjoying himself and running hi...

Score: 14.23
Title: Vedi
Genre: action-masala
Plot: Vedi tells the story of Prabhakaran (Vishal), a young police officer, who goes to Kolkata in search of his sister, Aishwarya (Poonam Kaur). Prabhakaran, at his native place, Thoothukudi, had developed...

Score: 13.82
Title: I. G.
Genre: action, thriller
Plot: IG is an action movie which Suresh Gopi dons the role of I.G. Durga Prasad. He is the head of Traffic Police. One day during his duty time he takes into custody a gang of criminals who involved in haw...

Score: 13.62
Title: Crayon Shin-chan: The Storm Called The Jungle
Genre: animated
Plot: Shin-chan and his parents including Shiro along with his friends and families go on a cruise to for several days to meet Action Mask (the actor). But a group of monkeys raid the ship and all the middl...
---------------------------------------------------------------------------------------
Part 4: 

--- Processing Query 1: 'scary movies to watch at night' ---

Assessing relevance for query: 'scary movies to watch at night' using TF-IDF

Result 1 (Doc ID: 18567, Score: 357.3258)
Title: Dark Tales of Japan
Genre: horror
Plot: Introduction: Would You Like to Hear a Scary Tale? (Intorodakushon: Kowai hanashi, kikitai desu ka) Directed by Yoshihiro Nakamura; teleplay by Yoshihiro Nakamura and Katsuhide Suzuki
Plot: At a bus ...
Is this document relevant? (yes/no): yes

Result 2 (Doc ID: 14563, Score: 235.2495)
Title: Winter
Genre: horror
Plot: Jayaram and Bhavana takes the lead roles as Dr. Ramdas and his wife in the film. Dr. Ramdas is leading medical practitioner in Hyderabad. Fed up with the fast-paced city life, Ramdas and his wife deci...
Is this document relevant? (yes/no): yes

Result 3 (Doc ID: 6820, Score: 182.2122)
Title: Movie 43
Genre: comedy
Plot: Movie 43 is a series of different sketches containing different scenes and scenarios.
The film is composed of multiple comedy shorts presented through an overarching segment titled "The Pitch", in wh...
Is this document relevant? (yes/no): no

Result 4 (Doc ID: 12903, Score: 172.0296)
Title: Darna Zaroori Hai
Genre: horror
Plot: Darna Zaroori Hai interweaves six stories into one film. Five children get lost in the middle of a forest until they find a haunted house. Inside, there is an old woman who agrees to tell them six sca...
Is this document relevant? (yes/no): yes

Result 5 (Doc ID: 17148, Score: 171.4404)
Title: 24
Genre: science fiction
Plot: Dr. Sethuraman (Suriya) is a reputed scientist and watchmaker who lives with his wife Priya (Nithya Menen) and newborn son Mani in a mansion with a laboratory at Megamalai. In January 1990, on his bir...
Is this document relevant? (yes/no): no

Result 6 (Doc ID: 7485, Score: 125.9678)
Title: Brigsby Bear
Genre: comedy, drama
Plot: James lives in an underground home with his parents Ted and April Mitchum. Forced to stay underground by his parents, James' only connection with the outside world is an educational children's show ca...
Is this document relevant? (yes/no): no

Result 7 (Doc ID: 4940, Score: 123.6300)
Title: Pooh's Heffalump Movie
Genre: animation
Plot: Winnie the Pooh and his friends hear a strange noise and find a set of large, circular footprints in the Hundred Acre Wood. During the night, Tigger's house is damaged by what appears to be an earthqu...
Is this document relevant? (yes/no): no

Top 7 Precision for query 'scary movies to watch at night' (TF-IDF): 0.4286

Assessing relevance for query: 'scary movies to watch at night' using BM25

Result 1 (Doc ID: 14563, Score: 20.6704)
Title: Winter
Genre: horror
Plot: Jayaram and Bhavana takes the lead roles as Dr. Ramdas and his wife in the film. Dr. Ramdas is leading medical practitioner in Hyderabad. Fed up with the fast-paced city life, Ramdas and his wife deci...
Is this document relevant? (yes/no): yes

Result 2 (Doc ID: 18567, Score: 20.1756)
Title: Dark Tales of Japan
Genre: horror
Plot: Introduction: Would You Like to Hear a Scary Tale? (Intorodakushon: Kowai hanashi, kikitai desu ka) Directed by Yoshihiro Nakamura; teleplay by Yoshihiro Nakamura and Katsuhide Suzuki
Plot: At a bus ...
Is this document relevant? (yes/no): yes

Result 3 (Doc ID: 15244, Score: 16.3128)
Title: A Paying Ghost
Genre: comedy, love story, drama
Plot: [3] The movie, “Paying Ghost”, is based on a comedy fiction by renowned Marathi novelist, Late P. V. Kale. It picturizes typical life of a Mumbai resident and how a ghost helps him to overcome the cha...
Is this document relevant? (yes/no): no

Result 4 (Doc ID: 1950, Score: 15.9989)
Title: Whore
Genre: drama
Plot: Liz is a Los Angeles street prostitute. The audience first sees her attempting to get a customer on a busy downtown street near a tunnel. She addresses the audience directly on her life and problems t...
Is this document relevant? (yes/no): no

Result 5 (Doc ID: 4940, Score: 14.5124)
Title: Pooh's Heffalump Movie
Genre: animation
Plot: Winnie the Pooh and his friends hear a strange noise and find a set of large, circular footprints in the Hundred Acre Wood. During the night, Tigger's house is damaged by what appears to be an earthqu...
Is this document relevant? (yes/no): no

Result 6 (Doc ID: 12903, Score: 13.6025)
Title: Darna Zaroori Hai
Genre: horror
Plot: Darna Zaroori Hai interweaves six stories into one film. Five children get lost in the middle of a forest until they find a haunted house. Inside, there is an old woman who agrees to tell them six sca...
Is this document relevant? (yes/no): yes

Result 7 (Doc ID: 9517, Score: 13.5797)
Title: Boys and Girls
Genre: short
Plot: The father of a girl is a fox farmer. He had silver foxes. In autumn and early winter, when their fur was good, he killed them and shaved their skins and sold them to the company. In winter, the famil...
Is this document relevant? (yes/no): no

Top 7 Precision for query 'scary movies to watch at night' (BM25): 0.4286

--- Processing Query 2: 'romantic comedy movies to watch for fun' ---

Assessing relevance for query: 'romantic comedy movies to watch for fun' using TF-IDF

Result 1 (Doc ID: 6820, Score: 233.7851)
Title: Movie 43
Genre: comedy
Plot: Movie 43 is a series of different sketches containing different scenes and scenarios.
The film is composed of multiple comedy shorts presented through an overarching segment titled "The Pitch", in wh...
Is this document relevant? (yes/no): no

Result 2 (Doc ID: 17148, Score: 165.5304)
Title: 24
Genre: science fiction
Plot: Dr. Sethuraman (Suriya) is a reputed scientist and watchmaker who lives with his wife Priya (Nithya Menen) and newborn son Mani in a mansion with a laboratory at Megamalai. In January 1990, on his bir...
Is this document relevant? (yes/no): no

Result 3 (Doc ID: 2659, Score: 144.2994)
Title: Heavyweights
Genre: comedy
Plot: As school ends for the summer, Gerry Garner (Aaron Schwartz) is sent by his parents to Camp Hope, a weight loss camp for boys. Despite worrying at first, Gerry makes friends easily at camp and learns ...
Is this document relevant? (yes/no): no

Result 4 (Doc ID: 7549, Score: 126.9543)
Title: Daddy's Home 2
Genre: comedy
Plot: After finally becoming friends at the end of the first film, Brad Whittaker and Dusty Mayron have a co-dad system where their two children, Megan and Dylan, take turns at each father's house. Dusty ha...
Is this document relevant? (yes/no): no

Result 5 (Doc ID: 15449, Score: 119.0356)
Title: Anbulla Rajinikanth
Genre: unknown
Plot: Rosy (Meena), a limb and left arm paralysed girl with weak cardiac health, lives at an orphanage (Karunai Illam) along with other orphans that were dumped by their parents forsaking due to disabilitie...
Is this document relevant? (yes/no): no

Result 6 (Doc ID: 5913, Score: 116.0827)
Title: Nine
Genre: musical
Plot: Guido Contini (Daniel Day-Lewis) is a gifted Italian filmmaker in 1965 at the famous Cinecittà movie studios in Rome. At the age of fifty he has developed writer's block and surrealistically summons a...
Is this document relevant? (yes/no): no

Result 7 (Doc ID: 4320, Score: 112.1353)
Title: Pinocchio
Genre: family
Plot: A magical log falls off a wagon and rolls through an Italian town causing considerable damage and some injuries. It comes to rest in front of the house of Geppetto, a poor wood carver who carves a pup...
Is this document relevant? (yes/no): no

Top 7 Precision for query 'romantic comedy movies to watch for fun' (TF-IDF): 0.0000

Assessing relevance for query: 'romantic comedy movies to watch for fun' using BM25

Result 1 (Doc ID: 14012, Score: 20.9696)
Title: Rocket
Genre: action romance
Plot: The movie is a romantic comedy. The main lead of the movie, Rakesh (Sathish Ninasam), falls in love with Shwetha (Aishani Shetty), and goes through a romantic journey. He faces a lot of hurdles in the...
Is this document relevant? (yes/no): yes

Result 2 (Doc ID: 17143, Score: 20.8085)
Title: Oyee
Genre: romantic comedy
Plot: The movie is based on 2004 South Korean romantic comedy Too Beautiful to Lie.[5]...
Is this document relevant? (yes/no): yes

Result 3 (Doc ID: 19077, Score: 20.1402)
Title: Itazura na Kiss the Movie 2 ~Campus-Hen~
Genre: drama, romantic comedy
Plot: In this romantic comedy story, a high school girl named Kotoko Aihara finally tells a fellow senior named Naoki that she has loved him from afar since she saw him on their first day of high school. Ho...
Is this document relevant? (yes/no): yes

Result 4 (Doc ID: 19146, Score: 20.1402)
Title: Itazura na Kiss the Movie 3 ~Proposal-Hen~
Genre: drama, romantic comedy
Plot: In this romantic comedy story, a high school girl named Kotoko Aihara finally tells a fellow senior named Naoki that she has loved him from afar since she saw him on their first day of high school. Ho...
Is this document relevant? (yes/no): yes

Result 5 (Doc ID: 19064, Score: 20.1029)
Title: Itazura na Kiss the Movie ~High School-Hen~
Genre: drama, romantic comedy
Plot: In this romantic comedy story, a high school girl named Kotoko Aihara finally tells a fellow senior named Naoki that she has loved him from afar since she saw him on their first day of high school. Ho...
Is this document relevant? (yes/no): yes

Result 6 (Doc ID: 12483, Score: 18.6792)
Title: Hyderabad Blues
Genre: social
Plot: The protagonist of Hyderabad Blues is Varun, played by the director, Nagesh Kukunoor. The movie revolves around his visit to his home after 12 years in the USA and his resulting culture shock. The mov...
Is this document relevant? (yes/no): no

Result 7 (Doc ID: 13858, Score: 17.8346)
Title: Mooru Guttu Ondu Sullu Ondu Nija
Genre: comedy
Plot: This is a less expensive comedy movies with the overall movie being shot in a single house. The movie starts with the family having four children with komal as eldest son and three girls. The overall ...
Is this document relevant? (yes/no): no

Top 7 Precision for query 'romantic comedy movies to watch for fun' (BM25): 0.7143

--- Processing Query 3: 'worst action movies of all time' ---

Assessing relevance for query: 'worst action movies of all time' using TF-IDF

Result 1 (Doc ID: 18478, Score: 145.6762)
Title: Crayon Shin-chan: The Storm Called The Jungle
Genre: animated
Plot: Shin-chan and his parents including Shiro along with his friends and families go on a cruise to for several days to meet Action Mask (the actor). But a group of monkeys raid the ship and all the middl...
Is this document relevant? (yes/no): no

Result 2 (Doc ID: 5174, Score: 141.0570)
Title: Just My Luck
Genre: comedy
Plot: The film follows the life of lucky and popular Ashley Albright (Lindsay Lohan) who has an extremely fortunate life and is always experiencing remarkable strokes of luck in contrast to the life of unlu...
Is this document relevant? (yes/no): no

Result 3 (Doc ID: 19714, Score: 135.8698)
Title: The Flu
Genre: unknown
Plot: The opening scene shows a group of illegal immigrants that are being prepared to be smuggled to South Korea inside a shipping container. As they are about to be sent overseas, one of the traffickers n...
Is this document relevant? (yes/no): no

Result 4 (Doc ID: 13092, Score: 122.3399)
Title: Dhoondte Reh Jaaoge
Genre: comedy
Plot: Set in Mumbai, the film starts with Raj (Paresh Rawal), a good-for-nothing movie director who has released certain films, but none of them ever do well at the box office. He gets threatened by his lan...
Is this document relevant? (yes/no): no

Result 5 (Doc ID: 18800, Score: 119.2924)
Title: Crayon Shin-chan: The Storm Called: Operation Golden Spy
Genre: anime
Plot: A girl named Lemon suddenly appears. She shows Shin-chan a message which is sent from Shinnosuke's hero Action Mask. Shinnosuke totally believes Lemon and they start spy training together. They duo be...
Is this document relevant? (yes/no): yes

Result 6 (Doc ID: 6820, Score: 109.8622)
Title: Movie 43
Genre: comedy
Plot: Movie 43 is a series of different sketches containing different scenes and scenarios.
The film is composed of multiple comedy shorts presented through an overarching segment titled "The Pitch", in wh...
Is this document relevant? (yes/no): no

Result 7 (Doc ID: 6257, Score: 102.6660)
Title: In Time
Genre: science fiction, thriller
Plot: In 2169, people are genetically engineered to stop aging on their 25th birthday. Everyone then develops a countdown on their forearm set for a year. When the clock reaches zero, that person "times out...
Is this document relevant? (yes/no): no

Top 7 Precision for query 'worst action movies of all time' (TF-IDF): 0.1429

Assessing relevance for query: 'worst action movies of all time' using BM25

Result 1 (Doc ID: 16146, Score: 17.2804)
Title: Doubles
Genre: unknown
Plot: The movie starts projecting Prabhu (Prabhu Deva) as a Shop Keeper who sells toys to kids. He will be wearing a Mask which is similar to his face and he will be wearing that mask on the backside of his...
Is this document relevant? (yes/no): no

Result 2 (Doc ID: 17630, Score: 15.8101)
Title: Varsham
Genre: romance/action
Plot: Venkat (Prabhas), an unemployed youngster meets Shailaja (Trisha), a middle-class beauty in a train journey and they immediately get attracted to each other after dancing in a rain shower. At the same...
Is this document relevant? (yes/no): no

Result 3 (Doc ID: 11467, Score: 14.6408)
Title: Tulkalam
Genre: romance
Plot: Tulkalam is a political action film, it is based on land scam in West Bengal. It is an all-time record blockbuster hit movie in the Bengali film industry.[citation needed]...
Is this document relevant? (yes/no): no

Result 4 (Doc ID: 5180, Score: 14.3689)
Title: Land of the Blind
Genre: drama
Plot: Hollander plays Maximilian II (often called Junior), the ignorant, vindictive and petulant ruler of a troubled (but unnamed) country. Maximilian has two main interests: enjoying himself and running hi...
Is this document relevant? (yes/no): no

Result 5 (Doc ID: 16860, Score: 14.2284)
Title: Vedi
Genre: action-masala
Plot: Vedi tells the story of Prabhakaran (Vishal), a young police officer, who goes to Kolkata in search of his sister, Aishwarya (Poonam Kaur). Prabhakaran, at his native place, Thoothukudi, had developed...
Is this document relevant? (yes/no): yes

Result 6 (Doc ID: 14546, Score: 13.8219)
Title: I. G.
Genre: action, thriller
Plot: IG is an action movie which Suresh Gopi dons the role of I.G. Durga Prasad. He is the head of Traffic Police. One day during his duty time he takes into custody a gang of criminals who involved in haw...
Is this document relevant? (yes/no): yes

Result 7 (Doc ID: 18478, Score: 13.6211)
Title: Crayon Shin-chan: The Storm Called The Jungle
Genre: animated
Plot: Shin-chan and his parents including Shiro along with his friends and families go on a cruise to for several days to meet Action Mask (the actor). But a group of monkeys raid the ship and all the middl...
Is this document relevant? (yes/no): yes

Top 7 Precision for query 'worst action movies of all time' (BM25): 0.4286

---------------------------------------------------------------------------------------
PART 5: 
**Comparing TF-IDF and BM25 Precision Results**

After running the code cell and manually judging the relevance of the top 7 results for each query and similarity function, you will have the top 7 precision score for each combination. Use these scores to compare the performance of the standard TF-IDF and BM25 methods.


1.  State the Precision Values:

  Query 1 ("scary movies to watch at night"): TF-IDF Precision = 0.4286, BM25 Precision = 0.4286

  Query 2 ("romantic comedy movies to watch for fun"): TF-IDF Precision = 0.0000, BM25 Precision = 0.7143

  Query 3 ("worst action movies of all time"): TF-IDF Precision = 0.1429, BM25 Precision = 0.4286

2.  Direct Comparison:

  Query 1, both methods performed equally, this leads us to believe that when the dataset matches the horror theme, both methods retunr similar results. Query 2 however resulted in a major difference where TF-IDF failed to retrieve relevant romantic comedies while BM25 resulted in a much higher score of 0.7143. For Query 3, BM25 once again outperformed TF-IDF, resulting more relevant action films with a precision of .0.4286 while TF-IDF resulted in 0.1429.

3.   Reasons for Differences/conclusion:

These results demonstrate that although TF-IDF and BMD25 can be compared when query is simple, BM25 overall outperforms retrieval when relevance depends on more refined rankings. BM25's edge in Query 2 depicts its higher strength in retrieval, overweighting popular terms so that i can rank highly where the "romantic" element counts as much as teh "comedy" one. 

Overall, BM25 slightly outperformed TF-IDF in this experiment, particularly for queries requiring more refined ranking of relevance. The differences can be attributed to BM25’s ability to balance term frequency without overweighting repeated terms, making it better suited for capturing meaningful results in queries with less direct matches. In contrast, TF-IDF may struggle with cases where raw term frequency skews the relevance ranking.

