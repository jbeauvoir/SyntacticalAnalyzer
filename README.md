READ_ME 

Whenever you make changes to ANY file checkout the read-me branch and update the readme
,otherwise I have to review all your code to see what changes you made. Always document
with comments for things you believe the other person might not understand. Remember to 
leave out any comments that output to the commandline. 



Git Notes:
- Name branches based on what you worked on. It's harder to know what your branch does
  when you name something as an abbreviation. Examples of appropriate branch names:
  read-me, error-checks, variable-changes, etc.

- make clean before commiting any changes. failure to make clean will
  result in extra "~" files in the repsository

Merging:

The merge order 
1. logic-corrections
2. error-checking
3. re-organize
4. read-me


Tasks: 
- Which branch was the EOF issue corrected in?
      -> is the eof error not there because I commented out output there 
- delete the "lexeme is " in the debugger output 
- modify the <non-terminal> name from lowercase to capitol 
      ex - define -> Define
      
      

Completed Tasks: 
- makefile was modified to compile using our group letter P
- run "make submit" in the command line which auto submits to 
  the dropbox
- look at the differences between expected output and ours, making changes 
  where necessary
