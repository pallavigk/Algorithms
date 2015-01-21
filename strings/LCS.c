#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Program to find Longest Common Subsequence of two strings X and Y
//
//Definitions:
//Sequence: A sequence is a list of items in which the order of items matters.
//we will be working with in this chapter are strings of characters, and we’ll
//and we use the term “string” instead of “sequence.”
//
//Subsequence: A subsequence Z of a string X is X, possibly with items removed
//For example, if X is the string GAC, then it has
//eight subsequences: GAC (no characters removed), GA (C removed),
//GC (A removed), AC (G removed), G (A and C removed), A (G and C
//removed), C (G and A removed), and the empty string (all characters
//removed).
//
//Common subsequence: If X and Y are strings, then Z is a common subsequence
//of X and Y if it is a subsequence of both of them.
//
//Longest common subsequence: Need not be unique.
//For example: IF X = CATCGA and Y = GTACCGTCA, then CTCA is a LCS. Note that 
//TCGA is also an LCS.
//
//Substring: differ: A substring is a subsequence of a string in which the
//characters must be drawn from contiguous positions in the string. For
//the string CATCGA, the subsequence ATCG is a substring but the subsequence
//CTCA is not.
//
//Application in computational biology:
//Biologists encode strands of
//Biologists encode strands of DNA as strings over just four characters—A, C, G, T
//which represent the base molecules adenine, cytosine, guanine, and thymine.
//The longer a common subsequence we can find between two
//strands of DNA, the more similar they are.
//
//How to solve the problem?
//Inefficient way:
//Try each subsequence of X and check whether it’s a subsequence of Y, working from
//the longest to the smallest subsequences of X, checking each against Y
//and stopping once you find a subsequence of both X and Y. If X has length m, 
//then it has 2m subsequences, and so even if we ignore the time to check each 
//subsequence against Y, the time to find an LCS would be at least exponential in 
//the length of X in the worst case.
//
//Dynamic programming: We need to find an optimal substructure for the problem. 
//An optimal solution to a problem contains optimal solutions to its subproblems
//To find an LCS of two strings via dynamic programming, we first need to decide 
//what constitutes a subproblem.
//
//If X is a string of length m, ie., X = x1x2x3...xm, then
//the ith prefix of X is the string x1x2x3...xi, and we denote it by Xi.
//Here 0 <= i <= m. X0 is the empty string.
//For example, if X is CATCGA, then X4 is CATC
//LCS of two strings contains within it an LCS of the prefixes of the two strings.
//
//Let X = x1x2x3...xm and Y = y1y2y3...yn.
//Assume They have some LCS, say Z, where Z = z1z2...zk for some length k, 
//which could be anywhere from 0 to the smaller of m and n.
//Consider last characters xm and yn. 
//  - If they are equal, then zk must be equal to this character. This means, 
//  z1z2...zk-1 must be an LCS of (Xm-1 and Yn-1). For example: when 
//  X = CATCGA and Y = GTACCGTCA and an LCS is Z = CTCA,the
//  last character, A, of X and Y is the last character of Z, and we
//  see that Z3 = CTC must be an LCS of X5 = CATCG and Y8 = GTACCGTC.
//
//  - If they are not equal, we have two possibilities
//      * zk might be the same as either the last character xm of X or the 
//      last character yn of Y, but not of both. This means, Z must be an
//      LCS of (X and Yn-1) or an LCS of (Xm-1 and Y)
//      * zk might not be the same as the last character of either X or Y.
//      In this case, Z is an LCS of (Xm-1 and Yn-1)
//
//Two step algorithm to find a LCS:
//1. Find the length of an LCS of X and Y, as well as the lengths of the 
//longest common subsequences of all prefixes of X and Y. Call this algorithm
//COMPUTE-LCS-TABLE
//
//2. After computing the LCS lengths, we will “reverse engineer” how we computed 
//these lengths to find an actual LCS of X and Y. Call this algorithm ASSEMBLE-LCS
//
//Procedure COMPUTE-LCS-TABLE(X, Y)
//Inputs: X and Y : two strings of length m and n, respectively.
//Output: The array l[0..m, 0..n]. The value of l[m][n] is the length
//of a longest common subsequence of X and Y.
//1. Let l[0..m, 0..n] be a new array.
//2. For i = 0 to m
//  A. Set l[i][0] =  0
//3. For j = 0 to n
//  A. Set l[0]j] = 0.
//4. For i = 1 to m:
//  A. For j = 1 to n:
//      i. If xi is the same as yj , then set l[i][j] = l[i-1][j-1] + 1
//      ii. Otherwise (xi differs from yj ), set l[i][j] to the larger of
//      l[i-1][j] and l[i][j-1]. If both of them are equal,it doesn’t 
//      matter which you choose.
//5. Return the array l .
//
//Procedure ASSEMBLE-LCS(X,Y,l,i,j)
//Inputs:
//X and Y : two strings.
//l : the array filled in by the COMPUTE-LCS-TABLE procedure.
//i and j : indices into X and Y, respectively, as well as into l .
//
//Output: An LCS of Xi and Yj
//
//1. If l[i][j] equals 0, then return the empty string.
//2. Otherwise (because l[i][j] is positive, both i and j are positive),
//   if xi is the same as yj , then return the string formed by first
//   recursively calling ASSEMBLE-LCS(X,Y,l,i-1,j-1) and
//   then appending xi (or yj ) to the end of the string returned by the
//   recursive call.
//3. Otherwise (xi differs from yj ), if l[i][j-1] is greater than
//   l[i-1][j], then return the string returned by recursively calling
//   ASSEMBLE-LCS(X,Y,l,i,j-1).
//4. Otherwise (xi differs from yj and l[i][j-1] is less than or equal
//   to l[i-1][j], return the string returned by recursively calling
//   ASSEMBLE-LCS(X,Y,l,i-1,j).
//

void ComputeLCSTable(const char *X, const char *Y, int **length, int m, int n) {
    //Any Xi with Y0 has an LCS of length 0.
    for (int i = 0; i <= m; i++)
        length[i][0] = 0;
    //Any Yi with X0 has an LCS of length 0. 
    for (int j = 0; j <= n; j++) 
        length[0][j] =0;

    //An string X of length m has m+1 prefixes including the empty prefix (ie., X0,X1,..,Xm)
    //C array indexes are zero based. So, to accces ith charater of the string, refer to (i-1)th
    //position in the array. 
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i-1] == Y[j-1])
                length[i][j] = length[i-1][j-1] + 1;
            else
                length[i][j] = length[i][j-1] > length[i-1][j] ? length[i][j-1] : length[i-1][j]; 
        }
    }
}

void AssembleLCS(const char *X, const char *Y, int **length, int i, int j, char *LCS) {

    //Xi and Yj has no LCS. Do nothing and return
    if (length[i][j] == 0) return ;

    if (X[i-1] == Y[j-1]) { //ith character of X is equal to jth character of  Y.
        AssembleLCS(X,Y,length,i-1,j-1,LCS); //So, find the LCS of X(i-1) and Y(j-1) and append Xi(or Yi)
        LCS[length[i][j]-1] = X[i-1];
        printf("LCS[%d] : %c\n",length[i][j]-1,X[i-1]);
    }
    else if (length[i][j-1] > length[i-1][j]) { //LCS of Xi with Yj-1 is longer. So go for that LCS.
        AssembleLCS(X,Y,length,i,j-1,LCS);
    }
    else //LCS of Xi with Yj-1 is smaller or equal to LCS of Xi-1 and Yj. So go for that LCS.
        AssembleLCS(X,Y,length,i-1,j,LCS);
}

void findLCS(const char *str1, const char *str2, char **LCSRef) {

    if (!(str1 && str2)) return; //if one of them is NULL, return NULL

    int m = strlen(str1);
    int n = strlen(str2);

    //We need a 2D array with rows = 0..m and cols = 0..n
    int **lenArray = NULL;
    lenArray = (int **)malloc((m+1) * sizeof(int *));
    if (lenArray == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(-1);
    }
    for (int i = 0; i <= m; i++) {
        lenArray[i] = (int *)malloc((n+1) * sizeof(int));
        if (lenArray[i] == NULL) {
            fprintf(stderr, "out of memory\n");
            exit(-1);
        }
    }
    ComputeLCSTable(str1,str2,lenArray,m,n);
    printf("LCS table \n");

#if 0
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++)    
            printf("%d ",lenArray[i][j]);
        printf("\n");
    }
#endif

    int lengthLCS = lenArray[m][n];
    printf("LCS length %d\n",lenArray[m][n]);

    if (lengthLCS) {
	*LCSRef = (char *)malloc(lengthLCS+1 * sizeof(char));
	if (*LCSRef == NULL) {
	    fprintf(stderr, "out of memory\n");
	    exit(-1);
	}
	(*LCSRef)[lengthLCS] = '\0';
	//*(*LCSRef+lengthLCS) = '\0'; this is fine too 
	AssembleLCS(str1,str2,lenArray, m, n, *LCSRef);
    }
}

int main() {
    //char str1[] = "CATCGA";
    //char str2[] = "GTACCGTCA";
    //
    //char str1[] = "Pallavi";
    //char str2[] = "asnPaidf";

    //char str1[] = "Pallavi";
    //char str2[] = "xyzxyzxyzyx";

    char str1[] = "abcdef";
    char str2[] = "acdgea";
    char *LCS = NULL;
    findLCS(str1,str2,&LCS);
    if (LCS != NULL)
        printf("LCS of %s and %s is %s\n",str1,str2,LCS);
    else
        printf("There is no LCS between %s and %s\n",str1,str2);
}

