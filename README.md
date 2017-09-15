# ZodiacKillerCipher
This repo contains code which breaks the infamous Zodiac 408 Ciphertext Message



About Zodiac Killer
From  - The Zodiac Killer or Zodiac was a serial killer who operated in northern California in the late 1960s and early 1970s. The killer's identity remains unknown. The Zodiac murdered victims in Benicia, Vallejo, Lake Berryessa, and San Francisco between December 1968 and October 1969. Four men and three women between the ages of 16 and 29 were targeted. The killer originated the name "Zodiac" in a series of taunting letters sent to the local Bay Area press. These letters included four cryptograms (or ciphers). Of the four cryptograms sent, only one has been definitively solved.[1]

Suspects have been named by law enforcement and amateur investigators, but no conclusive evidence has surfaced. The San Francisco Police Department (SFPD) marked the case "inactive" in April 2004, but re-opened it at some point prior to March 2007.[2][3] The case also remains open in the city of Vallejo, as well as in Napa County and Solano County.[4] The California Department of Justice has maintained an open case file on the Zodiac murders since 1969.[5]

Solution:
Create a hidden Markov model that breaks the zodiac 408 ciphertext based on probabilities of diagraph letter frequencies. Turns out it is a homophonic substitution cipher!

The following is the number mapped form of the Zodiac Cipher Text:
https://d1b10bmlvqabco.cloudfront.net/attach/j6nmd2xw4gn4je/hc278o6iohu1ig/j7iaqqdith0m/Z408.txt

1 2 3 4 5 4 6 7 2 8 9 10 11 12 13 11 7 

14 15 16 17 18 19 20 21 1 22 3 23 24 25 26 19 17

27 28 19 29 6 30 8 31 26 32 33 34 35 19 36 37 38 

39 40 4 1 2 7 3 9 10 41 6 2 42 10 43 26 44 

8 29 45 27 5 28 46 47 48 12 20 22 15 14 17 31 19 

23 16 26 18 36 1 24 30 38 21 26 13 49 37 50 39 40 

10 34 33 30 19 44 43 9 1 26 18 7 32 21 39 2 7 

45 46 4 3 2 7 23 13 26 44 22 27 6 29 10 10 8

51 5 24 26 12 30 38 14 26 25 49 37 45 27 47 1 52 

7 3 36 10 16 28 11 21 48 34 40 17 44 6 22 8 20 

5 51 12 9 15 14 30 37 16 33 45 38 43 29 10 21 22

30 1 36 10 53 32 19 47 48 46 17 4 23 13 28 35 41

3 37 27 49 10 6 33 2 45 38 34 15 44 24 22 11 18

47 30 25 28 8 37 1 49 45 27 43 34 41 38 5 40 3

50 6 12 8 41 1 52 7 15 14 48 16 15 32 33 9 3 

29 11 39 47 43 42 6 17 21 31 36 50 18 2 2 25 27

34 8 38 39 51 44 4 1 2 2 5 42 41 3 52 7 15 

12 17 13 26 14 26 53 20 52 49 51 16 23 1 41 1 7

2 9 32 37 10 6 51 16 53 46 19 26 53 29 39 26 14 

15 5 17 18 19 24 44 53 32 19 41 1 2 52 45 33 53 

22 25 20 7 13 1 50 13 41 36 46 48 31 45 25 11 26 

53 17 46 52 52 21 17 37 3 9 10 13 35 20 2 18 51

5 23 28 32 33 26 53 49 28 30 16 47 7 3 35 14 21

15 44 13 47 1 14 30 21 26 44 22 27 38 11 19 30 8






References / Good Reads:

1)Wikipedia https://en.wikipedia.org/wiki/Zodiac_Killer
2)https://www.wired.com/2012/12/codes/
3)http://scholarworks.sjsu.edu/cgi/viewcontent.cgi?article=4566&context=etd_theses
