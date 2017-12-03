NOTE: 2nd revision as of 11/30/2017 11AM. Revisions:
	1. No longer replacing 2 character words with their exceptions (am -> be)

NOTE: this is revised as of 11/25/2017 2PM. Revisions:
	1. The previous correct output was wrong, 
	2. there was a small bug that effected wordlists but did not affect the final output or counts that has been corrected, and 
	3. the similarity scores for the three files in the reading range were added to their count files. Other sim scores were not necessary to calculate.

All input files are in the in/ folder. The following commands were used.

***VALID TAR: 5 pts***
***VALID MAKE: 5 pts***

***VALID CASE #1: 70 pts***

input:
./PA8 in/reference in/library 1 6.85 

output:
/s/chopin/b/grad/dwhite54/cs253/PA8/Test_Cases/in/tamingshrew

return value: 
0

***INVALID CASE #1: 5 pts***

input:
./PA8 in/reference in/library 

output:
<any>

return value:
-1


***INVALID CASE #2: 5 pts***

input:
./PA8 in/reference in/library2 1 6.85

output:
<any>

return value:
-1


***INVALID CASE #1: 5 pts***

input:
./PA8 in/reference in/library3 1 6.85

output:
<any>

return value:
-1


***INVALID CASE #1: 5 pts***

input:
./PA8 in/reference in/doesnotexist 1 6.85

output:
<any>

return value:
-1
