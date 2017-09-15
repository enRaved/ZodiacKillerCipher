/*
 Written by: Ravee Khandagale
 Hidden Markov Model that breaks the zodiac killer cipher
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#define N 26
#define M 52 //53 symbols
#define T 390 // Last 18 letters are fillers, it seems



static double A[N][N];

static double B[N][M]; //result can be interpreted with this matrix


static double bestB[N][M];
static double bestPi[N];


static double pi[N];
static int maxIters;

static int observationSequence[T] = {1, 2, 3, 4, 5, 4, 6, 7, 2, 8, 9, 10, 11, 12, 13, 11, 7,

14, 15, 16, 17, 18, 19, 20, 21, 1, 22, 3, 23, 24, 25, 26, 19, 17,

27, 28, 19, 29, 6, 30, 8, 31, 26, 32, 33, 34, 35, 19, 36, 37, 38,

39, 40, 4, 1, 2, 7, 3, 9, 10, 41, 6, 2, 42, 10, 43, 26, 44,

8, 29, 45, 27, 5, 28, 46, 47, 48, 12, 20, 22, 15, 14, 17, 31, 19,

23,16, 26, 18, 36, 1, 24, 30, 38, 21, 26, 13, 49, 37, 50, 39, 40,

10, 34, 33, 30, 19, 44, 43, 9, 1, 26, 18, 7, 32, 21, 39, 2, 7,

45, 46, 4, 3, 2, 7, 23, 13, 26, 44, 22, 27, 6, 29, 10, 10, 8,

51, 5, 24, 26, 12, 30, 38, 14, 26, 25, 49, 37, 45, 27, 47, 1, 52,

7, 3, 36, 10, 16, 28, 11, 21, 48, 34, 40, 17, 44, 6, 22, 8, 20,

5, 51, 12, 9, 15, 14, 30, 37, 16, 33, 45, 38, 43, 29, 10, 21, 22,

30, 1, 36, 10, 53, 32, 19, 47, 48, 46, 17, 4, 23, 13, 28, 35, 41,

3, 37, 27, 49, 10, 6, 33, 2, 45, 38, 34, 15, 44, 24, 22, 11, 18,

47, 30, 25, 28, 8, 37, 1, 49, 45, 27,43, 34, 41, 38, 5, 40, 3,

50, 6, 12, 8, 41, 1, 52, 7, 15, 14, 48, 16, 15, 32, 33, 9, 3,

29, 11, 39, 47, 43, 42, 6, 17, 21, 31, 36, 50, 18, 2, 2, 25, 27,

34, 8, 38, 39, 51, 44, 4, 1, 2, 2, 5, 42, 41, 3, 52, 7, 15,

12, 17, 13, 26, 14, 26, 53, 20, 52, 49, 51, 16, 23, 1, 41, 1, 7,

2, 9, 32, 37, 10, 6, 51, 16, 53, 46, 19, 26, 53, 29, 39, 26, 14,

15, 5, 17, 18, 19, 24, 44, 53, 32, 19, 41, 1, 2, 52, 45, 33, 53,

22, 25, 20, 7, 13, 1, 50, 13, 41, 36, 46, 48, 31, 45, 25, 11, 26,

53, 17, 46, 52, 52, 21, 17, 37, 3, 9, 10, 13, 35, 20, 2, 18, 51,

5, 23, 28, 32, 33, 26, 53, 49, 28, 30, 16, 47, 7, 3, 35, 14, 21,

15, 44, 13, 47, 1, 14, 30, 21, 26, 44, 22, 27, 38, 11, 19, 30, 8};
static double C[T];
static double alpha[T][N];
static double beta[T][N];
static double mygamma[T][N];
static double digamma[T][N][N];
static double bestScore;

int iters = 0;
double oldLogProb = -DBL_MAX, logProb;

void computeAlphaPass();
void computeBetaPass();
void computeGammaDigamma();
void reestimate();
void initialiseGreekLetters();

void printGreekLetter(double [][N]);


int convertLettersToNumbers(char);

void printSequence(int []);

void generateDiagraph();
void normalizeA();
void assignBestModel();

int main(int argc, char *argv[]){
int numberOfHmms = 2;
int number = 0;
	maxIters = atoi(argv[3]);
	int seed = atoi(argv[4]);


	

bestScore = -DBL_MAX;

while (number < numberOfHmms){

	iters = 0;
	logProb = 0;

	initialiseGreekLetters();


	int k = 0;
	int c;
	iters = 0;
	


	//initilaise A with the diagraph values
	generateDiagraph();
    normalizeA();



	//initialise B randomly and make row stochastic
	
	double tempB[N][M];
	for(int i = 0; i < N; i++){
		double sum = 0;
		for(int j = 0; j < M; j++){

			double diff = 0.7 - 0.3;
			tempB[i][j] = (((float) rand() / RAND_MAX) * diff) + 0.3;
			tempB[i][j] += 5;
			sum += tempB[i][j];	
		}

		for(int k = 0; k < M; k++){
			B[i][k] = tempB[i][k] / sum;
		}
	}


	//initialise pi
	
	
	double sum = 0;
	double tempPi[N];
	for(int j = 0; j < N; j++){
			
			double diff = 0.6 - 0.4;
			tempPi[j] = (((float) rand() / RAND_MAX) * diff) + 0.4;
			tempPi[j] += 5;
			sum += tempPi[j];	
		}
	for(int j = 0; j < N; j++){
			pi[j] = tempPi[j] / sum;
		}


while(iters < maxIters || logProb > oldLogProb){

	computeAlphaPass();
	computeBetaPass();
	computeGammaDigamma();

	reestimate();

	// 6. Compute Compute log[P (O | λ)]
	logProb = 0;
	for(int i = 0; i < T; i++){
		logProb = logProb + log (C[i]);
	}
	logProb = -logProb;

	//To iterate or not to iterate, that is the question. . .
	

	iters = iters + 1;

	

	//if(iters < maxIters && logProb > oldLogProb){
	if(iters < maxIters){
		oldLogProb = logProb;
		
	}
	else{


		printf("Interation %d: %f\n", iters, logProb);
		if(bestScore < logProb){
			bestScore = logProb;
			assignBestModel();
			}



		printf("\n");
        break;
	}


} //while ends here


number++;
printf("Score for %d hmm: %lf\n", number, logProb);

}
printf("Best score: %lf\n", logProb);
printf("\nB OF BEST MODEL\n");
for(int i = 0; i < N; i++){
	printf("\n");
	for(int j = 0; j < M; j++){
		printf("%lf ",bestB[i][j]);
	}
}


char zodiacMappings[390] = "ilikekillingpeoplebecauseitissomuchfunitismorefunthankillingwildgameintheforrestbecausemanisthemostdangeroueanamalofalltokillsomethinggivesmethemostthrillingexperenceitisevenbetterthangettingyourrocksofwithagirlthebestpartofitisthaewhenidieiwillbereborninparadiceandalltheihavekilledwillbecomemyslavesiwillnotgiveyoumynamebecauseyouwilltrytosloidownoratopmycollectiogofslavesformyafterlifee";
char letters[26] = "abcdefghijklmnopqrstuvwxyz";
int correctCount = 0;

		printf("\nShifted Keys for encrypted a, b c,...z:");
		for(int i = 0; i < N; i++){
			printf("\n");
			double max = 0;
			int maxj = 0;
			for(int j = 0; j < M; j++){
				if( max  < bestB[i][j]){
					max = bestB[i][j];
					maxj = j;
				}

				for(int k = 0; k < 390; k++){

						if(maxj == observationSequence[k]){
							if(zodiacMappings[k] == letters[i]){
								correctCount++;
								break;
							}
						}
				}
					
				}
				printf("%d : %lf\n", maxj, max );
				}

				printf("\nCorrect Count %d\n" , correctCount);

}

void computeAlphaPass(){

	
	// compute α0(i)
		C[0] = 0;
		for(int i = 0; i < N; i++){
		alpha[0][i] = pi[i] * B[i][observationSequence[0]];
		C[0] = C[0] + alpha[0][i];
	}

	//scale the α0(i)
	C[0] = 1/C[0];
	for(int i = 0; i < N; i++){
		alpha[0][i] = C[0] * alpha[0][i];
	}

	//compute αt(i)
	for(int t = 1; t < T; t++){
		C[t] = 0;
		for(int i = 0; i < N; i++){
			alpha[t][i] = 0;
			for(int j = 0; j < N; j++){
				alpha[t][i] = alpha[t][i] + alpha[t-1][j] * A[j][i];
			}
			alpha[t][i] = alpha[t][i] * B[i][observationSequence[t]];
			C[t] = C[t] + alpha[t][i];
		}
		// scale αt(i)
		C[t] = 1/C[t];
		for(int i = 0; i < N; i++){
			alpha[t][i] = C[t] * alpha[t][i];
		}
	}

}

void computeBetaPass(){
	for(int i = 0; i < N; i++){
		beta[T-1][i] = C[T-1];
	}

	// β-pass
	for(int t = (T - 2); t >= 0; t--){
		for(int i = 0; i < N; i++){
			beta[t][i] = 0;
			for(int j = 0; j < N; j++){
				beta[t][i] = beta[t][i] + A[i][j] * B[j][observationSequence[t+1]] * beta[t+1][j];
			}
			// scale βt(i) with same scale factor as αt(i)
			beta[t][i] = C[t] * beta[t][i];
		}
	}
}

void computeGammaDigamma(){
	double numer, denom;
		for(int t = 0; t < T-1; t++){
		denom = 0;
		for(int i = 0; i < N; i++){
			for(int j = 0; j < N; j++){
				denom = denom + alpha[t][i] * A[i][j] * B[j][observationSequence[t+1]] * beta[t+1][j];
			}
		}
		for(int i = 0; i < N; i++){
			mygamma[t][i] = 0;

			for(int j = 0; j < N; j++){

				digamma[t][i][j] = ( alpha[t][i] * A[i][j] * B[j][observationSequence[t+1]] * beta[t+1][j] ) / denom;
				mygamma[t][i] = mygamma[t][i] + digamma[t][i][j];

			}
		}
	}

	// Special case for γT−1(i)
	denom = 0;
	for(int i = 0; i < N; i++){
		denom = denom + alpha[T-1][i];
	}
	for(int i = 0; i < N; i++){
		mygamma[T-1][i] = alpha[T-1][i]/denom;
	}
}

void reestimate(){
	// 5. Re-estimate A, B and π

	//re-estimate π
	for(int i = 0; i < N; i++){
		pi[i] = mygamma[0][i];
	}

	 

	//re-estimate A
	double numer, denom;
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			numer = 0;
			denom = 0;
			for(int t  = 0; t < T-1; t++){
				numer = numer + digamma[t][i][j];
				denom = denom + mygamma[t][i];
			}
			A[i][j] = numer/denom;
		}
	}


	
	//re-estimate B
	for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++){
			numer = 0;
			denom = 0;
			for(int t = 0; t < T; t++){
				if(observationSequence[t]==j){
					numer = numer + mygamma[t][i];
				}
				denom = denom + mygamma[t][i];
			}
			B[i][j] = numer/denom;
		}
	}


}

void printGreekLetter(double greekletter[][N]){
//PRINT STATEMENT REMOVE
//print alpha, beta and gamma pass
printf("Pass\n");
for(int t = 0; t < T; t++){
	for(int i = 0; i < N; i++){
			printf("%lf\t", greekletter[t][i]);
		}
		printf("\n");
}
}

int convertLettersToNumbers(char c){
	//printf("%c\n", c);
		return c - 'a';
}



void printSequence(int observationSequence[]){

	for (int i = 0; i < T; ++i)
	{
		printf("%d\t", observationSequence[i]);
	}
}

void generateDiagraph(){

    int count['z' - 'a' + 1]['z' - 'a' + 1] = {{ 0 }};
    int char0 = EOF, c1, c2;
    int t = 0;
    FILE *file;
    file = fopen("brown.txt", "r");
    c1 = getc(file);

    if (file != NULL) {
        while ((c2 = getc(file)) != EOF && t < T) {
            count[c1 - 'a'][c2 - 'a']++;
            c1 = c2;
            t++;
        }
        fclose(file);
        for (c1 = 'a'; c1 <= 'z'; c1++) {
            for (c2 = 'a'; c2 <= 'z'; c2++) {
                int frequency = count[c1 - 'a'][c2 - 'a'];
                // formulate matrix
                A[convertLettersToNumbers(c1)][convertLettersToNumbers(c2)] = frequency;
            }
        }
    }

}

void normalizeA(){

    double sumOfRow[N];
        
        //add 5 to each element
    for(int i = 0; i < 26; i++){

        for(int j = 0; j < 26; j++){

           A[i][j] = A[i][j] + 5;

        }

    }

    double sum = 0;
    for(int i = 0; i < 26; i++){
         for(int j = 0; j < 26; j++){
            
            sum = sum + A[i][j];
        }
        sumOfRow[i] = sum;
        sum = 0;
    }

    for(int i = 0; i < N; i++){

        for(int j = 0; j < N; j++){

            A[i][j] = A[i][j]/sumOfRow[i];
        }
    }

}

void assignBestModel(){
	for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++){
			bestB[i][j] = B[i][j];
		}
	}

	for(int i = 0; i < N; i++){
		bestPi[i] = pi[i];
	}
}

void initialiseGreekLetters(){
		//initilise alpha
	for(int t = 0; t < T; t++){
		for(int i = 0; i < N; i++){
			alpha[t][i] = 0;
		}
	}

	//initilise beta
	for(int t = 0; t < T; t++){
		for(int i = 0; i < N; i++){
			beta[t][i] = 0;
		}
	}

	//initialise gamma
	for(int t = 0; t < T; t++){
		for(int i = 0; i < N; i++){
			mygamma[t][i] = 0;
		}
	}

	//initialise digamma
	for(int t = 0; t < T; t++){
		for(int i = 0; i < N; i++){
			for(int j = 0; j < N; j++){
				digamma[t][i][j] = 0;
			}
		}
	}
}

