# Team Members: Ryan Chen, Dylan, Brandon Sabillon 
# Description: Create a bag of words model from speeches
# Revision History:
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
# Name:            Date:          Comments:
# Ryan and Sabillon 11/24/23.      Created tables with pandas 


# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 




import pandas as pd
from utility import removePunc, getTokens, getTF, getFileNames

def main():
    file1, file2, file3, file4, file5 = getFileNames()

    speech1_name, speech2_name, speech3_name, speech4_name, speech5_name = '1981-Reagan', '1993-Clinton', '2001-Bush', '2009-Obama', '2017-Trump'

    txt_clean1 = removePunc(file1)
    txt_clean2 = removePunc(file2)
    txt_clean3 = removePunc(file3)
    txt_clean4 = removePunc(file4)
    txt_clean5 = removePunc(file5)

    unique_list = getTokens(txt_clean1 + ' ' + txt_clean2 + ' ' + txt_clean3 + ' ' + txt_clean4 + ' ' + txt_clean5)

    data = {}
    for name, text in zip([speech1_name, speech2_name, speech3_name, speech4_name, speech5_name], [txt_clean1, txt_clean2, txt_clean3, txt_clean4, txt_clean5]):
        data[name] = pd.Series(getTF(unique_list, text))

    df = pd.DataFrame(data).fillna(0)

    print(df)

# calling the main function to display the table
main()
