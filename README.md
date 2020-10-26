# C-project-for-my-university
This is my first big project in C for university purposes.

Make a program that reads texts from the user and analyzes them in
words, sentences and paragraphs.
• One word consists of 1 or more consecutive Latin letters
(lowercase and/or uppercase)
• One sentence consists of 1 or more words (separated by spaces
or other characters) ending with . Or! Or? Or?
• One paragraph consists of 1 or more sentences
end with a line break character.
The program will constantly request commands from the user until it accepts the "qt" command
which terminates the program.
The commands he can accept are:

• "ap:" After this command the program should read a
paragraph (with a maximum length of 10000 characters) to analyse it in
sentences and words and store it in appropriate structures in memory.
• "fw:" After this command the program should read a
string (with a maximum length of 10000 characters) and display the words
containing the specific string within them. Note: The
program should display only once each word (even if
repeated in the text). See the examples in eagle
• "fs:" After this command the program should read a
string (with a maximum length of 10000 characters) and display the
sentences that contain the specific string within them.
Note: In the appearance of the proposals, the programme should be
displays the words in the correct order (separated by just one space) and
then a line break character. The other characters that may be
given by the user will not be displayed. See the examples in eagle
• "fp:" After this command the program should read a
string (with a maximum length of 10000 characters) and display the
paragraphs containing the specific string within them.
Note: When displaying paragraphs, the program should
displays all the sentences in this paragraph in accordance with the
Previous. See the examples in eagle
• "owf" The program should display all the words in the text (each
word will only appear once) sorted in descending order based on
the display number of each word in the text. In case 2 words
have the same incidence to be classified by ascending
dictionary order (first uppercase after lowercase). Every word should be
be displayed with its display number within [] (e.g. the [3],
if the word the was 3 times in the text)
• "owl" The program should display all the words in the text (each
word will appear only once) sorted in ascending order based on
the length of each word. In case 2 words are the same length as
classified in ascending lexicographic order (first the uppercase after the
lowercase). Each word should appear along with its length within [] (e.g.
Graham [6], as the word is 6 letters long)
• "qt" The program should shut down.

Note: The program will run in an environment with limited
resources in memory (stack) so you should use as much as possible
more dynamic memory management and avoid static
Tables
